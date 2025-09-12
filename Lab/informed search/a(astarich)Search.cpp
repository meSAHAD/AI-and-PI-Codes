#include <stdio.h>

#define MAX_NODES 10
#define INFINITY 9999

// --- Global variables ---

int graph[MAX_NODES][MAX_NODES]; // Adjacency matrix representing the graph with actual costs
int numNodes;

int heuristic[MAX_NODES]; // Array for heuristic costs (h(n)) from each node to the goal
int g_cost[MAX_NODES]; // Cost from start node to current node (g(n))
int f_cost[MAX_NODES]; // Total estimated cost f(n) = g(n) + h(n)
int visited[MAX_NODES]; // Array to track visited nodes (the closed set)

// --- A* Search Algorithm ---  Expands the node with the lowest f(n) value.
void a_star(int startNode, int goalNode)
{
    int i, count, min_f_cost, currentNode;

    for (i = 0; i < numNodes; i++) // Initialize all costs and visited status
    {
        g_cost[i] = INFINITY;
        f_cost[i] = INFINITY;
        visited[i] = 0;
    }

    g_cost[startNode] = 0;
    f_cost[startNode] = g_cost[startNode] + heuristic[startNode];

    printf("A* Search Path Exploration:\n");

    for (count = 0; count < numNodes; count++) // Loop until all nodes are considered or goal is found
    {
        min_f_cost = INFINITY;
        currentNode = -1;

        // Find the unvisited node with the lowest f_cost    This simulates an "open list" or priority queue
        for (i = 0; i < numNodes; i++)
        {
            if (!visited[i] && f_cost[i] < min_f_cost)
            {
                min_f_cost = f_cost[i];
                currentNode = i;
            }
        }

        if (currentNode == -1)
        {
            printf("No path found.\n");
            return;
        }

        printf("Visiting Node: %d (g=%d, h=%d, f=%d)\n", currentNode, g_cost[currentNode], heuristic[currentNode], f_cost[currentNode]);

        if (currentNode == goalNode)
        {
            printf("\nGoal reached! Minimum cost is %d.\n", g_cost[goalNode]);
            return;
        }

        visited[currentNode] = 1; // Mark the current node as visited (move to closed set)

        for (i = 0; i < numNodes; i++) // Explore neighbors of the current node

        {
            if (graph[currentNode][i] > 0) // If there's an edge to a neighbor

            {
                int new_g_cost = g_cost[currentNode] + graph[currentNode][i]; // Calculate the new g_cost for the neighbor
                if (new_g_cost < g_cost[i]) // If this new path is better than any previous path
                {
                    g_cost[i] = new_g_cost; // Update g_cost and f_cost for the neighbor
                    f_cost[i] = g_cost[i] + heuristic[i];
                }
            }
        }
    }
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
    int testHeuristic[] = {8, 7, 6, 2, 1, 0}; // Admissible heuristic

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

    // Run A* Search
    a_star(startNode, goalNode);

    // Expected Output:
    // Visiting Node: 0 (g=0, h=8, f=8)
    // Visiting Node: 1 (g=2, h=7, f=9)
    // Visiting Node: 4 (g=3, h=1, f=4)
    // Visiting Node: 5 (g=8, h=0, f=8)
    // Goal reached! Minimum cost is 8.
    // The optimal path is 0 -> 1 -> 4 -> 5 with cost 2 + 1 + 5 = 8
    return 0;
}
