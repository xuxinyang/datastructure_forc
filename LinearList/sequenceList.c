#include <stdio.h>
#include <stdlib.h>

#define OK         (1)
#define ERROR      (0)
#define TRUE       (1)
#define FALSE      (0)
#define MAXSIZE    (20)

typedef int ElemType;        // ElemType类型根据实际情况而定，这里假设为int
typedef int Status;
/* Structure Define */
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
}SQList;
/**
 * Status是函数的类型，其值是函数结果状态代码，如OK等
 * 初始条件：顺序线性表L已存在，1<=i<=Listlength(L)
 * 操作结果：用e返回L中第i个数据元素的值
 */
Status GetElem(SQList L, int i, ElemType *e)
{
    if (L.length == 0 || i < 1 || i > L.length)
    {
        return ERROR;
    }
    *e = L.data[i-1];
    return OK;
}
/**
 * 初始条件：顺序线性表L已存在，1<=i<=ListLength(L)
 * 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1
 */
Status ListInsert(SQList *L, int i, ElemType e)
{
    int k;
    if (L -> length == MAXSIZE)       // 顺序线性表已满
    {
        return ERROR;
    }
    if ((i < 1) || (i > (L->length)+1))   // i不在范围内
    {
        return ERROR;
    }
    if (i < L -> length)          // 插入的数据不在表尾
    {
        for (k = L->length-1; k >= i-1; k--)   // 将要插入位置后数据元素向后移一位 
        {
            L->data[k+1] = L->data[k];
        }
    }
    L->data[i-1] = e;    // 插入新元素
    L->length ++;
    return OK;
}

/**
 * 初始条件：顺序线性表L已存在，1<=i<=ListLength(L)
 * 操作结果：删除L的第i个数据元素，并用e返回其值，L的表长减1
 */
Status ListDelete(SQList *L, int i, ElemType *e)
{
    int k;
    if (L->length == 0)
    {
        return ERROR;
    }
    if (i < 1 || i > L->length)
    {
        return ERROR;
    }
    *e = L->data[i-1];
    if (i < L->length)
    {
        for (k = i; k < L->length; k++)      // 将删除位置后继元素前移
        {
            L->data[k-1] = L->data[k];
        }
    }
    L->length --;
    return OK;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
