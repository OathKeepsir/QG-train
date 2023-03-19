#include<stdio.h>
#include<stdlib.h>
//���ֱ���׵�����ADTʵ�ֵ��Ǹ���ҵ�Ŀ���ˡ�
// ������ߣ����������Ͽε�ʱ���Ŷ��ˣ�������뷨д�������������ܸо�ģģ�����Ĳ��Ͻ���Ȼ��ȥ������ѧ��ʽ���Ƶ���
/*������Ϊ������n = 2k + 1��kΪ��������
����������£���ָ�뾭��k + 1���ƶ��󵽴������ĩβ��������ָ��ÿ���ƶ�һ����������ָ�������ʱ�����ƶ���k������ˣ���ָ�뽫ָ������ĵ�k + 1���ڵ㣬���е㡣

������Ϊż����n = 2k����
����������£���ָ�뾭��k���ƶ��󵽴������ĩβ��������ָ��ÿ���ƶ�һ����������ָ�������ʱ�����ƶ���k������ˣ���ָ�뽫ָ������ĵ�k���ڵ㣬����ڵ����м������ڵ��еĵ�һ����*/
//�������������ż�������������OK�ġ�
// ���������е�ĺ���
struct Node
{
    int data;
    struct Node* next;
};
Node* findMiddleNode(Node* head) {
    // ��ʼ������ָ��
    Node* slow = head;
    Node* fast = head;

    // ����ָ��Ϳ�ָ���next����ΪNULLʱ������ָ��ͬʱǰ��
    while (fast != NULL && fast->next != NULL) {
        //ѧ����һ���ܽ᣺�����while�����У����Ǽ��fast�Ƿ�ΪNULL�Լ�fast->next�Ƿ�ΪNULL��������Ϊ����ϣ��ȷ����ѭ���з���fast->next�ǰ�ȫ�ġ���C�����У�������Է���NULLָ��ĳ�Ա������������

        //��������ѭ�����ڲ�ִ��fast = fast->next->next;ʱ������ʵ�������ڷ���fast->nextָ���next��Ա���������Ǳ���ȷ��fast->next����Ч�ģ�����NULL����

          //  ���ڣ������ǿ���Ϊʲô����Ҫ���fast�Ƿ�ΪNULL����������Ϊż��������£���ָ��������һ���ڵ����һ���ڵ㴦ֹͣ����NULL��������������£�fast��ΪNULL�����ǲ���Ҫ���fast->next�Ƿ�ΪNULL����Ϊ��������������ǲ������fast->next����Ϊ��ȷ������ļ���Ժ�һ���ԣ�������������ͬʱ�����fast��fast->next�Ƿ�ΪNULL��

           // ��֮��while(fast != NULL && fast->next != NULL)����ȷ����������ѭ���ڲ����������Ч��ָ�룬�Ӷ����������������ּ�鷽ʽͬʱ�������������Ⱥ�ż�����ȵ�����
        slow = slow->next; // ��ָ��ÿ��ǰ��һ��
        fast = fast->next->next; // ��ָ��ÿ��ǰ������
    }

    // ����ָ�뵽������ĩβʱ����ָ��ָ���е�
    return slow;
}
//��ʼ������ ͷ�ڵ㣬1.Ҫ�ڴ� 2.ָ����
struct Node* init()
{
    struct Node* head;
    head = (struct Node*)malloc(sizeof(struct Node));
    head->next = NULL;
    return head;
}
//����ڵ� ����һ���ڵ�Ҫʲô�������ԭ������Ĳ���������Ҫһ��ͷ�ڵ㣬������Ҫ��������ݡ�
//�����ͷ��ʼ��������������null��ʱ��˵����ĩβ�ˣ�ʹ��β�巨��
//qָ�������ҵ����һ���ڵ㣬pָ��������Ϊ����ڵ��ָ�룬q�ҵ�ĩβ֮�󣬼����½ڵ�����һ���ڴ�ռ䣬Ȼ�����ڵ����½ڵ��������-������������
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
//ɾ���ڵ� ɾ��һ���ڵ�Ҫ��ʲô�������ԭ������Ĳ���������Ҫһ��ͷ�ڵ㣬������Ҫɾ�������ݡ�
//������Ȼ�Ǵ�ͷ��ʼ������ÿ�α�����ֻҪû�е�ĩβ���ͽ���һ���жϡ�����жϸ���������Ҫɾ�������ݣ��ǣ������������1.Ҫɾ���Ľڵ��Ѿ���ĩβ�� 2.Ҫɾ���Ľڵ㣬ǰ��ڵ㻹���ڡ�
//��Ե�һ�������ֱ��free��ǰָ��ָ��Ľڵ�����£�ͬʱ����һ�ڵ��ָ������Ϊnull�����¡�
//����Ϊ�˸���ͨ�õ�����أ����ǵڶ��������д���Ĵ�����ͬʱ�����������������һ�ֵ�����޷Ǿ��ǣ�������õ�һ������Ĵ�����в�������ǰ��ڵ����������ʮ�ֵĲ����㡣��ô���ã���Ҫɾ���ڵ��ָ��
//��pָ����p->next!=null���жϣ������ӿ��Ըպø�����
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
            free(q);//�ҵ�֮����q
            return;
        }
        p = p->next;//Ȼ��p����ǰ��Ѱ��
    }
}
//���ҽڵ�
//��������ͬ��ɾ���ڵ㸴�ӣ�ֱ�ӷ��ؼ��ɣ��ҵ��ͷ��أ������궼û�оͷ���null
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
//��ӡ����
//���Ҳ�򵥣�һ��node��ָ�룬����һ�����һ����
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
//ɾ������
//���Ϊʲô�鷳һ���أ���Ϊ��ɾ����һ���ڵ�֮�����û�취�ҵ��¸��ڵ��ˡ����������Ҫ�����ڵ㣬p�Լ�ȥɱ��
//��ˣ�û������һ������Ҫ����һ���Ǻţ�Ȼ��ɾ����һ�����ٰѼǺŽ����Լ�������ǰ��
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
        printf("�ҵ�����ڵ���:%d\n", p->data);
    else
        printf("û�ҵ�����ڵ�\n");
    freeList(head);
    return 0;
}
