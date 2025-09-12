#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // We need this for INT_MAX, which is the largest possible integer.

// --- CONFIGURATION ---
#define NUM_NODES 8    // The total number of nodes (A through H) in our graph.
#define BEAM_WIDTH 3   // 'k', the number of best paths we keep at each step.
#define MAX_PATH_LEN 8 // A path can't be longer than the total number of nodes.

// --- THE GRAPH ---
// This is the graph from your image, stored as an "adjacency matrix".
// The value at graph[row][col] is the distance between those two nodes.
// A '0' means there is no direct path.
// Nodes are: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, 7=H
int graph[NUM_NODES][NUM_NODES] = {
    // A  B   C   D   E  F   G  H
    {0, 11, 14, 7, 0, 0, 0, 0},  // Distances from A
    {11, 0, 0, 0, 15, 0, 0, 0},  // Distances from B
    {14, 0, 0, 18, 8, 10, 0, 0}, // Distances from C
    {7, 0, 18, 0, 0, 25, 0, 0},  // Distances from D
    {0, 15, 8, 0, 0, 0, 0, 9},   // Distances from E
    {0, 0, 10, 25, 0, 0, 20, 0}, // Distances from F
    {0, 0, 0, 0, 0, 20, 0, 10},  // Distances from G
    {0, 0, 0, 0, 9, 0, 10, 0}    // Distances from H
};

// --- HELPER FUNCTIONS ---

// This function prints a path in a human-readable format.
void printPath(int path_nodes[], int path_length, int path_cost)
{
    printf("Path: ");
    for (int i = 0; i < path_length; i++)
    {
        // Convert node index (0) to a character ('A') for printing.
        printf("%c ", path_nodes[i] + 'A');
        if (i < path_length - 1)
        {
            printf("-> ");
        }
    }
    printf("| Cost: %d\n", path_cost);
}

// This function checks if a node is already in a path.
// This is important to prevent cycles (e.g., A -> D -> A -> D ...).
int isVisited(int path_nodes[], int path_length, int node)
{
    for (int i = 0; i < path_length; i++)
    {
        if (path_nodes[i] == node)
        {
            return 1; // 1 means 'true'
        }
    }
    return 0; // 0 means 'false'
}

// This function sorts all the potential next paths to find the best ones.
// It uses a simple Bubble Sort algorithm.
// Because we aren't using structs, we have to sort three arrays (costs, lengths, and the paths themselves) at the same time.
void sortPaths(int paths[][MAX_PATH_LEN], int lengths[], int costs[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            // If the cost of the current path is greater than the next one, swap them.
            if (costs[j] > costs[j + 1])
            {
                // 1. Swap the costs
                int temp_cost = costs[j];
                costs[j] = costs[j + 1];
                costs[j + 1] = temp_cost;

                // 2. Swap the lengths
                int temp_length = lengths[j];
                lengths[j] = lengths[j + 1];
                lengths[j + 1] = temp_length;

                // 3. Swap the entire path arrays. This requires a loop.
                int temp_path_nodes[MAX_PATH_LEN];
                for (int k = 0; k < MAX_PATH_LEN; k++)
                    temp_path_nodes[k] = paths[j][k];
                for (int k = 0; k < MAX_PATH_LEN; k++)
                    paths[j][k] = paths[j + 1][k];
                for (int k = 0; k < MAX_PATH_LEN; k++)
                    paths[j + 1][k] = temp_path_nodes[k];
            }
        }
    }
}

// --- THE MAIN ALGORITHM ---
void beamSearch(int startNode, int goalNode)
{
    // The "beam" holds the best `k` paths we are currently considering.
    // We use three separate arrays to store the path data.
    int beam_paths[BEAM_WIDTH][MAX_PATH_LEN];
    int beam_lengths[BEAM_WIDTH];
    int beam_costs[BEAM_WIDTH];

    // --- STEP 1: INITIALIZATION ---
    // Start the beam with only one path: the starting node itself.
    for (int i = 0; i < BEAM_WIDTH; i++)
    {
        beam_lengths[i] = 0;     // Length is 0 for empty paths
        beam_costs[i] = INT_MAX; // Cost is infinity for empty paths
    }
    // Setup the very first path in our beam.
    beam_paths[0][0] = startNode; // Path is just the start node
    beam_lengths[0] = 1;          // Length is 1
    beam_costs[0] = 0;            // Cost is 0

    printf("Starting search from %c to %c with beam width %d...\n\n", startNode + 'A', goalNode + 'A', BEAM_WIDTH);

    // This is the main loop. It continues until the goal is found.
    while (1)
    {

        // --- STEP 2: GENERATE CANDIDATES ---
        // These arrays will hold all possible next paths we can take.
        int candidate_paths[BEAM_WIDTH * NUM_NODES][MAX_PATH_LEN];
        int candidate_lengths[BEAM_WIDTH * NUM_NODES];
        int candidate_costs[BEAM_WIDTH * NUM_NODES];
        int candidateCount = 0;

        // For every path currently in our beam...
        for (int i = 0; i < BEAM_WIDTH; i++)
        {
            // Skip any empty or invalid paths in the beam.
            if (beam_lengths[i] == 0)
                continue;

            // Get the last node of the current path.
            int lastNode = beam_paths[i][beam_lengths[i] - 1];

            // *** Check if we have reached the goal ***
            if (lastNode == goalNode)
            {
                printf("===================================\n");
                printf("Goal Reached! Here is the best path found:\n");
                printPath(beam_paths[i], beam_lengths[i], beam_costs[i]);
                printf("===================================\n");
                return; // Exit the function since we are done.
            }

            // ...look at all of its neighbors to create new paths.
            for (int neighbor = 0; neighbor < NUM_NODES; neighbor++)
            {
                int distance = graph[lastNode][neighbor];
                // If a path exists (distance > 0) and we haven't been to that neighbor yet...
                if (distance > 0 && !isVisited(beam_paths[i], beam_lengths[i], neighbor))
                {
                    // ...create a new candidate path.
                    // First, copy the old path.
                    for (int k = 0; k < beam_lengths[i]; k++)
                    {
                        candidate_paths[candidateCount][k] = beam_paths[i][k];
                    }
                    // Then, add the new neighbor to the end.
                    candidate_paths[candidateCount][beam_lengths[i]] = neighbor;
                    candidate_lengths[candidateCount] = beam_lengths[i] + 1;
                    candidate_costs[candidateCount] = beam_costs[i] + distance;
                    candidateCount++; // Increase the count of candidates found.
                }
            }
        }

        // If we couldn't find any new paths, the search is stuck.
        if (candidateCount == 0)
        {
            printf("Search stuck. No more paths to explore.\n");
            return;
        }

        // --- STEP 3: SORT AND SELECT ---
        // Sort all the candidates we found by their cost (shortest first).
        sortPaths(candidate_paths, candidate_lengths, candidate_costs, candidateCount);

        // --- STEP 4: FORM THE NEW BEAM ---
        // The new beam will be the top `k` (BEAM_WIDTH) candidates.
        for (int i = 0; i < BEAM_WIDTH && i < candidateCount; i++)
        {
            for (int k = 0; k < candidate_lengths[i]; k++)
            {
                beam_paths[i][k] = candidate_paths[i][k];
            }
            beam_lengths[i] = candidate_lengths[i];
            beam_costs[i] = candidate_costs[i];
        }
        // Invalidate any remaining slots in the beam from the previous iteration.
        for (int i = candidateCount; i < BEAM_WIDTH; i++)
        {
            beam_lengths[i] = 0;
            beam_costs[i] = INT_MAX;
        }
    }
}

// The program starts running here.
int main()
{
    int start = 0; // Node A
    int goal = 6;  // Node G

    // Call the main search function.
    beamSearch(start, goal);

    return 0;
}
