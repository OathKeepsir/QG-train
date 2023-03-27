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
//初始化栈
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
		printf("该栈中已无元素，弹出失败");
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
		printf("该栈中已无元素，获取失败");
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
        printf("\n链表栈的操作菜单(输入1-5的整数)：\n");
        printf("1. 入栈\n");
        printf("2. 出栈\n");
        printf("3. 查看栈顶元素\n");
        printf("4. 判断栈是否为空\n");
        printf("5. 退出程序\n");
        printf("请选择操作（1-5）：");
		if (scanf("%d", &choice) != 1) {
            printf("输入错误，请输入一个整数（1-5）。\n");
            while (getchar() != '\n'); // 清空输入缓冲区
            continue;
        } 
        switch (choice) {
        case 1:
            printf("请输入要入栈的整数：");
            if (scanf("%d", &data) != 1) {
                printf("输入错误，请输入一个整数。\n");
                while (getchar() != '\n'); // 清空输入缓冲区
            }
            else {
                push(&stack, data);
                printf("%d已成功入栈。\n", data);
            }
            break;
        case 2:
            if (!isempty(&stack)) {
                data = pop(&stack);
                printf("出栈的元素是：%d\n", data);
            }
            else {
                printf("栈为空，无法执行出栈操作。\n");
            }
            break;
        case 3:
            if (!isempty(&stack)) {
                data = top(&stack);
                printf("栈顶元素是：%d\n", data);
            }
            else {
                printf("栈为空。\n");
            }
            break;
        case 4:
            if(isempty){
            	printf("栈为空"); 
            }else{
            	printf("栈不为空");
            }
            break;
        case 5:
            printf("退出程序。\n");
            return 0;
        default:
            printf("输入错误，请输入一个整数来选择功能（1-5）。\n");
            break;
        }
    }
	system("pause");
    return 0;
}*/
