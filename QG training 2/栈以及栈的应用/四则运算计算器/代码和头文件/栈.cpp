//#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int data;
	struct Node* next;
}Node;
typedef struct Stack {
	Node* head;
	int size;
} Stack;
//��ʼ��ջ
void init(Stack* stack) {
	stack->head = NULL;
	stack->size = 0;
}
int isempty(Stack* stack) {
	return stack->size == 0;
}
void push(Stack* stack,int data) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->next = stack->head;
	stack->head = newnode;
	stack->size ++;
}
int pop(Stack* stack) {
	if (isempty(stack)) {
		printf("��ջ������Ԫ�أ�����ʧ��");
			return 0;
	}
	Node* tmp = stack->head;
	int pop_data = stack->head->data;
	stack->head = stack->head->next;
	free(tmp);
	stack->size--;
	return pop_data;
}

int top(Stack* stack) {
	if (isempty(stack)){
		printf("��ջ������Ԫ�أ���ȡʧ��");
		return 0;
	}
	return stack->head->data;
}
/*int main() {
	Stack stack;
	init(&stack);
    int choice;
    int data;
    while (1) {
        printf("\n����ջ�Ĳ����˵�(����1-5������)��\n");
        printf("1. ��ջ\n");
        printf("2. ��ջ\n");
        printf("3. �鿴ջ��Ԫ��\n");
        printf("4. �ж�ջ�Ƿ�Ϊ��\n");
        printf("5. �˳�����\n");
        printf("��ѡ�������1-5����");
		if (scanf("%d", &choice) != 1) {
            printf("�������������һ��������1-5����\n");
            while (getchar() != '\n'); // ������뻺����
            continue;
        } 
        switch (choice) {
        case 1:
            printf("������Ҫ��ջ��������");
            if (scanf("%d", &data) != 1) {
                printf("�������������һ��������\n");
                while (getchar() != '\n'); // ������뻺����
            }
            else {
                push(&stack, data);
                printf("%d�ѳɹ���ջ��\n", data);
            }
            break;
        case 2:
            if (!isempty(&stack)) {
                data = pop(&stack);
                printf("��ջ��Ԫ���ǣ�%d\n", data);
            }
            else {
                printf("ջΪ�գ��޷�ִ�г�ջ������\n");
            }
            break;
        case 3:
            if (!isempty(&stack)) {
                data = top(&stack);
                printf("ջ��Ԫ���ǣ�%d\n", data);
            }
            else {
                printf("ջΪ�ա�\n");
            }
            break;
        case 4:
            if(isempty){
            	printf("ջΪ��"); 
            }else{
            	printf("ջ��Ϊ��");
            }
            break;
        case 5:
            printf("�˳�����\n");
            return 0;
        default:
            printf("�������������һ��������ѡ���ܣ�1-5����\n");
            break;
        }
    }
	system("pause");
    return 0;
}*/
