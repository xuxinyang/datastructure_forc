#include <stdlib.h>
#include "common.h"

typedef struct QNode            // 结点结构
{
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct                  // 队列的链表结构
{
    QueuePtr front, rear;       // 队头、队尾操作
}LinkQueue;

/* 插入元素e为Q的新的队尾元素 */
Status EntryLinkQueue(LinkQueue *Q, QElemType e)
{
    QueuePtr sPtr = (QueuePtr)malloc(sizeof(QNode));
    if (!sPtr)
    {
        exit(OVERFLOW);
    }
    sPtr->data = e;
    sPtr->next = NULL;
    Q->rear->next = sPtr;       // 把拥有元素e新结点s赋值给原队尾结点的后继
    Q->rear = sPtr;             // 把当前的s设置为队尾结点，rear指向s
    return OK;
}

/* 若队列不空，则删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR */
Status DeleteLinkQueue(LinkQueue *Q, QElemType *e)
{
    QueuePtr ptr;
    if (Q->front == Q->rear)
    {
        return ERROR;
    }
    else
    {
        ptr = Q->front->next;       // 将要删除的队头结点暂存给ptr
        *e = ptr->data;             // 将要删除的队头结点赋值给e
        Q->front->next = ptr->next; //将原队头结点后继p->next赋值给头结点后继
    }

    if (Q->rear == ptr)             // 若队头是队尾，则删除后将rear指向头结点
    {
        Q->rear = Q->front;
    }
    free(ptr);
    return OK;
}