#include "common.h"

/* 循环队列的顺序存储结构 */
typedef struct
{
    QElemType data[MAXSIZE];
    int front;              // 头指针
    int rear;               // 尾指针
}SqQueue;

/* 初始化一个空队列 */
Status InitQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

/* 循环队列求队列长度 */
int QueueLength(SqQueue Q)
{
    return ((Q.rear-Q.front+MAXSIZE)%MAXSIZE);
}

/* 循环队列的入队操作代码如下 */
Status EntryQueue(SqQueue *Q, QElemType e)
{
    if ((Q->rear+1)%MAXSIZE == Q->front)    // 队列满的标志
    {
        return ERROR;
    }
    else
    {
        Q->data[Q->rear] = e;               // 将元素e赋值给队尾
        Q->rear = (Q->rear+1)%MAXSIZE;      // rear指针后移一位，若到最后，则转到头部
        return OK;
    }
}

/* 若队列不空，则删除Q中队头元素，用e返回其值 */
Status DeleteQueue(SqQueue *Q, QElemType *e)
{
    if (Q->front == Q->rear)                // 队列空的判断
    {
        return ERROR;
    }
    else
    {
        *e = Q->data[Q->front];             // 将队头元素赋值给e
        Q->front = (Q->front+1)%MAXSIZE;    // front指针向后移动一位置，若到最后，则转到数组头部
        return OK;
    }
    
}