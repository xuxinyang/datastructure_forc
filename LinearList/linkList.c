#include <stdlib.h>
#include <time.h>

#define OK       (1)
#define ERROR    (0)
#define TRUE     (1)
#define FALSE    (0)

typedef int ElemType;
typedef int Status;
/* 线性表的单链表存储结构 */
typedef struct Node
{
    ElemType data;
    struct Node *next;

}Node;
typedef struct Node *LinkList;     // 定义LinkList
/**
 * 初始条件：单链表L已存在，1<=i<=LinkListLength(L)
 * 操作结果：用e返回L中第i个数据元素的值
 */
Status LinkGetElem(LinkList L, int i, ElemType *e)
{
    int j;
    LinkList p;           // 声明一结点p
    p = L->next;          // p指向第一个结点
    j = 1;
    while (p && j < i)
    {
        p = p->next;
        ++ j;
    }
    if (!p || j > i)
    {
        return ERROR;
    }
    *e = p->data;         // 返回找到的元素
    return OK;
}

/**
 * 初始条件：单链表表L已存在，1<=i<=LinkListLength(L)
 * 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1
 */
Status LinkListInsert(LinkList *L, int i, ElemType e)
{
    int j;
    LinkList p, s;
    p = *L;
    j = 1;
    while (p && j < i)         // 寻找第i个结点
    {
        p = p->next;
        ++ j;
    }
    if (!p || j > i)
    {
        return ERROR;          // 第i个结点不存在
    }
    s = (LinkList)malloc(sizeof(Node));     // 生成新结点
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

/**
 * 初始条件：单链表L已存在，1<=i<=LinkListLength(L)
 * 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1
 */
Status LinkListDelete(LinkList *L, int i, ElemType *e)
{
    int j;
    LinkList p, q;
    p = *L;
    j = 1;
    while (p->next && j < i)
    {
        p = p->next;
        ++ j;
    }
    if (!(p->next) || j > i)
    {
        return ERROR;
    }
    q = p->next;
    p->next = q->next;          // 将q的后继赋给p的后继
    *e = q->data;               // 将q结点中的数据给e
    free(q);                    // 让系统回收此结点，释放内存
    return OK;
}

/**
 * 随机产生n个元素的值，建立带表头结点的单链线性表L（头插法）
 */
void CreateLinkListHead(LinkList *L, int n)
{
    LinkList p;
    int i;
    srand(time(0));               // 初始化随机数种子
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    for (i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(Node));
        p->data = rand()%100 + 1;
        p->next = (*L)->next;
        (*L)->next = p;           // 插入到表头
    }
}

/**
 * 随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法）
 */
void CreateLinkListTail(LinkList *L, int n)
{
    LinkList p, r;
    int i;
    srand(time(0));
    *L = (LinkList)malloc(sizeof(Node));
    r = *L;
    for (i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(Node));
        p->data = rand()%100 + 1;
        r->next = p;            // 将表尾终端结点的指针指向新结点
        r = p;                  // 将当前的新结点定义为表尾终端结点
    }
    r->next = NULL;
}

/**
 * 初始条件：单链表L已存在，操作结果：将L重置为空表
 */
Status ClearLinkList(LinkList *L)
{
    LinkList p, q;
    p = (*L)->next;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL;      // 头结点指针域
    return OK;
}