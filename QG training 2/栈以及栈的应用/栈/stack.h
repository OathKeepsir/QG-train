// stack.h
#ifndef STACK_H
#define STACK_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *head;
    int size;
} Stack;

void init(Stack *stack);
int isempty(Stack *stack);
void push(Stack *stack, int data);
int pop(Stack *stack);
int top(Stack *stack);

#endif // STACK_H

