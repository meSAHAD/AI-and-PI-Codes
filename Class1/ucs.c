#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int graph[MAX][MAX], n;
int visited[MAX];

typedef struct
{
    int vertex;
    int cost;
} Node;

Node pq[MAX];
int pqSize = 0;

// Priority Queue helpers
void push(int v, int c)
{
    pq[pqSize].vertex = v;
    pq[pqSize].cost = c;
    pqSize++;
    // bubble up
    for (int i = pqSize - 1; i > 0; i--)
    {
        if (pq[i].cost < pq[i - 1].cost)
        {
            Node temp = pq[i];
            pq[i] = pq[i - 1];
            pq[i - 1] = temp;
        }
    }
}

Node pop()
{
    Node top = pq[0];
    for (int i = 0; i < pqSize - 1; i++)
    {
        pq[i] = pq[i + 1];
    }
    pqSize--;
    return top;
}

int isEmpty()
{
    return pqSize == 0;
}

void UCS(int start, int target)
{
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    push(start, 0);

    while (!isEmpty())
    {
        Node current = pop();
        int v = current.vertex;
        int c = current.cost;

        if (visited[v])
            continue;
        visited[v] = 1;

        printf("Visited %d (cost=%d)\n", v, c);

        if (v == target)
        {
            printf("Target %d reached with cost %d\n", v, c);
            return;
        }

        for (int i = 0; i < n; i++)
        {
            if (graph[v][i] == 1 && !visited[i])
            {
                push(i, c + 1); // uniform edge cost = 1
            }
        }
    }
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

    printf("Uniform-Cost Search starting from 0:\n");
    UCS(start, target);

    return 0;
}
