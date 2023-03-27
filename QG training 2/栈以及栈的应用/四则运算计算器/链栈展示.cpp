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
void infix_to_postfix(char* infix,char* postfix){
	Stack operators;//ջ���м䴦�������
    init(&operators);//��ʼ��ջ
    int i = 0, j = 0;//��ʱ����������ָ�������е��ַ�λ��
    while (infix[i] != '\0') {//���while �Ƕ���׺���ʽ�Ĵ���
        char current = infix[i];//����һ�������� �洢��ǰ��׺���ʽ���ַ� 
        //��ǰ�ַ� 1.��������ֵĻ���ֱ�ӷŽ���׺���ʽ�У�2.����������Ż��������ţ�������������
		//����������ţ��Ǿ�ֱ�ӷŽ�ȥ������������ţ��Ǿ͵ÿ�ջ�����ǲ��ǿյģ�������û��ƥ��������ţ�
		//����ǿ��ҵ�ǰջ������ƥ��������ţ���ô��Ӧ���ǲ������������֣�ֱ�ӷ����׺���ʽ���ɣ�ѭ����ջ�ѿգ����Ѿ���������ô��ʱ�򵯳��� 
        if (isdigit(current)) {//���ж��ǲ������֣�������ֱ��ѹ�롣
            postfix[j++] = current;
        } else if (current == '(') {
            push(&operators, current);
        } else if (current == ')') {
            while (!isempty(&operators) && top(&operators) != '(') {
            postfix[j++] = (char)pop(&operators); //ע�⵽��������д��pop���������ص���int���ͣ����char�����Ӧ��ǿת�� 
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
            }//����ʽ��  ���ջ�ǿգ���current�����������ȼ�����˳� ���� �Ӽ�����ô ֱ��ѹ��ջ�С�   
         //���ӣ����ջ��Ԫ���� *����ǰ�ַ�Ϊ +���򵯳�*���ٰ�ѹ��ջ�С�
         //���ӣ����ջ��Ԫ���� +����ǰ�ַ�Ϊ * ����ѹ��*��ջ�����ж���һ��
         //���ӣ������ǰջ��Ԫ���ǿգ���ôֱ��ѹ�뵱ǰ��������
            push(&operators, current);
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
int evaluate_postfix(char *postfix) {
    Stack stack;//ò���и�main���������ĸо�������û��ϵ���������������ͻᱻ�ͷŵ���ֻ��Ҫ������� 
    init(&stack);
    int i = 0;

    // ������׺���ʽ��ÿһ���ַ�
    while (postfix[i] != '\0') {
        char current = postfix[i];

        // �����֣��ͷŽ�ջ�� 
        if (isdigit(current)) {
            push(&stack, current - '0');
        } else if (is_operator_v2(current)) { // �����ǰ�ַ��ǲ�����
            // ����ջ��������������Ϊ������������֮���ٰѼ�����ѹ��ջ�� 
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);

            switch (current) {
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
    char infix[256],postfix[256];
    while(1){
    printf("������һ����׺���ʽ����1+1��Ȼ���һ���������Ľ��");
	scanf("%s", infix);
    infix_to_postfix(infix,postfix);
    result =evaluate_postfix(postfix);
    printf("��Ӧ�ĺ�׺���ʽΪ��%s\n", postfix);
    printf("��Ӧ�ĺ�׺���ʽ���Ϊ��%d\n", result);
    system("pause");
    return 0;
}
}
