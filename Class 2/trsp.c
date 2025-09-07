#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void find_permutations(int *nodes, int l, int r, int start_node, int end_node, int *best_path, int *min_cost)
{
    if (l == r)
    {
        int current_path[NUM_NODES];
        current_path[0] = start_node;
        for (int i = 0; i <= r; i++)
        {
            current_path[i + 1] = nodes[i];
        }
        current_path[r + 2] = end_node;

        int current_cost = 0;
        int possible = 1;

        for (int i = 0; i < NUM_NODES - 1; i++)
        {
            int u = current_path[i];
            int v = current_path[i + 1];
            if (graph[u][v] != -1)
            {
                current_cost += graph[u][v];
            }
            else
            {
                possible = 0;
                break;
            }
        }

        if (possible && current_cost < *min_cost)
        {
            *min_cost = current_cost;
            memcpy(best_path, current_path, NUM_NODES * sizeof(int));
        }
        return;
    }

    for (int i = l; i <= r; i++)
    {
        swap(&nodes[l], &nodes[i]);
        find_permutations(nodes, l + 1, r, start_node, end_node, best_path, min_cost);
        swap(&nodes[l], &nodes[i]); 
    }
}

int main()
{
    setup_graph();
    int start_node = 0; // 'A'
    int end_node = 5;   // 'F'

    printf("1. Traveling Salesman (Brute-Force Adaptation)\n");
    printf("Finding path from %c to %c...\n", index_to_node(start_node), index_to_node(end_node));

    int intermediate_nodes[NUM_NODES - 2];
    int count = 0;
    for (int i = 0; i < NUM_NODES; i++)
    {
        if (i != start_node && i != end_node)
        {
            intermediate_nodes[count++] = i;
        }
    }

    int best_path[NUM_NODES];
    int min_cost = INF;

    find_permutations(intermediate_nodes, 0, count - 1, start_node, end_node, best_path, &min_cost);

    if (min_cost != INF)
    {
        print_path(best_path, NUM_NODES, min_cost);
    }
    else
    {
        printf("No valid path found that visits all nodes.\n");
    }

    return 0;
}
