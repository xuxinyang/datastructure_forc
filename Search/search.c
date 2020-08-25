#include <stdio.h>
#include <stdlib.h>

#define TRUE (1)
#define FALSE (0)

typedef int Status;
/* 二叉树的二叉链表结点结构定义 */
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/* 顺序查找，a为数组，n为要查找的数组个数，key为要查找的关键字 */
int Sequential_Search(int *a, int n, int key)
{
    int i;

    for (i = 1; i <= n; i++)
    {
        if (a[i] == key)
        {
            return i;
        }
    }
    return 0;
}

/* 有哨兵顺序查找 */
int Sequential_Search2(int *a, int n, int key)
{
    int i;
    a[0] = key; // 设置a[0]为关键字值，我们称之为“哨兵”
    i = n;      // 循环从数组尾部开始
    while (a[i] != key)
    {
        i--;
    }
    return i; // 返回0则说明查找失败
}

/* 折半查找 */
int Binary_Search(int *a, int n, int key)
{
    int low, high, mid;
    low = 1;
    high = n;
    while (low <= high)
    {
        mid = (low + mid) / 2;
        /* mid = low + (high-low)*(key-a[low])/(a[high]-a[low]) --> 插值 */
        if (key < a[mid])
        {
            high = mid - 1;
        }
        else if (key > a[mid])
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return 0;
}

/* 斐波那契查找 */
static const int F[10] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
int Fibonacci_Search(int *a, int n, int key)
{
    int low, high, mid, i, k;
    low = 1;  // 定义最低下标为记录首位
    high = n; // 定义最高下标为记录末位
    k = 0;
    while (n > F[k] - 1) // 计算n位于斐波那契数列的位置
    {
        k++;
    }
    for (i = n; i < F[k] - 1; i++) // 将不满的数值补全
    {
        a[i] = a[n];
    }
    while (low < high)
    {
        mid = low + F[k - 1] - 1; // 计算当前分割的下标
        if (key < a[mid])         // 若查找记录小于当前分割记录
        {
            high = mid - 1; // 最高下标调整到分割下标mid-1处
            k = k - 1;      // 斐波那契数列下标减1位
        }
        else if (key > a[mid]) // 若查找记录大于当前分割记录
        {
            low = mid + 1; // 最低下标调整到分割下标mid+1处
            k = k - 2;     // 斐波那契数列下标减两位
        }
        else
        {
            if (mid <= n)
            {
                return mid; // 若相等则说明mid即为查找到的位置
            }
            else
            {
                return n; // 若mid>n说明是补全数值，返回n
            }
        }
    }
    return n;
}

/**
 * 递归查找二叉排序树T中是否存在key
 * 指针f指向T的双亲，其初始调用值为NULL
 * 若查找成功，则指针p指向该数据元素结点，并返回TRUE
 * 否则指针p指向查找路径上访问的最后一个结点并返回FALSE
 */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
    if (!T) // 查找不成功
    {
        *p = f;
        return FALSE;
    }
    else if (key == T->data) // 查找成功
    {
        *p = T;
        return TRUE;
    }
    else if (key < T->data)
    {
        return SearchBST(T->lchild, key, T, p); // 在左子树继续查找
    }
    else
    {
        return SearchBST(T->rchild, key, T, p);
    }
}

/**
 * 当二叉排序树T中不存在关键字等于key的数据元素时
 * 插入key并返回TRUE，否则返回FALSE
 */
Status InsertBST(BiTree *T, int key)
{
    BiTree p, s;
    if (!SearchBST(*T, key, NULL, &p)) // 查找不成功
    {
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data = key;
        s->lchild = s->rchild = NULL;
        if (!p)
        {
            *T = s; // 插入s为新的根结点
        }
        else if (key < p->data)
        {
            p->lchild = s; // 插入s为左孩子
        }
        else
        {
            p->rchild = s; // 插入s为右孩子
        }
        return TRUE;
    }
    else
    {
        return FALSE; // 树中已有关键字相同的结点，不再插入
    }
}

/* 从二叉排序树中删除结点p，并重接它的左或右子树 */
Status Delete(BiTree *p)
{
    BiTree q, s;
    if ((*p)->rchild == NULL)       // 右子树空则只需重接它的左子树
    {
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    else if ((*p)->lchild == NULL)  // 只需重接它的右子树
    {
        q = *p;
        *p = (*p)->rchild;
        free(q);
    }
    else
    {
        q = *p;
        s = (*p)->lchild;
        while (s->rchild)   // 转左，然后向右到尽头（找待删结点的前驱）
        {
            q = s;
            s = s->rchild;
        }
        (*p)->data = s->data;   // s指向被删除结点的直接前驱
        if (q != *p)
        {
            q->rchild = s->lchild;  // 重接q的右子树
        }
        else
        {
            q->lchild = s->lchild;  // 重接q的左子树
        }
        free(s);
    }
    return TRUE;
}
/* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素的结点 */
/* 并返回TRUE，否则返回FALSE */
Status DeleteBST(BiTree *T, int key)
{
    if (!*T)
    {
        return FALSE;
    }
    else
    {
        if (key == (*T)->data)
        {
            return Delete(T);
        }
        else if (key < (*T)->data)
        {
            return DeleteBST(&(*T)->lchild, key);
        }
        else
        {
            return DeleteBST(&(*T)->rchild, key);
        }
    }
}