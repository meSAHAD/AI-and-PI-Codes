#include <stdio.h>

#define MAX_NODES 10
#define INFINITY 9999

// --- Global variables ---

// Adjacency matrix to represent the graph with weights/costs
// graph[i][j] = cost of edge from i to j. 0 if no direct edge.
int graph[MAX_NODES][MAX_NODES];
int numNodes;

// Array to store the minimum cost from the start node to any other node
int cost[MAX_NODES];

// Array to keep track of visited nodes
int visited[MAX_NODES];

// --- Uniform-Cost Search Algorithm ---

void ucs(int startNode, int goalNode)
{
    int i, j, count, minCost, nextNode;

    // Initialize cost and visited arrays
    for (i = 0; i < numNodes; i++)
    {
        cost[i] = INFINITY;
        visited[i] = 0;
    }

    // Cost of start node is 0
    cost[startNode] = 0;

    // The algorithm runs until all nodes are visited
    for (count = 0; count < numNodes - 1; count++)
    {
        minCost = INFINITY;

        // Find the unvisited node with the smallest cost
        for (i = 0; i < numNodes; i++)
        {
            if (!visited[i] && cost[i] < minCost)
            {
                minCost = cost[i];
                nextNode = i;
            }
        }

        // Mark the selected node as visited
        visited[nextNode] = 1;

        // If we have reached the goal, we can stop early
        if (nextNode == goalNode)
        {
            break;
        }

        // Update the cost of the adjacent nodes
        for (i = 0; i < numNodes; i++)
        {
            // If there is an edge and the new path is cheaper
            if (!visited[i] && graph[nextNode][i] &&
                cost[nextNode] + graph[nextNode][i] < cost[i])
            {
                cost[i] = cost[nextNode] + graph[nextNode][i];
            }
        }
    }

    // Print the result
    if (cost[goalNode] == INFINITY)
    {
        printf("No path found from node %d to node %d.\n", startNode, goalNode);
    }
    else
    {
        printf("Minimum cost from node %d to node %d is: %d\n", startNode, goalNode, cost[goalNode]);
    }
}

// --- Main Function with Test Case ---

int main()
{
    // Test Case: A simple weighted graph with 5 nodes
    numNodes = 5;
    int startNode = 0;
    int goalNode = 4;

    // Define the graph using an adjacency matrix with costs
    // A value of 0 means no direct edge.
    //      Nodes: 0  1  2  3  4
    // ---------------------------
    int testGraph[5][5] = {
        {0, 1, 5, 0, 0}, // 0 -> 1 (cost 1), 0 -> 2 (cost 5)
        {0, 0, 2, 8, 0}, // 1 -> 2 (cost 2), 1 -> 3 (cost 8)
        {0, 0, 0, 0, 3}, // 2 -> 4 (cost 3)
        {0, 0, 0, 0, 4}, // 3 -> 4 (cost 4)
        {0, 0, 0, 0, 0}};

    // Copy the test graph into the global graph variable
    int i, j;
    for (i = 0; i < numNodes; i++)
    {
        for (j = 0; j < numNodes; j++)
        {
            graph[i][j] = testGraph[i][j];
        }
    }

    // Run UCS to find the cheapest path from node 0 to node 4
    ucs(startNode, goalNode);

    // Expected Path: 0 -> 1 -> 2 -> 4
    // Expected Output: Minimum cost from node 0 to node 4 is: 6
    return 0;
}
