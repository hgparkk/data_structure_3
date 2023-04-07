/*
프로그램 내용 : 괄호가 알맞게 있는지 확인하고 중위수식표기법을 후위수식표기법으로 바꾸고 후위수식표기법을 계산하는 프로그램
실습일 : 2023.04.07
실습자 : 박현규
학번 : 202111678
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef double Element;

Element data[MAX_STACK_SIZE];
int top;

void error(char str[])
{
	printf("%s\n", str);
	exit(1);
}

void init_stack() { top = -1; }
int is_empty() { return top == -1; }
int is_full() { return top == MAX_STACK_SIZE; }
int size() { return top + 1; }

void push(Element e)
{
	if (is_full())
		error("스택 포화 에러");
	data[++top] = e;
}

Element pop()
{
	if (is_empty())
		error("스택 포화 에러");
	return data[top--];
}

Element peek()
{
	if (is_empty())
		error("스택 공백 에러");
	return data[top];
}

int check_matching(char expr[])
{
	int i = 0, prev;
	char ch;
	init_stack();
	while (expr[i] != '\0') {
		ch = expr[i++];
		if (ch == '[' || ch == '(' || ch == '{')
			push(ch);
		else if (ch == ']' || ch == ')' || ch == '}') {
			if (is_empty())
				return 2;
			prev = pop();
			if ((ch == ']' && prev != '[')
				|| (ch == ')' && prev != '(')
				|| (ch == '}' && prev != '{')) {
				return 3;
			}
		}
	}
	if (is_empty() == 0) return 1;
	return 0;
}

int precedence(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}

void infix_to_postfix(char expr[],char result[])
{
	int i = 0;
	int j = 0;
	char c, op;

	init_stack();
	while (expr[i] != '\0') {
		c = expr[i++];
		if ((c >= '0' && c <= '9')) {
			result[j++] = c;
		}
		else if (c == '(')
			push(c);
		else if (c == ')') {
			while (is_empty() == 0) {
				op = pop();
				if (op == '(') break;
				else result[j++] = op;
			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			while (is_empty() == 0) {
				op = peek();
				if (precedence(c) <= precedence(op)) {
					result[j++]=op;
					pop();
				}
				else break;
			}
			push(c);
		}
	}
	while (is_empty() == 0)
		result[j++] = pop();
	result[j] = '\0';
}

double calc_postfix(char expr[])
{
	char c;
	int i = 0;
	double val, val1, val2;

	init_stack();
	while (expr[i] != '\0') {
		c = expr[i++];
		if (c >= '0' && c <= '9') {
			val = c - '0';
			push(val);
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			val2 = pop();
			val1 = pop();
			switch (c) {
			case '+':push(val1 + val2); break;
			case '-':push(val1 - val2); break;
			case '*':push(val1 * val2); break;
			case '/':push(val1 / val2); break;
			}
		}
	}
	return pop();
}

void main()
{
	char expr[80];
	char result[80];
	printf("식을 입력하세요 >> ");
	scanf("%s", &expr);
	int errCode;
	errCode = check_matching(expr);
	if (errCode == 0)
	{
		printf("정상:%s \n", expr);
		printf("중위수식: %s ==> 후위수식: ", expr);
		infix_to_postfix(expr, result);
		printf("%s\n", result);
		printf("결과: %lf\n", calc_postfix(result));
	}
	else
		printf(" 오류:%s (조건%d 위반)\n", expr, errCode);
}