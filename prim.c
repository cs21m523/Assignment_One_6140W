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

void prim_spanning_tree(unsigned int **graph, int vertices)
{
    int edges;
    bool *selected_nodes;
    unsigned int minimum_weight = UINT_MAX, total_weight = 0;
    int from_node, to_node;
    int i = 0, j = 0;
    selected_nodes = malloc(vertices * sizeof(bool));
    memset(selected_nodes, false, sizeof(selected_nodes));
    edges = 0;
    selected_nodes[0] = true;
    printf("Minimum spanning tree: \n");
    printf("Edge\tWeight\n");
    while (edges < vertices - 1)
    {
        minimum_weight = UINT_MAX;
        from_node = 0;
        to_node = 0;
        for (i = 0; i < vertices; i++)
        {
            if (selected_nodes[i])
            {
                for (j = 0; j < vertices; j++)
                {
                    if (!selected_nodes[j] && graph[i][j])
                    {
                        if (minimum_weight > graph[i][j])
                        {
                            minimum_weight = graph[i][j];
                            from_node = i;
                            to_node = j;
                        }
                    }
                }
            }
        }
        printf("%c - %c\t%*d\n", 'A' + from_node, 'A' + to_node, 3, graph[from_node][to_node]);
        total_weight = total_weight + graph[from_node][to_node];
        selected_nodes[to_node] = true;
        edges++;
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
    prim_spanning_tree(graph, vertices);
}