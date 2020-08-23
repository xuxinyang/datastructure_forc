#include <stdio.h>
#include "graph_common.h"

typedef int Pathmatrix[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

/* Floyd算法，求网图G中各顶点v到其余顶点w最短路径P[v][w]及带权长度D[v][w] */
void ShortestPath_Floyd(MGraph G, Pathmatrix *P, ShortPathTable *D)
{
    int v, w, k;
    for (v = 0; v < G.numVertexes; ++v)
    {
        for (w = 0; w < G.numVertexes; ++w)
        {
            (*D)[v][w] = G.arc[v][w]; // D[v][w]值即为对应点间的权值
            (*P)[v][w] = w;           // 初始化P
        }
    }
    for (k = 0; k < G.numVertexes; ++k)
    {
        for (v = 0; v < G.numVertexes; ++v)
        {
            for (w = 0; w < G.numVertexes; ++w)
            {
                if ((*D)[v][w] > (*D)[v][k] + (*D)[k][w])
                {
                    /* 如果经过下标为k顶点路径比原两点间路径更短 */
                    /* 将当前两点权值设为更小的一个 */
                    (*D)[v][w] = (*D)[v][k] + (*D)[k][w];
                    (*P)[v][w] = (*P)[v][k]; // 路径设置经过下标为k的顶点
                }
            }
        }
    }
}

