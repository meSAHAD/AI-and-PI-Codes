#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX], visited[MAX], n;

int DFS_Limited(int v, int target, int limit, int depth)
{
    visited[v] = 1;
    printf("%d ", v);

    if (v == target)
    {
        printf("\nTarget %d found at depth %d\n", v, depth);
        return 1; // found
    }

    if (depth == limit)
        return 0;

    for (int i = 0; i < n; i++)
    {
        if (graph[v][i] == 1 && !visited[i])
        {
            if (DFS_Limited(i, target, limit, depth + 1))
                return 1;
        }
    }
    return 0;
}

void IDS(int start, int target)
{
    for (int limit = 0; limit < n; limit++)
    {
        for (int i = 0; i < n; i++)
            visited[i] = 0;
        printf("\nDepth Limit = %d\n", limit);
        if (DFS_Limited(start, target, limit, 0))
            return;
    }
    printf("\nTarget not found\n");
}

int main()
{
    int start = 0, target;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter target vertex: ");
    scanf("%d", &target);

    printf("Iterative Deepening Search starting from 0:\n");
    IDS(start, target);

    return 0;
}
