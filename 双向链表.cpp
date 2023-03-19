#include <stdio.h>
#include <stdlib.h>
//实现双向链表ADT，其中有，1.定义一个节点的结构，2.初始化一个链表 3.功能包括：（节点）插入结点，查找节点，删除节点，（链表）遍历链表，删除整个链表
//我要实现一个双向链表，那么这个链表的功能应该是有1.可以从头开始遍历，2.可以从尾开始遍历 3.我不需要遍历我就可以知道这个链表的个数了。那么可以定义一个结构体，来说明这个链表的属性也就是struct List
// 定义双向链表节点的结构体
typedef struct Node {
    int data;           // 数据
    struct Node* prev;  // 前驱节点的指针
    struct Node* next;  // 后继节点的指针
} Node;

// 定义双向链表的结构体
typedef struct List {
    int count;      // 记录个数(链表中节点)
    Node* head;     // 链表头节点的指针
    Node* tail;     // 链表尾节点的指针
} List;

// 初始化链表
List* initList() {
    List* list = (List*)malloc(sizeof(List));  // 给一块内存空间，大小当然是List
    list->count = 0;                            // 链表中节点数为 0
    list->head = NULL;                          // 头节点指针为 NULL
    list->tail = NULL;                          // 尾节点指针为 NULL
    //都是初始化
    return list;
}

// 创建节点
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));  // 分配节点内存空间
    node->data = data;                          // 节点存储数据
    node->prev = NULL;                          // 初始化前驱指针为 NULL
    node->next = NULL;                          // 初始化后继指针为 NULL
    return node;
}
//插入节点 插入一个节点要什么，针对于原先链表的操作，所以要一个头节点，还有你要插入的数据
//这里不同于单向链表，双向链表的优点就在于，时间复杂度低，但有利有弊，它牺牲了它的内存。
// 这里的话有两种情况，一种是本来就没有节点，一种是已经有节点了。
// 忘了是不是有一种通用的代码，不过也挺简单的，写个判断就行了。
// 插入节点
void insertNode(List* list, int data) {
    Node* node = createNode(data);  // 创建要插入的节点，调用在此之前的函数。
    if (list->count == 0) {         
        list->head = node;          //头尾都是同一个
        list->tail = node;
    }
    else {                       //1.这里先对这个插入的节点进行处理，然后再对整个结构体链表的属性（尾节点）进行调整，不过思路都是先节点后链表
        node->prev = list->tail;    // 将要插入节点的前驱 指向 当前尾节点
        list->tail->next = node;    // 将当前尾节点的后继 指向 要插入的节点
        list->tail = node;          // 将链表的尾指针 指向 要插入的节点
       
    }
    list->count++;                  // 节点数加 1
}

// 删除节点 传入要操作的双向链表的指针，和要删除节点的数据（这一段复杂了点，找了资料来看）
// 其实删除节点的时间复杂度还是O(n)依然是得遍历。
// 先找到，然后由于位置的不同，所以处理情况也会不同，这里有三种情况，对应这三种不同的处理办法。不知道有没有通用的代码，我估计是有的，但是为了代码的可读性，直接分类讨论爽一点，而且，只要不是头节点或者尾节点，那就吧不用对链表中的头尾节点指针做改变
//第一种情况：删除节点是头节点
void deleteNode(List* list, int data) {
    Node* node = list->head;        // 从头节点开始查找要删除的节点
    while (node != NULL) {
        if (node->data == data) {   // 如果找到了要删除的节点
            if (node->prev != NULL) {   // 如果要删除的节点不是头节点
                node->prev->next = node->next;  // 将要删除节点的前驱节点的后继 指向 要删除节点的后继节点
            }
            else {                // 如果要删除的节点是头节点
                list->head = node->next;        // 将头指针指向要删除节点的后继节点
                if (list->head != NULL) {       // 如果链表中还有节点
                    list->head->prev = NULL;    // 将新的头节点的前驱指针设置为 NULL
                }
                else {                        // 如果链表中已经没有节点
                    list->tail = NULL;          // 将尾指针也设置为 NULL
                }
            }
            if (node->next != NULL) {           // 如果要删除的节点不是尾节点
                node->next->prev = node->prev;  // 将要删除节点的后继节点的前驱指向要删除节点的前驱节点
            }
            else {                            // 如果要删除的节点是尾节点
                list->tail = node->prev;        // 将尾指针指向要删除节点的前驱节点
                if (list->tail != NULL) {       // 如果链表中还有节点
                    list->tail->next = NULL;    // 将新的尾节点的后继指针设置为 NULL
                }
                else {                        // 如果链表中已经没有节点
                    list->head = NULL;          // 将头指针也设置为 NULL
                }
            }
            free(node);                 // 释放要删除的节点的内存空间
            list->count--;              // 节点数减 1
            return;
        }
        node = node->next;              // 如果没有找到要删除的节点，继续向后遍历节点，下一个
    }
    printf("没有找到要删除的节点\n");   // 如果链表中没有找到要删除的节点，输出错误信息
}

// 查找节点
Node* findNode(List* list, int data) {
    Node* node = list->head;        // 从头开始
    while (node != NULL) {
        if (node->data == data) {   // 如果找到了要查找的节点，返回该节点的指针
            return node;
        }
        node = node->next;          // 如果没有找到，继续向后遍历节点
    }
    return NULL;                    // 如果链表中没有找到要查找的节点，返回 NULL
}

// 打印链表
void printList(List* list) {
    Node* node = list->head;        // 从头节点开始遍历
    printf("链表中的节点数为：%d\n", list->count);   // 输出链表中节点的个数
    while (node != NULL) {
        printf("%d ", node->data);  // 输出节点存储的数据
        node = node->next;          // 继续向后遍历节点
    }
    printf("\n");
}
//测试代码 
int main() {
    List* list = initList();    // 初始化链表
    insertNode(list, 1);        // 插入节点
    insertNode(list, 2);
    insertNode(list, 3);
    printList(list);            // 打印链表
    deleteNode(list, 2);
    printList(list);            // 打印链表
    Node* node = findNode(list, 3); // 查找节点
    if (node != NULL) {         // 如果找到了节点
        printf("找到了节点 %d\n", node->data);
    }
    else {                    // 如果没有找到节点
        printf("没有找到要查找的节点\n");
    }
    return 0;
}
