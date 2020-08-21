#include <stdio.h>

#define MAXVEX (100)    // 最大顶点数
#define INFINITY (0xFF) // 用0xFF代表∞

typedef char VertexType; // 顶点类型
typedef int EdgeType;    // 边上的权值类型

typedef struct
{
    VertexType vex[MAXVEX];       // 顶点表
    EdgeType arc[MAXVEX][MAXVEX]; // 邻接矩阵，可看作边表
    int numVertexes, numEdges;    // 图中当前的顶点数和边数
} MGraph;

/* 建立无向网图的邻接矩阵表示 */
void CreateMGraph(MGraph *G)
{
    int i, j, k, w;
    printf("Please input number of vertexs and edges:\n");
    scanf("%d, %d", &G->numVertexes, &G->numEdges); // 输入顶点数和边数
    for (i = 0; i < G->numVertexes; i++)
    {
        scanf("%c", &G->vex[i]); // 输入顶点信息，建立顶点表
    }
    for (i = 0; i < G->numVertexes; i++)
    {
        for (j = 0; j < G->numVertexes; j++)
        {
            G->arc[i][j] = INFINITY; // 邻接矩阵初始化
        }
    }
    for (k = 0; k < G->numEdges; k++) // 读入numberEdges条边，建立邻接矩阵
    {
        printf("Input i, j and weight of Edge(vi, vj)\n");
        scanf("%d, %d, %d", &i, &j, &w); // 输入边（vi，vj）的权重
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j]; // 因为是无向图，矩阵对称
    }
}