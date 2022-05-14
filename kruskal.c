#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

unsigned int **predef_graph(unsigned int **graph)
{
    unsigned int pregraph[6][6] = {
        {0, 4, 4, 0, 0, 0},
        {4, 0, 2, 0, 0, 0},
        {4, 2, 0, 3, 2, 4},
        {0, 0, 3, 0, 0, 3},
        {0, 0, 2, 0, 0, 3},
        {0, 0, 4, 3, 3, 0}};
    int i = 0, j = 0;
    graph = malloc(6 * sizeof(unsigned int *));
    for (i = 0; i < 6; i++)
    {
        graph[i] = malloc(6 * sizeof(unsigned int));
        for (j = 0; j < 6; j++)
        {
            graph[i][j] = pregraph[i][j];
        }
    }
    return graph;
}

unsigned int **input_graph(unsigned int **graph, int vertices)
{
    int i = 0, j = 0;
    unsigned int weight;
    printf("Enter weight data for %d nodes[0 if nodes are not connected]\n", vertices);
    graph = malloc(vertices * sizeof(unsigned int *));
    for (i = 0; i < vertices; i++)
    {
        graph[i] = malloc(vertices * sizeof(unsigned int));
        graph[i][i] = 0;
    }
    for (i = 0; i < vertices; i++)
    {
        for (j = i + 1; j < vertices; j++)
        {
            printf("Enter weight from node %c to %c> ", 'A' + i, 'A' + j);
            scanf("%d", &weight);
            graph[i][j] = weight;
            graph[j][i] = weight;
        }
    }
    return graph;
}

void print_graph(unsigned int **graph, int vertices)
{
    int i = 0, j = 0;
    printf("  ");
    for (j = 0; j < vertices; j++)
    {
        printf("%*c ", 3, 'A' + j);
    }
    printf("\n");
    for (i = 0; i < vertices; i++)
    {
        printf("%c ", 'A' + i);
        for (j = 0; j < vertices; j++)
        {
            printf("%*d ", 3, graph[i][j]);
        }
        printf("\n");
    }
}

int find_tree_root(int node, int *connected_nodes)
{
    while (connected_nodes[node] != -1)
    {
        node = connected_nodes[node];
    }
    return node;
}

int different_trees(int root1, int root2, int *connected_nodes)
{
    if (root1 != root2)
    {
        connected_nodes[root2] = root1;
        return 1;
    }
    return 0;
}

void kruskal_spanning_tree(unsigned int **graph, int vertices)
{
    int edges;
    int *connected_nodes;
    unsigned int minimum_weight = UINT_MAX, total_weight = 0;
    int from_node, to_node;
    int i = 0, j = 0, u = 0, v = 0;
    connected_nodes = malloc(vertices * sizeof(int));
    for (i = 0; i < vertices; i++)
    {
        connected_nodes[i] = -1;
    }
    edges = 0;
    printf("Minimum spanning tree: \n");
    printf("Edge\tWeight\n");
    while (edges < vertices - 1)
    {
        minimum_weight = UINT_MAX;
        for (i = 0; i < vertices; i++)
        {
            for (j = 0; j < vertices; j++)
            {
                if (graph[i][j] < minimum_weight && graph[i][j] != 0)
                {
                    minimum_weight = graph[i][j];
                    from_node = i;
                    u = i;
                    to_node = j;
                    v = j;
                }
            }
        }
        u = find_tree_root(u, connected_nodes);
        v = find_tree_root(v, connected_nodes);
        if (different_trees(u, v, connected_nodes))
        {
            printf("%c - %c\t%*d\n", 'A' + from_node, 'A' + to_node, 3, graph[from_node][to_node]);
            total_weight = total_weight + graph[from_node][to_node];
            edges++;
        }
        graph[from_node][to_node] = UINT_MAX;
        graph[to_node][from_node] = UINT_MAX;
    }
    printf("Total weight of the minimum spanning tree is: %d\n", total_weight);
}
void main(int argc, char *argv[])
{
    unsigned int **graph;
    char choice;
    int i = 0, j = 0, weight;
    int vertices;
    printf("Use pre-defined graph? [Y/y]> ");
    scanf("%c", &choice);
    if (choice != 'y' && choice != 'Y')
    {
        printf("Enter number of vertices> ");
        scanf("%d", &vertices);
        graph = input_graph(graph, vertices);
    }
    else
    {
        vertices = 6;
        graph = predef_graph(graph);
    }
    print_graph(graph, vertices);
    kruskal_spanning_tree(graph, vertices);
}