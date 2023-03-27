#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
int is_operator_v2(char symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}//这里是对是不是 加减乘除操作符的判断 
int precedence_v2(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}
//这里是对 加减和乘除操作符的优先级处理
void infix_to_postfix(char* infix,char* postfix){
	Stack operators;//栈，中间处理的容器
    init(&operators);//初始化栈
    int i = 0, j = 0;//临时变量，用于指定数组中的字符位置
    while (infix[i] != '\0') {//这个while 是对中缀表达式的处理，
        char current = infix[i];//定义一个变量来 存储当前中缀表达式的字符 
        //当前字符 1.如果是数字的话，直接放进后缀表达式中，2.如果是左括号或者右括号，再做分类讨论
		//如果是左括号，那就直接放进去，如果是右括号，那就得看栈里面是不是空的，还有有没有匹配的左括号，
		//如果非空且当前栈顶不是匹配的左括号，那么就应该是操作符或者数字，直接放入后缀表达式即可，循环至栈已空，或已经到（，那么这时候弹出（ 
        if (isdigit(current)) {//先判断是不是数字，数字则直接压入。
            postfix[j++] = current;
        } else if (current == '(') {
            push(&operators, current);
        } else if (current == ')') {
            while (!isempty(&operators) && top(&operators) != '(') {
            postfix[j++] = (char)pop(&operators); //注意到，这里面写的pop方法，返回的是int类型，存进char数组里，应该强转。 
    	}
		//pop(&operators); 这行代码先前写的有误，应该修改成以下代码，这样子避免的空栈弹出的错误
            if (!isempty(&operators)) {
                pop(&operators); // 弹出左括号
            }
            else {
                printf("错误：括号不匹配\n");
                return;
            }
		}
        //数字，括号，处理完毕，现在来到对 加减乘除 运算符的处理 
		 else if (is_operator_v2(current)) {
		 while (!isempty(&operators) && precedence_v2((char)top(&operators)) >= precedence_v2(current)) {
                postfix[j++] = (char)pop(&operators);
            }//处理方式，  如果栈非空，且current操作符的优先级，如乘除 大于 加减，那么 直接压入栈中。   
         //例子，如果栈顶元素是 *，当前字符为 +，则弹出*，再把压入栈中。
         //例子，如果栈顶元素是 +，当前字符为 * ，则压入*进栈，再判断下一轮
         //例子，如果当前栈顶元素是空，那么直接压入当前操作符。
            push(&operators, current);
        }
        i++;
        //进入下一轮对当前字符的处理。
    }
    //中缀表达式已经处理完毕，目前对栈中字符进行处理，全部弹出，并最后给后缀表达式设置终止符。
    while (!isempty(&operators)) {
        postfix[j++] = (char)pop(&operators);
    }
    postfix[j] = '\0';
}
// 这里是求解后缀表达式的函数，将后缀表达式字符串作为参数传入
int evaluate_postfix(char *postfix) {
    Stack stack;//貌似有跟main函数重名的感觉，但是没关系，这个函数结束后就会被释放掉，只是要个结果。 
    init(&stack);
    int i = 0;

    // 遍历后缀表达式的每一个字符
    while (postfix[i] != '\0') {
        char current = postfix[i];

        // 是数字，就放进栈中 
        if (isdigit(current)) {
            push(&stack, current - '0');
        } else if (is_operator_v2(current)) { // 如果当前字符是操作符
            // 弹出栈顶的两个数字作为操作数，计算之后，再把计算结果压进栈中 
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

    // 表达式求解完成后，栈顶元素即为结果
    return pop(&stack);
}
int main(){
	Stack stack;
	init(&stack);
    int choice;
    int result;
    char infix[256],postfix[256];
    while(1){
    printf("请输入一个中缀表达式，如1+1，然后我会告诉你计算的结果");
	scanf("%s", infix);
    infix_to_postfix(infix,postfix);
    result =evaluate_postfix(postfix);
    printf("对应的后缀表达式为：%s\n", postfix);
    printf("对应的后缀表达式结果为：%d\n", result);
    system("pause");
    return 0;
}
}
