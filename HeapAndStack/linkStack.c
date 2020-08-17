#include <stdio.h>
#include <stdlib.h>
#include "common.h"

typedef struct StackNode
{
    SElemType data;
    struct StackNode *next;
}StackNode, *LinkStackPtr;

typedef struct LinkStack
{
    LinkStackPtr top;
    int count;
}LinkStack;

/* 插入元素e为新的栈顶元素 */
Status LinkStackPush(LinkStack *S, SElemType e)
{
    LinkStackPtr sPtr = (LinkStackPtr)malloc(sizeof(StackNode));
    sPtr->data = e;
    sPtr->next = S->top;
    S->top = sPtr;
    S->count ++;
    return OK;
}

/* 栈中没有元素，则栈为空 */
Status LinkStackEmpty(LinkStack S)
{
    if(S.count == (int)0)
    {
        return ERROR;
    }
    else
    {
        return OK;
    }
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status LinkStackPop(LinkStack *S, SElemType *e)
{
    LinkStackPtr sPtr;
    if(LinkStackEmpty(*S))
        return ERROR;
    *e = S->top->data;
    sPtr = S->top;              // 将栈顶元素赋值给sPtr
    S->top = S->top->next;      // 使得栈顶指针下移一位，移向后一结点
    free(sPtr);
    S->count --;                // 释放结点p
    return OK;
}

int main(int argc, char const *argv[])
{
    printf("Hello World!");
    return 0;
}
