#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NUM_NODES 6
#define INF INT_MAX

int graph[NUM_NODES][NUM_NODES];
char index_to_node(int index)
{
    return 'A' + index;
}

void print_path(int *path, int length, int cost)
{
    printf("   Path: ");
    for (int i = 0; i < length; i++)
    {
        printf("%c", index_to_node(path[i]));
        if (i < length - 1)
            printf(" -> ");
    }
    printf("\n   Cost: %d\n\n", cost);
}

void setup_graph()
{
    for (int i = 0; i < NUM_NODES; i++)
    {
        for (int j = 0; j < NUM_NODES; j++)
        {
            graph[i][j] = -1; 
        }
    }
    graph[0][1] = 5;
    graph[1][0] = 5; // A-B
    graph[0][2] = 10;
    graph[2][0] = 10; // A-C
    graph[0][3] = 6;
    graph[3][0] = 6; // A-D
    graph[1][2] = 3;
    graph[2][1] = 3; // B-C
    graph[1][4] = 8;
    graph[4][1] = 8; // B-E
    graph[2][3] = 7;
    graph[3][2] = 7; // C-D
    graph[2][4] = 4;
    graph[4][2] = 4; // C-E
    graph[2][5] = 9;
    graph[5][2] = 9; // C-F
    graph[3][5] = 12;
    graph[5][3] = 12; // D-F
    graph[4][5] = 2;
    graph[5][4] = 2; // E-F
}

void hill_climbing_search(int start_node, int end_node)
{
    int path[NUM_NODES];
    int path_length = 0;
    int visited[NUM_NODES] = {0}; 
    int total_cost = 0;

    int current_node = start_node;
    path[path_length++] = current_node;
    visited[current_node] = 1;

    while (current_node != end_node)
    {
        int best_neighbor = -1;
        int min_edge_cost = INF;

        for (int neighbor = 0; neighbor < NUM_NODES; neighbor++)
        {
            if (graph[current_node][neighbor] != -1 && !visited[neighbor])
            {
                if (graph[current_node][neighbor] < min_edge_cost)
                {
                    min_edge_cost = graph[current_node][neighbor];
                    best_neighbor = neighbor;
                }
            }
        }

        if (best_neighbor == -1)
        {
            printf("   Stuck! No path found.\n");
            return;
        }

        total_cost += min_edge_cost;
        current_node = best_neighbor;
        path[path_length++] = current_node;
        visited[current_node] = 1;
    }

    print_path(path, path_length, total_cost);
}

int main()
{
    setup_graph();
    int start_node = 0; // 'A'
    int end_node = 5;   // 'F'

    printf("2. Hill Climbing Search\n");
    printf("Finding path from %c to %c...\n", index_to_node(start_node), index_to_node(end_node));
    hill_climbing_search(start_node, end_node);

    return 0;
}
