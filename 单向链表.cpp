#include<stdio.h>
#include<stdlib.h>
//定义单向链表的结构
//实现单链表ADT，其中有，1.定义一个节点的结构，2.初始化一个链表 3.功能包括：（节点）插入结点，查找节点，删除节点，（链表）遍历链表，删除整个链表

struct Node
{
    int data;
    struct Node* next;
};


//初始化链表 头节点，1.要内存 2.指针域
struct Node* init()
{
    struct Node* head;
    head = (struct Node*)malloc(sizeof(struct Node));
    head->next = NULL;
    return head;
}
//插入节点 插入一个节点要什么，针对于原先链表的操作，所以要一个头节点，还有你要插入的数据。
//这里从头开始遍历，遍历到是null的时候说明到末尾了，使用尾插法。
//q指针用来找到最后一个节点，p指针用来作为插入节点的指针，q找到末尾之后，即给新节点分配出一块内存空间，然后将最后节点与新节点产生链接-》》结束操作
void insertNode(struct Node* head, int data)
{
    struct Node* p, * q;
    q = head;
    while (q->next != NULL)
    {
        q = q->next;
    }
    p = (struct Node*)malloc(sizeof(struct Node));
    p->data = data;
    p->next = NULL;
    q->next = p;
}
//删除节点 删除一个节点要干什么，针对于原先链表的操作，所以要一个头节点，还有你要删除的数据。
//这里依然是从头开始遍历，每次遍历，只要没有到末尾，就进行一次判断。如果判断该数据是我要删除的数据，那，有两种情况，1.要删除的节点已经到末尾了 2.要删除的节点，前后节点还存在。
//针对第一种情况，直接free当前指针指向的节点就完事，同时将上一节点的指针域设为null，完事。
//但是为了更加通用的情况呢，考虑第二种情况，写出的代码能同时适用于两种情况。上一种的情况无非就是，如果我用第一种情况的代码进行操作，对前后节点的重新连接十分的不方便。那么就让（找要删除节点的指针
//即p指针用p->next!=null来判断，这样子可以刚好隔开。
void deleteNode(struct Node* head, int data)
{
    struct Node* p, * q;
    p = head;
    while (p->next != NULL)
    {
        if (p->next->data == data)
        {
            q = p->next;
            p->next = q->next;
            free(q);//找到之后用q
            return;
        }
        p = p->next;//然后p继续前进寻找
    }
}
//查找节点
//这个情况不同于删除节点复杂，直接返回即可，找到就返回，遍历完都没有就返回null
struct Node* findNode(struct Node* head, int data)
{
    struct Node* p;
    p = head->next;
    while (p != NULL)
    {
        if (p->data == data)
            return p;
        p = p->next;
    }
    return NULL;
}
//打印链表
//这个也简单，一个node型指针，遍历一个输出一个。
void printList(struct Node* head)
{
    struct Node* p;
    p = head->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
//删除链表
//这个为什么麻烦一点呢，因为你删除了一个节点之后，你就没办法找到下个节点了。因此这里需要两个节点，p自己去杀。
//因此，没遍历到一个，就要留下一个记号，然后删除上一个，再把记号交给自己，继续前进
void freeList(struct Node* head)
{
    struct Node* p, * q;
    p = head;
    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
}
int main()
{
    struct Node* head;
    head = init();
    insertNode(head, 1);
    insertNode(head, 2);
    insertNode(head, 3);
    insertNode(head, 4);
    insertNode(head, 5);
    printList(head);
    deleteNode(head, 3);
    printList(head);
    struct Node* p;
    p = findNode(head, 4);
    if (p != NULL)
        printf("找到这个节点了:%d\n", p->data);
    else
        printf("没找到这个节点\n");
    freeList(head);
    return 0;
}
