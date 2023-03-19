#include <stdio.h>
#include <stdlib.h>
/*����˼·��
����������������һ������������ż��������һ��������������ż�������ĵ����������Ҿ�������Ӧ���Ǻ��߲Ŷԣ�Ȼ�����������Ĳ��棬�ҵ��뷨Ӧ�������������������� ԭʼ����5->9->2->7->1
�����������9->5->7->2->1 �����Ž���������
��˼������ĽǶ�����������Ҫ�ƶ��ڵ㱾��ֻ�����nextָ�뼴�ɣ�������������ַ��������ǲ������ɾ�������ֻ���������Ч��̫���ˣ����Һ����룬̫���ӡ�
��������ָ�룬һ��ָ������λ�õĽڵ㣬��һ��ָ��ż��λ�õĽڵ㣬������Ŀ���ǣ��Ȱ�������������������ż����ȫ�����ֿ����������ǳ����Ĺ�ͷһ����
��������������λ�ýڵ��nextָ��ָ����һ������λ�ýڵ㣬��ż��λ�ýڵ��nextָ��ָ����һ��ż��λ�ýڵ㡣
��󣬽�����λ�ýڵ��β�����ӵ�ż��λ�ýڵ��ͷ���������ӾͿ������ʾ������Ҫ�Ľ��*/
typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

// ��������������λ�õĽڵ����ż��λ�ýڵ�֮ǰ
ListNode* adjustOddEvenNodes(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    // ��һ���Լ�һ��ʼû���뵽������ȷ������Ľ�׳�ԣ�����ô˵�ɣ�����������û�б���ʼ��������˵��ʼ���˵�ֻ����һ���ڵ㣬�Ǿ͸���û�б�Ҫȥ������ż�ˡ�
    // ��ϸ���룬֮ǰ��û�й��������뷨��Ϊʲô�أ�1.��Ϊһ��������ݲ��������⣬��Ŀ�2.�����ǲ��������������Ĵ��룬��ʱ��Ҳһ��������ȥ��ֱ�ӽ����ˡ�
    //�ܽ᣺�ٱ�дһ������֮ǰ��Ӧ��˼����ʲô��������²���Ҫִ����ķ�����

    // ���������ڵ��ż���ڵ��ͷָ��
    ListNode* odd = head, * even = head->next, * evenHead = even;
    //Ӧ�ð�������ż���ڵ㿴��һ���������ĵ�Ԫ�����µ����ڵ�֮���λ�ù�ϵ����Щ�ڵ���ʼ�մ��ڵġ�
    // ��������
    while (even && even->next) {
        // �����ڵ�ָ����һ�������ڵ�
        odd->next = odd->next->next;
        // ż���ڵ�ָ����һ��ż���ڵ�
        even->next = even->next->next;
        // �ƶ������ڵ��ż���ڵ�ָ��
        odd = odd->next;
        even = even->next;
    }

    // �������ڵ��β�����ӵ�ż���ڵ��ͷ��
    odd->next = evenHead;
    return head;
}
// ��ӡ����
void printList(ListNode* head) {
    while (head) {
        printf("%d->", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    int n;
    printf("����������ڵ������: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("����ڵ�����Ӧ����0\n");
        return 1;
    }

    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    ListNode* current = head;
    printf("�����������ֵ���Կո�ָ�: ");
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

    printf("ԭ����: ");
    printList(head);

    ListNode* result = adjustOddEvenNodes(head);

    printf("�����������: ");
    printList(result);

    return 0;
}
