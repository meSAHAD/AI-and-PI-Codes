#include <stdio.h>
#include <string.h> // Required for memset
#include <limits.h> // Recommended for INT_MAX

// Use a large number for infinity, but smaller than INT_MAX to avoid overflow
#define INF 99999

// --- CHANGE 1: Updated number of cities ---
#define N 5 // There are 5 cities (A, B, C, D, E)

// --- CHANGE 2: Updated distance matrix for the graph ---
// Mapping: A=0, B=1, C=2, D=3, E=4
int dist[N][N] = {
    {0, 10, 8, 9, 7},    // Distances from A
    {10, 0, 10, INF, 6}, // Distances from B
    {8, 10, 0, 8, INF},  // Distances from C
    {9, INF, 8, 0, 6},   // Distances from D
    {7, 6, INF, 6, 0}    // Distances from E
};

// dp[mask][i] stores the minimum cost to visit cities in 'mask' ending at city 'i'.
// The size is automatically adjusted by the new 'N'.
int dp[1 << N][N];

// The core TSP function (logic remains the same)
int tsp(int mask, int pos)
{
    // Base case: If all cities have been visited
    if (mask == (1 << N) - 1)
    {
        return dist[pos][0]; // Return to the starting city (A)
    }

    // Memoization: If the result is already computed, return it
    if (dp[mask][pos] != -1)
    {
        return dp[mask][pos];
    }

    int min_ans = INF;

    // Explore all unvisited cities
    for (int city = 0; city < N; city++)
    {
        // Check if the city 'city' is not in the 'mask'
        if (!(mask & (1 << city)))
        {
            // Calculate cost of going from 'pos' to 'city' and then visiting the rest
            int new_ans = dist[pos][city] + tsp(mask | (1 << city), city);
            if (new_ans < min_ans)
            {
                min_ans = new_ans;
            }
        }
    }

    // Store and return the result
    return dp[mask][pos] = min_ans;
}

int main()
{
    // --- OPTIMIZATION: Use memset for faster initialization ---
    memset(dp, -1, sizeof(dp));

    // Start TSP from city 0 (A) with the initial mask '1' (binary 00001)
    int min_cost = tsp(1, 0);

    printf("The minimum cost for the tour is: %d\n", min_cost);

    // One possible path with this cost is A -> C -> D -> E -> B -> A
    // Another is A -> B -> E -> D -> C -> A

    return 0;
}