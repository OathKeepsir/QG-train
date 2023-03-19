#include <stdio.h>
#include <stdlib.h>
//ʵ��˫������ADT�������У�1.����һ���ڵ�Ľṹ��2.��ʼ��һ������ 3.���ܰ��������ڵ㣩�����㣬���ҽڵ㣬ɾ���ڵ㣬��������������ɾ����������
//��Ҫʵ��һ��˫��������ô�������Ĺ���Ӧ������1.���Դ�ͷ��ʼ������2.���Դ�β��ʼ���� 3.�Ҳ���Ҫ�����ҾͿ���֪���������ĸ����ˡ���ô���Զ���һ���ṹ�壬��˵��������������Ҳ����struct List
// ����˫������ڵ�Ľṹ��
typedef struct Node {
    int data;           // ����
    struct Node* prev;  // ǰ���ڵ��ָ��
    struct Node* next;  // ��̽ڵ��ָ��
} Node;

// ����˫������Ľṹ��
typedef struct List {
    int count;      // ��¼����(�����нڵ�)
    Node* head;     // ����ͷ�ڵ��ָ��
    Node* tail;     // ����β�ڵ��ָ��
} List;

// ��ʼ������
List* initList() {
    List* list = (List*)malloc(sizeof(List));  // ��һ���ڴ�ռ䣬��С��Ȼ��List
    list->count = 0;                            // �����нڵ���Ϊ 0
    list->head = NULL;                          // ͷ�ڵ�ָ��Ϊ NULL
    list->tail = NULL;                          // β�ڵ�ָ��Ϊ NULL
    //���ǳ�ʼ��
    return list;
}

// �����ڵ�
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));  // ����ڵ��ڴ�ռ�
    node->data = data;                          // �ڵ�洢����
    node->prev = NULL;                          // ��ʼ��ǰ��ָ��Ϊ NULL
    node->next = NULL;                          // ��ʼ�����ָ��Ϊ NULL
    return node;
}
//����ڵ� ����һ���ڵ�Ҫʲô�������ԭ������Ĳ���������Ҫһ��ͷ�ڵ㣬������Ҫ���������
//���ﲻͬ�ڵ�������˫��������ŵ�����ڣ�ʱ�临�Ӷȵͣ��������бף��������������ڴ档
// ����Ļ������������һ���Ǳ�����û�нڵ㣬һ�����Ѿ��нڵ��ˡ�
// �����ǲ�����һ��ͨ�õĴ��룬����Ҳͦ�򵥵ģ�д���жϾ����ˡ�
// ����ڵ�
void insertNode(List* list, int data) {
    Node* node = createNode(data);  // ����Ҫ����Ľڵ㣬�����ڴ�֮ǰ�ĺ�����
    if (list->count == 0) {         
        list->head = node;          //ͷβ����ͬһ��
        list->tail = node;
    }
    else {                       //1.�����ȶ��������Ľڵ���д���Ȼ���ٶ������ṹ����������ԣ�β�ڵ㣩���е���������˼·�����Ƚڵ������
        node->prev = list->tail;    // ��Ҫ����ڵ��ǰ�� ָ�� ��ǰβ�ڵ�
        list->tail->next = node;    // ����ǰβ�ڵ�ĺ�� ָ�� Ҫ����Ľڵ�
        list->tail = node;          // �������βָ�� ָ�� Ҫ����Ľڵ�
       
    }
    list->count++;                  // �ڵ����� 1
}

// ɾ���ڵ� ����Ҫ������˫�������ָ�룬��Ҫɾ���ڵ�����ݣ���һ�θ����˵㣬��������������
// ��ʵɾ���ڵ��ʱ�临�ӶȻ���O(n)��Ȼ�ǵñ�����
// ���ҵ���Ȼ������λ�õĲ�ͬ�����Դ������Ҳ�᲻ͬ�������������������Ӧ�����ֲ�ͬ�Ĵ���취����֪����û��ͨ�õĴ��룬�ҹ������еģ�����Ϊ�˴���Ŀɶ��ԣ�ֱ�ӷ�������ˬһ�㣬���ң�ֻҪ����ͷ�ڵ����β�ڵ㣬�ǾͰɲ��ö������е�ͷβ�ڵ�ָ�����ı�
//��һ�������ɾ���ڵ���ͷ�ڵ�
void deleteNode(List* list, int data) {
    Node* node = list->head;        // ��ͷ�ڵ㿪ʼ����Ҫɾ���Ľڵ�
    while (node != NULL) {
        if (node->data == data) {   // ����ҵ���Ҫɾ���Ľڵ�
            if (node->prev != NULL) {   // ���Ҫɾ���Ľڵ㲻��ͷ�ڵ�
                node->prev->next = node->next;  // ��Ҫɾ���ڵ��ǰ���ڵ�ĺ�� ָ�� Ҫɾ���ڵ�ĺ�̽ڵ�
            }
            else {                // ���Ҫɾ���Ľڵ���ͷ�ڵ�
                list->head = node->next;        // ��ͷָ��ָ��Ҫɾ���ڵ�ĺ�̽ڵ�
                if (list->head != NULL) {       // ��������л��нڵ�
                    list->head->prev = NULL;    // ���µ�ͷ�ڵ��ǰ��ָ������Ϊ NULL
                }
                else {                        // ����������Ѿ�û�нڵ�
                    list->tail = NULL;          // ��βָ��Ҳ����Ϊ NULL
                }
            }
            if (node->next != NULL) {           // ���Ҫɾ���Ľڵ㲻��β�ڵ�
                node->next->prev = node->prev;  // ��Ҫɾ���ڵ�ĺ�̽ڵ��ǰ��ָ��Ҫɾ���ڵ��ǰ���ڵ�
            }
            else {                            // ���Ҫɾ���Ľڵ���β�ڵ�
                list->tail = node->prev;        // ��βָ��ָ��Ҫɾ���ڵ��ǰ���ڵ�
                if (list->tail != NULL) {       // ��������л��нڵ�
                    list->tail->next = NULL;    // ���µ�β�ڵ�ĺ��ָ������Ϊ NULL
                }
                else {                        // ����������Ѿ�û�нڵ�
                    list->head = NULL;          // ��ͷָ��Ҳ����Ϊ NULL
                }
            }
            free(node);                 // �ͷ�Ҫɾ���Ľڵ���ڴ�ռ�
            list->count--;              // �ڵ����� 1
            return;
        }
        node = node->next;              // ���û���ҵ�Ҫɾ���Ľڵ㣬�����������ڵ㣬��һ��
    }
    printf("û���ҵ�Ҫɾ���Ľڵ�\n");   // ���������û���ҵ�Ҫɾ���Ľڵ㣬���������Ϣ
}

// ���ҽڵ�
Node* findNode(List* list, int data) {
    Node* node = list->head;        // ��ͷ��ʼ
    while (node != NULL) {
        if (node->data == data) {   // ����ҵ���Ҫ���ҵĽڵ㣬���ظýڵ��ָ��
            return node;
        }
        node = node->next;          // ���û���ҵ��������������ڵ�
    }
    return NULL;                    // ���������û���ҵ�Ҫ���ҵĽڵ㣬���� NULL
}

// ��ӡ����
void printList(List* list) {
    Node* node = list->head;        // ��ͷ�ڵ㿪ʼ����
    printf("�����еĽڵ���Ϊ��%d\n", list->count);   // ��������нڵ�ĸ���
    while (node != NULL) {
        printf("%d ", node->data);  // ����ڵ�洢������
        node = node->next;          // �����������ڵ�
    }
    printf("\n");
}
//���Դ��� 
int main() {
    List* list = initList();    // ��ʼ������
    insertNode(list, 1);        // ����ڵ�
    insertNode(list, 2);
    insertNode(list, 3);
    printList(list);            // ��ӡ����
    deleteNode(list, 2);
    printList(list);            // ��ӡ����
    Node* node = findNode(list, 3); // ���ҽڵ�
    if (node != NULL) {         // ����ҵ��˽ڵ�
        printf("�ҵ��˽ڵ� %d\n", node->data);
    }
    else {                    // ���û���ҵ��ڵ�
        printf("û���ҵ�Ҫ���ҵĽڵ�\n");
    }
    return 0;
}
