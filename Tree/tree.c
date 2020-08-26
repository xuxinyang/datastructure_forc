#include <stdio.h>
#include <stdlib.h>

#define OK (1)
#define ERROR (0)
#define OVERFLOW (0)
#define MAX_TREE_SIZE (100)
#define SUCCESS (1)
#define FAILED (0)
#define HASHSIZE (12)
#define NULLKEY (-32768)

typedef int Status;
typedef char TElemType; // 树结点的数据类型，目前暂定为整型
typedef struct PTNode
{
    TElemType data; // 结点数据
    int parent;     // 双亲位置
} PTNode;

typedef struct
{
    PTNode nodes[MAX_TREE_SIZE]; // 结点数组
    int r, n;                    // 根的位置和结点
} PTree;

/* 树的孩子表示法结构定义 */
typedef struct CTNode // 孩子结点
{
    int child;
    struct CTNode *next;
} * ChildPtr;

typedef struct // 表头结构
{
    TElemType data;
    ChildPtr firstChild;
} CTBox;

typedef struct // 树结构
{
    CTBox nodes[MAX_TREE_SIZE]; // 结点数组
    int r, n;                   // 根的位置和结点数
} CTree;

/* 树的孩子兄弟表示法结构定义 */
typedef struct CSNode
{
    TElemType data;
    struct CSNode *firstChild, *rightSib;
} CSNode, *CSTNode;

/* 二叉树的二叉链表结构定义 */
typedef struct BiTNode // 结点结构
{
    TElemType data;                  // 结点数据
    struct BiTNode *lchild, *rchild; // 左右孩子指针
} BiTNode, *BiTree;

/* 二叉树的二叉线索存储结构定义 */
typedef enum
{
    Link,  // Link==0表示指向左右孩子指针
    Thread // Thread==1表示指向前驱或后继的线索
} PointerTag;

typedef struct BiThrNode // 二叉线索存储结点结构
{
    TElemType data;
    struct BiThrNode *lchild, *rchild; // 左右孩子指针
    PointerTag LTag, RTag;             // 左右标志
} BiThrNode, *BiThrTree;

typedef struct
{
    int *elem; // 数据元素存储基址，动态分配数组
    int count; // 当前数据元素个数
} HashTable;
int m = 0; // 散列表表长，全局变量

/* 二叉树的前序遍历递归算法 */
void PreOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    else
    {
        printf("%c", T->data);       // 显示结点数据，可以更改为其他对结点操作
        PreOrderTraverse(T->lchild); // 再先序遍历左子树
        PreOrderTraverse(T->rchild); // 最后先序遍历右子树
    }
}

/* 二叉树的中序遍历递归算法 */
void MidOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    else
    {
        MidOrderTraverse(T->lchild); // 中序遍历左子树
        printf("%c", T->data);       // 显示结点数据，可以更改为其他对结点的操作
        MidOrderTraverse(T->rchild); // 中序遍历右子树
    }
}

/* 二叉树的后序遍历递归算法 */
void PostOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    else
    {
        PostOrderTraverse(T->lchild); // 后序遍历左子树
        PostOrderTraverse(T->rchild); // 后序遍历右子树
        printf("%c", T->data);        // 显示结点数据，可以更改为其他对结点的操作
    }
}

/* 按前序输入二叉树中结点的值
 * #表示空树，构造二叉链表表示二叉树T
 */
void CreateBiTree(BiTree *T)
{
    TElemType ch;
    scanf("%c", &ch);
    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!*T)
        {
            exit(OVERFLOW);
        }
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}
BiThrTree pre;
/* 中序遍历线索化 */
void MidOrderThreading(BiThrTree biOrderThr)
{
    if (biOrderThr)
    {
        MidOrderThreading(biOrderThr->lchild); // 递归左子树线索化
        if (!biOrderThr->lchild)               // 没有左子树
        {
            biOrderThr->LTag = Thread; // 前驱线索
            biOrderThr->lchild = pre;  // 左孩子指针指向前驱
        }
        if (!pre->rchild) // 前驱没有右孩子
        {
            pre->RTag = Thread;       // 后继线索
            pre->rchild = biOrderThr; // 前驱有孩子指针指向后继（当前结点biOrderThr）
        }
        pre = biOrderThr;                      //  保持pre指向biOrderThr的前驱
        MidOrderThreading(biOrderThr->rchild); // 递归右子树线索化
    }
}

/**
 * T指向头结点，头结点左链lchild指向根结点，头结点右链rchild指向中序遍历的最后一个结点。
 * 中序遍历二叉线索链表表示的二叉树T
 */
Status MidOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild;
    while (p != T)
    {
        while (p->LTag == Link)
            p = p->lchild;
        printf("%c", p->data);
        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            printf("%c", p->data);
        }
        p = p->rchild;
    }
    return OK;
}

Status InitHashTable(HashTable *H)
{
    int i;
    m = HASHSIZE;
    H->count = m;
    H->elem = (int *)malloc(m * sizeof(int));
    for (i = 0; i < m; i++)
    {
        H->elem[i] = NULLKEY;
    }
    return OK;
}

/* 散列函数 */
int Hash(int key)
{
    return key % m; // 除留余数法
}

/* 插入关键字进散列表 */
void InsertHash(HashTable *H, int key)
{
    int addr = Hash(key);            // 求散列地址
    while (H->elem[addr] != NULLKEY) // 如果不为空，则冲突
        addr = (addr + 1) % m;       // 开放定址的线性探测
    H->elem[addr] = key;             // 直到有空位后插入关键字
}

/* 散列表查找关键字 */
Status SearchHash(HashTable H, int key, int *addr)
{
    *addr = Hash(key);           // 求散列地址
    while (H.elem[*addr] != key) // 如果不为空则冲突
    {
        *addr = (*addr + 1) % m; // 开放定址法的线性探测
        if (H.elem[*addr] == NULLKEY || *addr == Hash(key))
        {
            /* 如果循回到原点 */
            return FAILED; // 则说明关键字不存在
        }
    }
    return SUCCESS;
}