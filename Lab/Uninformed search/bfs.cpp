#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX_NODES = 10;

// Adjacency matrix to represent the graph
int graph[MAX_NODES][MAX_NODES];
int numNodes;

// Array to keep track of visited nodes
bool visited[MAX_NODES];

// --- Breadth-First Search Algorithm ---
void bfs(int startNode)
{
    // Initialize all nodes as not visited
    for (int i = 0; i < numNodes; i++)
        visited[i] = false;

    queue<int> q;
    visited[startNode] = true;
    q.push(startNode);

    cout << "BFS Traversal: ";

    while (!q.empty())
    {
        int currentNode = q.front();
        q.pop();
        cout << currentNode << " ";

        // Visit all adjacent nodes of the current node
        for (int i = 0; i < numNodes; i++)
        {
            if (graph[currentNode][i] == 1 && !visited[i])
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

// --- Main Function with Test Case ---
int main()
{
    // Test Case: A simple graph with 6 nodes
    numNodes = 6;
    int startNode = 0;

    int testGraph[6][6] = {
        {0, 1, 1, 0, 0, 0}, // Node 0 is connected to 1, 2
        {1, 0, 0, 1, 1, 0}, // Node 1 is connected to 0, 3, 4
        {1, 0, 0, 0, 0, 1}, // Node 2 is connected to 0, 5
        {0, 1, 0, 0, 0, 0}, // Node 3 is connected to 1
        {0, 1, 0, 0, 0, 0}, // Node 4 is connected to 1
        {0, 0, 1, 0, 0, 0}  // Node 5 is connected to 2
    };

    // Copy the test graph into the global graph variable
    for (int i = 0; i < numNodes; i++)
        for (int j = 0; j < numNodes; j++)
            graph[i][j] = testGraph[i][j];

    // Run the BFS algorithm starting from node 0
    bfs(startNode);

    // Expected Output: BFS Traversal: 0 1 2 3 4 5
    return 0;
}
