#include <stdio.h>
#include <stdlib.h>
/*代码思路：
这道题有两种情况，一个是数据奇数偶数调换，一个是奇数索引和偶数索引的调换，但是我觉得题意应该是后者才对，然后在理解题意的层面，我的想法应该是类似于这样的例子 原始链表：5->9->2->7->1
调整后的链表：9->5->7->2->1 这样才叫做调换。
从思考问题的角度来看：不需要移动节点本身，只需调整next指针即可，如果不采用这种方法，而是插入或者删除这两种基本方法，效率太低了，而且好难想，太复杂。
定义两个指针，一个指向奇数位置的节点，另一个指向偶数位置的节点，这样的目的是，先把这个链表里面的奇数和偶数，全部区分开来，就像是抽出鱼的骨头一样。
遍历链表，将奇数位置节点的next指针指向下一个奇数位置节点，将偶数位置节点的next指针指向下一个偶数位置节点。
最后，将奇数位置节点的尾部连接到偶数位置节点的头部，这样子就可以输出示例中想要的结果*/
typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

// 调整链表，将奇数位置的节点放在偶数位置节点之前
ListNode* adjustOddEvenNodes(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    // 这一段自己一开始没有想到，这是确保代码的健壮性，是这么说吧？如果这个链表没有被初始化，或者说初始化了但只有这一个节点，那就根本没有必要去调整奇偶了。
    // 仔细想想，之前是没有过这样的想法，为什么呢，1.因为一般给的数据不会有问题，题目嘛，2.就算是不满足上述条件的代码，有时候也一样能跑下去，直接结束了。
    //总结：再编写一个函数之前，应该思考，什么样的情况下不需要执行你的方法。

    // 定义奇数节点和偶数节点的头指针
    ListNode* odd = head, * even = head->next, * evenHead = even;
    //应该把奇数和偶数节点看出一个个独立的单元，重新调整节点之间的位置关系，那些节点是始终存在的。
    // 遍历链表
    while (even && even->next) {
        // 奇数节点指向下一个奇数节点
        odd->next = odd->next->next;
        // 偶数节点指向下一个偶数节点
        even->next = even->next->next;
        // 移动奇数节点和偶数节点指针
        odd = odd->next;
        even = even->next;
    }

    // 将奇数节点的尾部连接到偶数节点的头部
    odd->next = evenHead;
    return head;
}
// 打印链表
void printList(ListNode* head) {
    while (head) {
        printf("%d->", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    int n;
    printf("请输入链表节点的数量: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("链表节点数量应大于0\n");
        return 1;
    }

    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    ListNode* current = head;
    printf("请输入链表的值，以空格分隔: ");
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        current->val = value;
        if (i < n - 1) {
            current->next = (ListNode*)malloc(sizeof(ListNode));
            current = current->next;
        } else {
            current->next = NULL;
        }
    }

    printf("原链表: ");
    printList(head);

    ListNode* result = adjustOddEvenNodes(head);

    printf("交换后的链表: ");
    printList(result);

    return 0;
}
