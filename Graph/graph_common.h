#include <stdio.h>
#include <stdlib.h>

#define TRUE (1)
#define FALSE (0)
#define MAXVEX (100)    // 最大顶点数
#define INFINITY (0xFF) // 用0xFF代表∞
#define MAX (20)
#define MAXSIZE (100)
#define OK (1)
#define ERROR (0)
#define MAXEDGE (15)

typedef char VertexType; // 顶点类型
typedef int EdgeType;    // 边上的权值类型
typedef int Boolean;     // Boolean是布尔类型，其值是TRUE或FALSE
typedef int Status;

Boolean visited[MAX];

/* 邻接矩阵结构定义 */
typedef struct
{
    VertexType vex[MAXVEX];       // 顶点表
    EdgeType arc[MAXVEX][MAXVEX]; // 邻接矩阵，可看作边表
    int numVertexes, numEdges;    // 图中当前的顶点数和边数
} MGraph;

/* 邻接链表结构定义 */
typedef struct EdgeNode // 边表结点
{
    int adjvex;            // 邻接点域，存储该顶点对应的下标
    EdgeType weight;       // 用于存储权值，对于非网图可以不需要
    struct EdgeNode *next; // 链域，指向下一个邻接点
} EdgeNode;

typedef struct VertexNode // 顶点表结点
{
    VertexType data;     // 顶点域，存储顶点信息
    EdgeNode *firstEdge; // 边表头指针
} VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList AdjList;
    int numVertexes, numEdges; // 图中当前顶点数和边数
} GraphAdjList;

/* 对边集数组Edge结构的定义 */
typedef struct
{
    int begin;
    int end;
    int weight;
}Edge;


typedef struct
{
    int data[MAXSIZE];
    int front; /* 头指针 */
    int rear;  /* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
} Queue;