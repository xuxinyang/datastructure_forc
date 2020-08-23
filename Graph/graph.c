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

/* 初始化一个空队列Q */
Status InitQueue(Queue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty(Queue Q)
{
    if (Q.front == Q.rear) /* 队列空的标志 */
        return TRUE;
    else
        return FALSE;
}

/* 若队列未满，则插入元素e为Q新的队尾元素 */
Status EnQueue(Queue *Q, int e)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front) /* 队列满的判断 */
        return ERROR;
    Q->data[Q->rear] = e;              /* 将元素e赋值给队尾 */
    Q->rear = (Q->rear + 1) % MAXSIZE; /* rear指针向后移一位置， */
                                       /* 若到最后则转到数组头部 */
    return OK;
}

/* 若队列不空，则删除Q中队头元素，用e返回其值 */
Status DeQueue(Queue *Q, int *e)
{
    if (Q->front == Q->rear) /* 队列空的判断 */
        return ERROR;
    *e = Q->data[Q->front];              /* 将队头元素赋值给e */
    Q->front = (Q->front + 1) % MAXSIZE; /* front指针向后移一位置， */
                                         /* 若到最后则转到数组头部 */
    return OK;
}

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

void CreateALGraph(GraphAdjList *G)
{
    int i, j, k;
    EdgeNode *e;
    printf("Please input the number of vertexs and edges:\n");
    scanf("%d, %d", &G->numVertexes, &G->numEdges); // 输入顶点数和边数
    for (i = 0; i < G->numVertexes; i++)            // 输入顶点信息，建立顶点表
    {
        scanf("%c", &G->AdjList[i].data); // 输入顶点信息
        G->AdjList[i].firstEdge = NULL;   // 将边表置为空表
    }
    for (k = 0; k < G->numEdges; k++) // 建立边表
    {
        printf("Please input index of edge(vi, vj):\n");
        scanf("%d, %d", &i, &j);                  // 输入边（vi，vj）上的顶点序号
        e = (EdgeNode *)malloc(sizeof(EdgeNode)); // 向内存申请空间，生成边表结点
        e->adjvex = j;                            // 邻接序号为j
        e->next = G->AdjList[i].firstEdge;        // 将e指针指向当前顶点指向的结点
        G->AdjList[i].firstEdge = e;              // 将当前顶点的指针指向e
        e = (EdgeNode *)malloc(sizeof(EdgeNode)); // 生成边表结点
        e->adjvex = i;                            // 邻接序号为i
        e->next = G->AdjList[j].firstEdge;        // 将e指针指向当前顶点指向的结点
        G->AdjList[j].firstEdge = e;              // 将当前顶点的指针指向e
    }
}

/* 邻接矩阵的深度优先递归算法 */
void DFSMatrix(MGraph G, int i)
{
    int j;
    visited[i] = TRUE;
    printf("%c", G.vex[i]);
    for (j = 0; j < G.numVertexes; j++)
    {
        if (G.arc[i][j] == 1 && !visited[j])
        {
            DFSMatrix(G, j);
        }
    }
}

/* 邻接矩阵的深度遍历操作 */
void DFSMatrixTraverse(MGraph G)
{
    int i;
    for (i = 0; i < G.numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    for (i = 0; i < G.numVertexes; i++)
    {
        if (!visited[i]) // 对未访问过的结点调用DFS，若是连通图，只会执行一次
        {
            DFSMatrix(G, i);
        }
    }
}

/* 邻接表的深度优先递归算法 */
void DFSList(GraphAdjList *GL, int i)
{
    EdgeNode *p;
    visited[i] = TRUE;
    printf("%c", GL->AdjList[i].data);
    p = GL->AdjList[i].firstEdge;
    while (p)
    {
        if (!visited[p->adjvex])
            DFSList(GL, p->adjvex);
        p = p->next;
    }
}

/* 邻接表的深度遍历操作 */
void DFSListTraverse(GraphAdjList *GL)
{
    int i;
    for (i = 0; i < GL->numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    for (i = 0; i < GL->numVertexes; i++)
    {
        if (!visited[i])
        {
            DFSList(GL, i);
        }
    }
}

/* 邻接矩阵的广度优先遍历算法 */
void BFSMatrixTrverse(MGraph G)
{
    int i, j;
    Queue Q;
    for (i = 0; i < G.numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    InitQueue(&Q);                      // 初始化一辅助用的队列
    for (i = 0; i < G.numVertexes; i++) // 对每一个顶点做循环
    {
        if (!visited[i]) // 若是未访问过九处理
        {
            visited[i] = TRUE;      // 设置当前结点访问过
            printf("%c", G.vex[i]); // 打印结点，也可以进行其他操作
            EnQueue(&Q, i);         // 将此顶点入队
            while (!QueueEmpty(Q))  // 若当前队列不空
            {
                DeQueue(&Q, &i); // 将队中元素出队，赋值给i
                for (j = 0; j < G.numVertexes; j++)
                {
                    /* 判断其他顶点若与当前顶点存在边且未访问过 */
                    if (G.arc[i][j] == 1 && !visited[j])
                    {
                        visited[j] = TRUE;      // 将找到的此顶点标记为已访问
                        printf("%c", G.vex[j]); // 打印结点
                        EnQueue(&Q, j);         // 将找到的此顶点入队
                    }
                }
            }
        }
    }
}

/* 邻接表的广度遍历算法 */
void BFSListTraverse(GraphAdjList *GL)
{
    int i;
    EdgeNode *p;
    Queue Q;
    for (i = 0; i < GL->numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    InitQueue(&Q);
    for (i = 0; i < GL->numVertexes; i++)
    {
        if (!visited[i])
        {
            visited[i] = TRUE;
            printf("%c", GL->AdjList[i].data);
            EnQueue(&Q, i);
            while (!QueueEmpty(Q))
            {
                DeQueue(&Q, &i);
                p = GL->AdjList[i].firstEdge; // 找到当前顶点边表链表头指针
                while (p)
                {
                    if (!visited[p->adjvex])
                    {
                        visited[p->adjvex] = TRUE;
                        printf("%c", GL->AdjList[p->adjvex].data);
                        EnQueue(&Q, p->adjvex);
                    }
                    p = p->next;
                }
            }
        }
    }
}

/* Prim算法生成最小生成树 */
void MiniSpanTree_Prim(MGraph G)
{
    int min, i, j, k;
    int adjvex[MAXVEX];  // 保存相关顶点下标
    int lowcost[MAXVEX]; // 保存相关顶点间边的权值
    lowcost[0] = 0;      // 初始化第一个权值为0，即v0加入生成树，lowcost的值为0，在这里就是此下标的顶点已加入生成树
    adjvex[0] = 0;       // 初始化第一个顶点下标为0

    for (i = 1; i < G.numVertexes; i++) // 循环除了下标为0以外的全部顶点
    {
        lowcost[i] = G.arc[0][i]; // 将v0顶点与之有边的权值存入数组
        adjvex[i] = 0;            // 初始化都为v0的下标
    }
    for (i = 1; i < G.numVertexes; i++)
    {
        min = INFINITY; // 初始化最小值为65535
        j = 1, k = 0;
        while (j < G.numVertexes) // 循环全部顶点
        {
            if (lowcost[j] != 0 && lowcost[j] < min) // 如果权值不为0且权值小于min
            {
                min = lowcost[j]; // 则让当前权值成为最小值
                k = j;            // 将当前最小值的下标存入k
            }
            j++;
        }
        printf("(%d, %d)", adjvex[k], k);   // 打印当前顶点边中权值最小的边
        lowcost[k] = 0;                     // 将当前顶点的权值设置为0，表示此顶点已经完成任务
        for (j = 1; j < G.numVertexes; j++) // 循环所有顶点
        {
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
            {
                /* 若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值 */
                lowcost[j] = G.arc[k][j]; // 将较小权值存入lowcost
                adjvex[j] = k;            // 将下标为k的顶点存入adjvex
            }
        }
    }
}

/* 查找连线顶点的尾部下标 */
int Find(int *parent, int f)
{
    while (parent[f] > 0)
    {
        f = parent[f];
    }
    return f;
}

/* Kruskal算法生成最小生成树 */
void MiniSpanTree_Kruskal(MGraph G)
{
    int i, n, m;
    Edge edges[MAXEDGE];    // 定义边集数组
    int parent[MAXVEX];     // 定义一数组用来判断边与边之间是否形成环路
    /* 此处省略将邻接矩阵G转化为边集数组edges并按权由小到大排序的代码 */
    for (i = 0; i < G.numVertexes; i++)
    {
        parent[i] = 0;  // 初始化数组值为0
    }
    for (i = 0; i < G.numEdges; i++)    // 循环每一条边
    {
        n = Find(parent, edges[i].begin);
        m = Find(parent, edges[i].end);
        if (n != m) // 假如n与m不相等，说明此边没有与现有生成树形成环路
        {
            parent[n] = m;  // 将此边的结尾顶点放入下标为起点的parent中，表示此定调已经在生成树集合中
            printf("(%d, %d) %d", edges[i].begin, edges[i].end, edges[i].weight);
        }
        
    }
    
}