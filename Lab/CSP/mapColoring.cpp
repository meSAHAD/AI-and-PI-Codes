#include <stdio.h>

// --- Global Variables ---

// V is the number of vertices/regions in the map
#define V 4

// M is the number of available colors
#define M 4 // Increased to 4 to include Purple

// graph[V][V] is the adjacency matrix.
// graph[i][j] = 1 means region i and j are adjacent.
int graph[V][V] = {
    {0, 1, 1, 1},
    {1, 0, 1, 0},
    {1, 1, 0, 1},
    {1, 0, 1, 0},
};

// color[V] stores the color assigned to each region (as an integer).
// 0 means no color is assigned yet.
int color[V] = {0};

// Array of color names corresponding to the integer values.
// Index 0 is unused as we start coloring from 1.
const char *colorNames[] = {"", "Red", "Green", "Blue", "Purple"};

// --- Helper Functions ---

// Function to print the solution using color names
void printSolution()
{
    printf("Solution Found: The assigned colors are:\n");
    for (int i = 0; i < V; i++)
    {
        // Print the color name from the colorNames array
        printf(" Region %d ---> Color %s\n", i, colorNames[color[i]]);
    }
    printf("\n");
}

// Function to check if it's safe to color a vertex with a specific color.
// It checks if any adjacent vertex has the same color.
int isSafe(int v, int c)
{
    for (int i = 0; i < V; i++)
    {
        // If v and i are adjacent AND color of i is already c
        if (graph[v][i] == 1 && c == color[i])
        {
            return 0; // Not safe
        }
    }
    return 1; // Safe
}

// --- Backtracking Algorithm ---

// The main recursive function to solve the map coloring problem.
// It tries to color vertices one by one, starting from vertex v.
int solveMapColoring(int v)
{
    // Base Case: If all vertices are colored, then we found a solution.
    if (v == V)
    {
        printSolution();
        return 1; // Return true to indicate a solution is found
    }

    // Try different colors for the current vertex v
    for (int c = 1; c <= M; c++)
    {
        // Check if the current color assignment is safe
        if (isSafe(v, c))
        {
            // Assign the color
            color[v] = c;

            // Recursively call for the next vertex
            if (solveMapColoring(v + 1) == 1)
            {
                return 1;
            }

            // If assigning color c doesn't lead to a solution,
            // then backtrack and remove the color assignment.
            color[v] = 0;
        }
    }

    // If no color can be assigned to this vertex, return false
    return 0;
}

// --- Main Driver ---

int main()
{
    printf("--- Map Coloring Problem using Backtracking ---\n");

    // Start the algorithm from the first vertex (vertex 0)
    if (solveMapColoring(0) == 0)
    {
        printf("No solution exists with the given constraints.\n");
    }

    return 0;
}
