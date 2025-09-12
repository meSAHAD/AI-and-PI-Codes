#include <stdio.h>

#define MAX_NODES 10
#define INFINITY 9999

// --- Global variables ---

// Adjacency matrix to represent the graph with actual costs (g(n))
// graph[i][j] > 0 if there is an edge from i to j
int graph[MAX_NODES][MAX_NODES];
int numNodes;

// Array to store the heuristic cost (h(n)) for each node
// This is an estimate of the cost from a node to the goal
int heuristic[MAX_NODES];

// Array to keep track of visited nodes
int visited[MAX_NODES];

// --- Greedy Best-First Search Algorithm ---
// It always expands the node that appears to be closest to the goal,
// based solely on the heuristic value.

void greedy_bfs(int startNode, int goalNode)
{
    int i, currentNode, nextNode;
    int minHeuristic;

    // Initialize all nodes as not visited
    for (i = 0; i < numNodes; i++)
    {
        visited[i] = 0;
    }

    currentNode = startNode;
    printf("Path: %d ", currentNode);
    visited[currentNode] = 1;

    // Loop until the goal is reached
    while (currentNode != goalNode)
    {
        minHeuristic = INFINITY;
        nextNode = -1;

        // Look at all neighbors of the current node
        for (i = 0; i < numNodes; i++)
        {
            // If there is an edge and the neighbor hasn't been visited
            if (graph[currentNode][i] > 0 && !visited[i])
            {
                // Find the neighbor with the lowest heuristic value
                if (heuristic[i] < minHeuristic)
                {
                    minHeuristic = heuristic[i];
                    nextNode = i;
                }
            }
        }

        // If no unvisited neighbor is found, path does not exist
        if (nextNode == -1)
        {
            printf("\nPath to goal not found.\n");
            return;
        }

        // Move to the node with the best heuristic
        currentNode = nextNode;
        printf("%d ", currentNode);
        visited[currentNode] = 1;
    }
    printf("\nGoal reached!\n");
}

// --- Main Function with Test Case ---

int main()
{
    // Test Case: A graph with 6 nodes
    numNodes = 6;
    int startNode = 0;
    int goalNode = 5;

    // Define the graph (value is cost, 0 means no edge)
    //      Nodes: 0  1  2  3  4  5
    // ---------------------------
    int testGraph[6][6] = {
        {0, 2, 3, 0, 0, 0}, // 0 -> 1, 2
        {2, 0, 0, 4, 1, 0}, // 1 -> 0, 3, 4
        {3, 0, 0, 0, 0, 7}, // 2 -> 0, 5 (Goal)
        {0, 4, 0, 0, 0, 0}, // 3 -> 1
        {0, 1, 0, 0, 0, 5}, // 4 -> 1, 5 (Goal)
        {0, 0, 7, 0, 5, 0}  // 5 (Goal)
    };

    // Heuristic values (estimated cost from node to goal)
    // Node:    0   1  2  3  4  5
    int testHeuristic[] = {10, 8, 5, 4, 2, 0};

    // Copy test data into global variables
    int i, j;
    for (i = 0; i < numNodes; i++)
    {
        heuristic[i] = testHeuristic[i];
        for (j = 0; j < numNodes; j++)
        {
            graph[i][j] = testGraph[i][j];
        }
    }

    // Run the Greedy Best-First Search
    greedy_bfs(startNode, goalNode);

    // Expected behavior:
    // From 0, node 2 (h=5) is better than node 1 (h=8).
    // From 2, the only option is 5 (goal).
    // Expected Output: Path: 0 2 5
    // Note: It doesn't find the shortest path (0-1-4-5), just the one that looks best at each step.
    return 0;
}
