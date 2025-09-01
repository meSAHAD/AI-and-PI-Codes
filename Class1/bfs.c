#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX], visited[MAX], n;

void BFS(int start) {
    int queue[MAX], front = -1, rear = -1;
    visited[start] = 1;
    queue[++rear] = start;

    while (front != rear) {
        int vertex = queue[++front];
        printf("%d ", vertex);

        for (int i = 0; i < n; i++) {
            if (graph[vertex][i] == 1 && !visited[i]) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
}

int main() {
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    for (int i = 0; i < n; i++) visited[i] = 0;

    printf("BFS Traversal starting from vertex 0:\n");
    BFS(0);

    return 0;
}

