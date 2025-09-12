#include <stdio.h>

#define MAX_NODES 10
#define TRUE 1
#define FALSE 0

// --- Global variables ---

// Adjacency matrix representation of the graph
int graph[MAX_NODES][MAX_NODES];
int numNodes;

// --- Depth-Limited Search (DLS) ---
// This is a helper function for IDS. It performs DFS up to a specific depth.

int dls(int currentNode, int goalNode, int depthLimit)
{
    // If the current node is the goal, we've found it
    if (currentNode == goalNode)
    {
        return TRUE;
    }

    // If the depth limit is reached, stop exploring this path
    if (depthLimit <= 0)
    {
        return FALSE;
    }

    // Recursively explore adjacent nodes
    int i;
    for (i = 0; i < numNodes; i++)
    {
        // If there is an edge
        if (graph[currentNode][i] == 1)
        {
            // If the goal is found in the deeper level, return true
            if (dls(i, goalNode, depthLimit - 1) == TRUE)
            {
                return TRUE;
            }
        }
    }

    // Goal not found in this path within the depth limit
    return FALSE;
}

// --- Iterative Deepening Search (IDS) ---

void ids(int startNode, int goalNode, int maxDepth)
{
    int depth;
    printf("Searching for goal node %d from start node %d...\n", goalNode, startNode);

    // Perform DLS for each depth from 0 to maxDepth
    for (depth = 0; depth <= maxDepth; depth++)
    {
        printf("Searching at depth limit: %d\n", depth);
        // If DLS finds the goal at the current depth
        if (dls(startNode, goalNode, depth) == TRUE)
        {
            printf("\nGoal node %d found at depth %d.\n", goalNode, depth);
            return; // Exit after finding the goal
        }
    }

    // If the loop completes, the goal was not found within the max depth
    printf("\nGoal node %d not found within max depth of %d.\n", goalNode, maxDepth);
}

// --- Main Function with Test Case ---

int main()
{
    // Test Case: A simple graph with 7 nodes
    numNodes = 7;
    int startNode = 0;
    int goalNode = 6;
    int maxDepth = 5; // The maximum depth to search

    // Define the graph using an adjacency matrix
    //      Nodes: 0  1  2  3  4  5  6
    // ---------------------------------
    int testGraph[7][7] = {
        {0, 1, 1, 0, 0, 0, 0}, // 0 -> 1, 2
        {0, 0, 0, 1, 1, 0, 0}, // 1 -> 3, 4
        {0, 0, 0, 0, 0, 1, 0}, // 2 -> 5
        {0, 0, 0, 0, 0, 0, 0}, // 3
        {0, 0, 0, 0, 0, 0, 1}, // 4 -> 6
        {0, 0, 0, 0, 0, 0, 0}, // 5
        {0, 0, 0, 0, 0, 0, 0}  // 6 (Goal)
    };

    // Copy the test graph into the global graph variable
    int i, j;
    for (i = 0; i < numNodes; i++)
    {
        for (j = 0; j < numNodes; j++)
        {
            graph[i][j] = testGraph[i][j];
        }
    }

    // Run IDS
    ids(startNode, goalNode, maxDepth);

    // Expected Output:
    // Searching at depth limit: 0
    // Searching at depth limit: 1
    // Searching at depth limit: 2
    // Goal node 6 found at depth 2.
    return 0;
}
