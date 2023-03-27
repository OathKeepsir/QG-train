#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
int is_operator_v2(char symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}//�����Ƕ��ǲ��� �Ӽ��˳����������ж� 
int precedence_v2(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}
//�����Ƕ� �Ӽ��ͳ˳������������ȼ�����
void infix_to_postfix(char* infix,int* postfix){
	Stack operators;//ջ���м䴦�������
    init(&operators);//��ʼ��ջ
    int i = 0, j = 0;//��ʱ����������ָ�������е��ַ�λ��
    while (infix[i] != '\0') {//���while �Ƕ���׺���ʽ�Ĵ���
        char current = infix[i];//����һ�������� �洢��ǰ��׺���ʽ���ַ� 
        //��ǰ�ַ� 1.��������ֵĻ���ֱ�ӷŽ���׺���ʽ�У�2.����������Ż��������ţ�������������
		//����������ţ��Ǿ�ֱ�ӷŽ�ȥ������������ţ��Ǿ͵ÿ�ջ�����ǲ��ǿյģ�������û��ƥ��������ţ�
		//����ǿ��ҵ�ǰջ������ƥ��������ţ���ô��Ӧ���ǲ������������֣�ֱ�ӷ����׺���ʽ���ɣ�ѭ����ջ�ѿգ����Ѿ���������ô��ʱ�򵯳��� 
        if (isdigit(current)) {//���ж��ǲ������֣�������ֱ��ѹ�롣
            int number = current - '0';
            i++;
            while (isdigit(infix[i])){
                number = number * 10 + (infix[i] - '0');
                i++;
            }
            postfix[j++] = number;
            postfix[j++] = -1;
        } else if (current == '(') {
            push(&operators, current);
        } else if (current == ')') {
            while (!isempty(&operators) && top(&operators) != '(') {
                int op = pop(&operators);
                switch (op) {
                case '+':
                    postfix[j++] = -2;
                    break;
                case '-':
                    postfix[j++] = -3;
                    break;
                case '*':
                    postfix[j++] = -4;
                    break;
                case '/':
                    postfix[j++] = -5;
                    break;
                }
    	}
		//pop(&operators); ���д�����ǰд������Ӧ���޸ĳ����´��룬�����ӱ���Ŀ�ջ�����Ĵ���
            if (!isempty(&operators)) {
                pop(&operators); // ����������
            }
            else {
                printf("�������Ų�ƥ��\n");
                return;
            }
		}
        //���֣����ţ�������ϣ����������� �Ӽ��˳� ������Ĵ��� 
        else if (is_operator_v2(current)) {
            while (!isempty(&operators) && precedence_v2((char)top(&operators)) >= precedence_v2(current)) {
                postfix[j++] = (char)pop(&operators);
            }
            postfix[j++] = current; // ���������洢�� postfix ������
            postfix[j++] = -1; // ��Ӳ������ָ���
            push(&operators, current);
        }
        //����ʽ��  ���ջ�ǿգ���current�����������ȼ�����˳� ���� �Ӽ�����ô ֱ��ѹ��ջ�С�   
         //���ӣ����ջ��Ԫ���� *����ǰ�ַ�Ϊ +���򵯳�*���ٰ�ѹ��ջ�С�
         //���ӣ����ջ��Ԫ���� +����ǰ�ַ�Ϊ * ����ѹ��*��ջ�����ж���һ��
         //���ӣ������ǰջ��Ԫ���ǿգ���ôֱ��ѹ�뵱ǰ��������
         if (i > 0 && isdigit(infix[i - 1])) {
             postfix[j++] = -1;
         }

        }
        i++;
        //������һ�ֶԵ�ǰ�ַ��Ĵ���
    }
    //��׺���ʽ�Ѿ�������ϣ�Ŀǰ��ջ���ַ����д���ȫ����������������׺���ʽ������ֹ����
    while (!isempty(&operators)) {
        postfix[j++] = (char)pop(&operators);
    }
    postfix[j] = '\0';
}
// ����������׺���ʽ�ĺ���������׺���ʽ�ַ�����Ϊ��������
int evaluate_postfix(int* postfix) {
    Stack stack;//ò���и�main���������ĸо�������û��ϵ���������������ͻᱻ�ͷŵ���ֻ��Ҫ������� 
    init(&stack);
    int i = 0;

    // ������׺���ʽ��ÿһ���ַ�
    while (postfix[i] != '\0') {
        int current = postfix[i];

        // �����֣��ͷŽ�ջ�� 
        if (current > 0) {
            int number = current;
            push(&stack, number);
            i++;
        }
        else if (current == -1) {
            i++;
            continue;
        }
        else if (is_operator_v2((char)current)) {
            // �����ǰ�ַ��ǲ�����
                   // ����ջ��������������Ϊ������������֮���ٰѼ�����ѹ��ջ�� 
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);

            switch (-current) {
            case '+':
                push(&stack, operand1 + operand2);
                break;
            case '-':
                push(&stack, operand1 - operand2);
                break;
            case '*':
                push(&stack, operand1 * operand2);
                break;
            case '/':
                push(&stack, operand1 / operand2);
                break;
            }
        }
        i++;

    }
    // ���ʽ�����ɺ�ջ��Ԫ�ؼ�Ϊ���
    return pop(&stack);
}
int main(){
	Stack stack;
	init(&stack);
    int choice;
    int result;
    char infix[256];
    int postfix[256];
    while(1){
    printf("������һ����׺���ʽ����1+1��Ȼ���һ���������Ľ��\n");
	scanf("%s", infix);
    infix_to_postfix(infix,postfix);
    result =evaluate_postfix(postfix);
    int k = 0;
    printf("��׺���ʽΪ��");
    if (postfix[k] > 0) {
        printf("%d", postfix[k]);
    }
    else if (postfix[k] == -1) {
        printf(" ");
    }
    else {
        switch (-postfix[k]) {
        case 2:
            printf("+");
            break;
        case 3:
            printf("-");
            break;
        case 4:
            printf("*");
            break;
        case 5:
            printf("/");
            break;
        }
    }

    printf("��Ӧ�ĺ�׺���ʽ���Ϊ��%d\n", result);
}
    system("pause");
    return 0;
}
