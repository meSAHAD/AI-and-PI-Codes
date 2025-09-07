#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <time.h>

#define NUM_NODES 6
#define INF INT_MAX

int graph[NUM_NODES][NUM_NODES];

char index_to_node(int index) { return 'A' + index; }

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
    graph[1][0] = 5;
    graph[0][2] = 10;
    graph[2][0] = 10;
    graph[0][3] = 6;
    graph[3][0] = 6;
    graph[1][2] = 3;
    graph[2][1] = 3;
    graph[1][4] = 8;
    graph[4][1] = 8;
    graph[2][3] = 7;
    graph[3][2] = 7;
    graph[2][4] = 4;
    graph[4][2] = 4;
    graph[2][5] = 9;
    graph[5][2] = 9;
    graph[3][5] = 12;
    graph[5][3] = 12;
    graph[4][5] = 2;
    graph[5][4] = 2;
}

int calculate_cost(int *path, int length)
{
    int cost = 0;
    for (int i = 0; i < length - 1; i++)
    {
        int u = path[i];
        int v = path[i + 1];
        if (graph[u][v] == -1)
            return INF; // Invalid path
        cost += graph[u][v];
    }
    return cost;
}

void get_initial_path(int start, int end, int *path)
{
    int intermediate[NUM_NODES - 2];
    int count = 0;
    for (int i = 0; i < NUM_NODES; i++)
    {
        if (i != start && i != end)
        {
            intermediate[count++] = i;
        }
    }

    path[0] = start;
    memcpy(path + 1, intermediate, (NUM_NODES - 2) * sizeof(int));
    path[NUM_NODES - 1] = end;

    // A -> D -> C -> B -> E -> F
    path[0] = 0;
    path[1] = 3;
    path[2] = 2;
    path[3] = 1;
    path[4] = 4;
    path[5] = 5;
}

void simulated_annealing(int start, int end)
{
    srand(time(NULL));

    int current_path[NUM_NODES];
    int best_path[NUM_NODES];

    get_initial_path(start, end, current_path);
    int current_cost = calculate_cost(current_path, NUM_NODES);

    memcpy(best_path, current_path, NUM_NODES * sizeof(int));
    int best_cost = current_cost;

    double temp = 10000.0;
    double cooling_rate = 0.9995;

    while (temp > 1)
    {
        int new_path[NUM_NODES];
        memcpy(new_path, current_path, NUM_NODES * sizeof(int));

        int i = 1 + rand() % (NUM_NODES - 2);
        int j = 1 + rand() % (NUM_NODES - 2);
        int temp_node = new_path[i];
        new_path[i] = new_path[j];
        new_path[j] = temp_node;

        int new_cost = calculate_cost(new_path, NUM_NODES);

        if (new_cost == INF)
            continue; 

        if (new_cost < current_cost || exp((current_cost - new_cost) / temp) > (double)rand() / RAND_MAX)
        {
            memcpy(current_path, new_path, NUM_NODES * sizeof(int));
            current_cost = new_cost;
        }

        if (current_cost < best_cost)
        {
            best_cost = current_cost;
            memcpy(best_path, current_path, NUM_NODES * sizeof(int));
        }

        temp *= cooling_rate;
    }
    print_path(best_path, NUM_NODES, best_cost);
}

int main()
{
    setup_graph();
    int start_node = 0; // 'A'
    int end_node = 5;   // 'F'

    printf("4. Simulated Annealing Search\n");
    printf("Finding path from %c to %c...\n", index_to_node(start_node), index_to_node(end_node));
    simulated_annealing(start_node, end_node);

    return 0;
}
