#include <stdio.h>
#include <stdlib.h>
#include "common.h"

typedef struct
{
    SElemType data[MAXSIZE];
    int top;
}SqStack;

/* 两栈共享空间结构 */
typedef struct
{
    SElemType data[MAXSIZE];
    int top1;       // 栈1栈顶指针
    int top2;       // 栈2栈顶指针
}SqDoubleStack;

/* 插入元素e为新的栈顶元素 */
Status StackPush(SqStack *S, SElemType e)
{
    if (S->top == MAXSIZE-1)
    {
        return ERROR;
    }
    S->top ++;                  // 栈顶指针加1
    S->data[S->top] = e;        // 将新插入元素赋值给栈顶空间
    return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status StackPop(SqStack *S, SElemType *e)
{
    if (S->top == -1)
    {
        return ERROR;
    }
    *e = S->data[S->top];       // 将要删除的栈顶元素赋值给e
    S->top --;                  // 栈顶指针减1
    return OK;
}

/* 共享栈插入元素e为新的栈顶元素 */
Status DoubleStackPush(SqDoubleStack *S, SElemType e, int stackNumber)
{
    if (S->top1+1 == S->top2)   // 栈已满，不能再psh新元素了
    {
        return ERROR;
    }
    if (stackNumber == 1)
    {
        S->data[++S->top1] = e; // 栈1有元素进栈，先将top1+1，在给数组元素赋值
    }
    else if (stackNumber == 2)
    {
        S->data[--S->top2] = e; // 栈2有元素进栈，先将top2-1，在给数组元素赋值
    }
    else
    {
        /* Do nothing */
    }
    return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status DoubleStackPop(SqDoubleStack *S, SElemType *e, int stackNumber)
{
    if (stackNumber == 1)
    {
        if (S->top1 == -1)
        {
            return ERROR;              // 说明栈1为空
        }
        else
        {
            *e = S->data[S->top1--];   // 将栈1的栈顶元素取出
        }
    }
    else if (stackNumber == 2)
    {
        if (S->top2 == MAXSIZE)
        {
            return ERROR;              // 说明栈2为空
        }
        else
        {
            *e = S->data[S->top2++];   // 将栈2的栈顶元素取出
        }
    }
    return OK;
}