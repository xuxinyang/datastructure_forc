#include <stdio.h>

#define MAXSIZE (10)
#define TRUE (1)
#define FALSE (0)

typedef int Status;
typedef struct
{
    int r[MAXSIZE + 1]; // 用于存储要排序的数组，r[0]用作哨兵或临时变量
    int length;         // 用于记录顺序表的长度
} SqList;

/* 交换L中数组r的下标为i和j的值 */
void swap(SqList *L, int i, int j)
{
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

/* 对顺序表L做交换排序（冒泡排序初级版） */
void BubbleSortPrime(SqList *L)
{
    int i, j;
    for (i = 1; i < L->length; i++)
    {
        for (j = i + 1; j < L->length; j++)
        {
            if (L->r[i] > L->r[j])
            {
                swap(L, i, j); // 交换L->r[i]与L->r[j]的值
            }
        }
    }
}

/* 对顺序表L做冒泡排序 */
void BubbleSort(SqList *L)
{
    int i, j;
    for (i = 1; i < L->length; i++)
    {
        for (j = L->length - 1; j >= i; j--) // 注意j是从后向前循环
        {
            if (L->r[j] > L->r[j + 1]) // 若前者大于后者
            {
                swap(L, j, j + 1); // 交换值
            }
        }
    }
}

/* 对顺序表L做改进冒泡算法 */
void BubbleSortSenior(SqList *L)
{
    int i, j;
    Status flag = TRUE;                     // flag用来作为标记
    for (i = 1; i < L->length && flag; i++) // 若flag为false则退出循环
    {
        flag = FALSE; // 初始为false
        for (j = L->length - 1; j >= i; j--)
        {
            if (L->r[j] > L->r[j + 1])
            {
                swap(L, j, j + 1); // 交换L->[j]与L->[j+1]的值
                flag = TRUE;       // 如果有数据交换，则flag为true
            }
        }
    }
}

/* 对顺序表L做简单选择排序 */
void SelectSort(SqList *L)
{
    int i, j, min;
    for (i = 1; i < L->length; i++)
    {
        min = i;                            // 将当前下标定义为最小值下标
        for (j = i + 1; j < L->length; j++) // 循环之后的数据
        {
            if (L->r[min] > L->r[j]) // 如果有小于当前最小值的关键字
            {
                min = j; // 将此关键字的下标赋值给min
            }
            if (i != min) // 若min不等于i，说明找到最小值，交换
            {
                swap(L, i, min); // 交换值
            }
        }
    }
}

/* 对顺序表L做直接插入排序 */
void InsertSort(SqList *L)
{
    int i, j;
    for (i = 2; i <= L->length; i++)
    {
        if (L->r[i] < L->r[i - 1]) // 需要将L->r[i]插入有序子表
        {
            L->r[0] = L->r[i]; // 设置哨兵
            for (j = i - 1; L->r[j] > L->r[0]; j--)
            {
                L->r[j + 1] = L->r[j]; // 记录后移
            }
            L->r[j + 1] = L->r[0]; // 插入到正确位置
        }
    }
}

/* 对顺序表L做希尔排序 */
void ShellSort(SqList *L)
{
    int i, j;
    int increment = L->length;
    do
    {
        increment = increment / 3 + 1; // 增量序列
        for (i = increment + 1; i < L->length; i++)
        {
            if (L->r[i] < L->r[i - increment])
            {
                /* 需将L->r[i]插入有序增量子表 */
                L->r[0] = L->r[i]; // 暂存在L->r[0]
                for (j = i - increment; j > 0 && L->r[0] < L->r[j]; j -= increment)
                {
                    L->r[j + increment] = L->r[j]; // 记录后移，查找插入位置
                }
                L->r[j + increment] = L->r[0]; // 插入
            }
        }

    } while (increment > 1);
}

/**
 * 已知L->r[s..m]中记录的关键字除了L->r[s]之外均满足堆的定义
 * 本函数调整L->r[s]的关键字，使L->r[s..m]成为一个大顶堆
 */

void HeapAdjust(SqList *L, int s, int m)
{
    int temp, j;
    temp = L->r[s];
    for (j = 2 * s; j <= m; j *= 2) // 沿关键字较大的孩子结点向下筛选
    {
        if (j < m && L->r[j] < L->[j + 1])
        {
            ++j; // j为关键字中较大的记录的下标
        }
        if (temp >= L->r[j])
        {
            break; // rc应插入在位置s上
        }
        L->r[s] = L->r[j];
        s = j;
    }
    L->r[s] = temp; // 插入
}

/* 对顺序表L进行堆排序 */
void HeapSort(SqList *L)
{
    int i;
    for (i = L->length / 2; i > 0; i--) // 把L中的r构建成一个大顶堆
    {
        HeapAdjust(L, i, L->length);
    }
    for (i = L->length; i > 1; i--)
    {
        swap(L, 1, i); // 将堆顶记录和当前未经排序子序列的最后一个记录交换
        HeapAdjust(L, 1, i - 1); // 将L->r[1..i-1]重新调整为大顶堆
    }
}