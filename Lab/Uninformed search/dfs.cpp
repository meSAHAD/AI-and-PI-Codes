#include <stdio.h>

#define MAX_NODES 10

// --- Global variables ---

// Adjacency matrix representation of the graph
int graph[MAX_NODES][MAX_NODES];
int numNodes;

// Array to keep track of visited nodes
int visited[MAX_NODES];

// --- Depth-First Search Algorithm (Recursive) ---

void dfs(int currentNode)
{
    int i;

    // Print the current node and mark it as visited
    printf("%d ", currentNode);
    visited[currentNode] = 1;

    // Recursively visit all adjacent, unvisited nodes
    for (i = 0; i < numNodes; i++)
    {
        // If there is an edge and the node has not been visited
        if (graph[currentNode][i] == 1 && !visited[i])
        {
            dfs(i);
        }
    }
}

// --- Main Function with Test Case ---

int main()
{
    // Test Case: A simple graph with 6 nodes
    numNodes = 6;
    int startNode = 0;

    // Define the graph using an adjacency matrix
    //      Nodes: 0  1  2  3  4  5
    // ---------------------------
    int testGraph[6][6] = {
        {0, 1, 1, 0, 0, 0}, // Node 0 is connected to 1, 2
        {1, 0, 0, 1, 1, 0}, // Node 1 is connected to 0, 3, 4
        {1, 0, 0, 0, 0, 1}, // Node 2 is connected to 0, 5
        {0, 1, 0, 0, 0, 0}, // Node 3 is connected to 1
        {0, 1, 0, 0, 0, 0}, // Node 4 is connected to 1
        {0, 0, 1, 0, 0, 0}  // Node 5 is connected to 2
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

    // Initialize all nodes as not visited
    for (i = 0; i < numNodes; i++)
    {
        visited[i] = 0;
    }

    printf("DFS Traversal: ");
    // Run the DFS algorithm starting from node 0
    dfs(startNode);
    printf("\n");

    // Expected Output (one possible valid traversal):
    // DFS Traversal: 0 1 3 4 2 5
    return 0;
}
