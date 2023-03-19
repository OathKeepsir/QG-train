#include<stdio.h>
#include<stdlib.h>
//这边直接套单链表ADT实现的那个作业的框架了。
// 诶，这边，周五晚上上课的时候大概懂了，把这个想法写了下来，但是总感觉模模糊糊的不严谨，然后去找了数学公式的推导。
/*链表长度为奇数（n = 2k + 1，k为整数）：
在这种情况下，快指针经过k + 1次移动后到达链表的末尾。由于慢指针每次移动一步，所以慢指针在这段时间里移动了k步。因此，慢指针将指向链表的第k + 1个节点，即中点。

链表长度为偶数（n = 2k）：
在这种情况下，快指针经过k次移动后到达链表的末尾。由于慢指针每次移动一步，所以慢指针在这段时间里移动了k步。因此，慢指针将指向链表的第k个节点，这个节点是中间两个节点中的第一个。*/
//所以无论如何奇偶两种情况，都是OK的。
// 查找链表中点的函数
struct Node
{
    int data;
    struct Node* next;
};
Node* findMiddleNode(Node* head) {
    // 初始化快慢指针
    Node* slow = head;
    Node* fast = head;

    // 当快指针和快指针的next都不为NULL时，快慢指针同时前进
    while (fast != NULL && fast->next != NULL) {
        //学到的一个总结：在这个while条件中，我们检查fast是否为NULL以及fast->next是否为NULL，这是因为我们希望确保在循环中访问fast->next是安全的。在C语言中，如果尝试访问NULL指针的成员，程序会崩溃。

        //当我们在循环体内部执行fast = fast->next->next;时，我们实际上是在访问fast->next指针的next成员。所以我们必须确保fast->next是有效的（即非NULL）。

          //  现在，让我们考虑为什么还需要检查fast是否为NULL。在链表长度为偶数的情况下，快指针会在最后一个节点的下一个节点处停止（即NULL）。在这种情况下，fast将为NULL，我们不需要检查fast->next是否为NULL，因为在这种情况下我们不会访问fast->next。但为了确保代码的简洁性和一致性，我们在条件中同时检查了fast和fast->next是否为NULL。

           // 总之，while(fast != NULL && fast->next != NULL)条件确保了我们在循环内部不会访问无效的指针，从而避免程序崩溃。这种检查方式同时适用于奇数长度和偶数长度的链表。
        slow = slow->next; // 慢指针每次前进一步
        fast = fast->next->next; // 快指针每次前进两步
    }

    // 当快指针到达链表末尾时，慢指针指向中点
    return slow;
}
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
    p = findMiddleNode(head);
    if (p != NULL)
        printf("找到这个节点了:%d\n", p->data);
    else
        printf("没找到这个节点\n");
    freeList(head);
    return 0;
}
