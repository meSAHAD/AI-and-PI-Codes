#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NUM_NODES 6
#define INF INT_MAX
#define MAX_PATH_LEN 10
#define MAX_CANDIDATES 50 

int graph[NUM_NODES][NUM_NODES];

typedef struct
{
    int nodes[MAX_PATH_LEN];
    int length;
    int cost;
} Path;

char index_to_node(int index) { return 'A' + index; }

void print_path_struct(Path *p)
{
    printf("   Path: ");
    for (int i = 0; i < p->length; i++)
    {
        printf("%c", index_to_node(p->nodes[i]));
        if (i < p->length - 1)
            printf(" -> ");
    }
    printf("\n   Cost: %d\n\n", p->cost);
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

int is_node_in_path(int node, Path *p)
{
    for (int i = 0; i < p->length; i++)
    {
        if (p->nodes[i] == node)
            return 1;
    }
    return 0;
}

int compare_paths(const void *a, const void *b)
{
    Path *pathA = (Path *)a;
    Path *pathB = (Path *)b;
    return (pathA->cost - pathB->cost);
}

void beam_search(int start_node, int end_node, int beam_width)
{
    Path *beam = malloc(beam_width * sizeof(Path));
    int beam_size = 1;

    beam[0].nodes[0] = start_node;
    beam[0].length = 1;
    beam[0].cost = 0;

    while (1)
    {
        Path candidates[MAX_CANDIDATES];
        int num_candidates = 0;

        for (int i = 0; i < beam_size; i++)
        {
            Path current_path = beam[i];
            int last_node = current_path.nodes[current_path.length - 1];

            if (last_node == end_node)
            {
                candidates[num_candidates++] = current_path;
                continue;
            }

            for (int neighbor = 0; neighbor < NUM_NODES; neighbor++)
            {
                if (graph[last_node][neighbor] != -1 && !is_node_in_path(neighbor, &current_path))
                {
                    Path new_path = current_path;
                    new_path.nodes[new_path.length++] = neighbor;
                    new_path.cost += graph[last_node][neighbor];
                    candidates[num_candidates++] = new_path;
                }
            }
        }

        if (num_candidates == 0)
        {
            printf("   No path found.\n");
            free(beam);
            return;
        }

        qsort(candidates, num_candidates, sizeof(Path), compare_paths);

        if (candidates[0].nodes[candidates[0].length - 1] == end_node)
        {
            print_path_struct(&candidates[0]);
            free(beam);
            return;
        }

        beam_size = (num_candidates < beam_width) ? num_candidates : beam_width;
        memcpy(beam, candidates, beam_size * sizeof(Path));
    }
}

int main()
{
    setup_graph();
    int start_node = 0; // 'A'
    int end_node = 5;   // 'F'
    int beam_width = 2;

    printf("3. Beam Search (width=%d)\n", beam_width);
    printf("Finding path from %c to %c...\n", index_to_node(start_node), index_to_node(end_node));
    beam_search(start_node, end_node, beam_width);

    return 0;
}
