﻿/*
프로그램 내용 : 후위수식표기법으로 표기된 식을 계산하는 프로그램
실습일 : 2023.03.23
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
			case '+':push(val1 + val2);break;
			case '-':push(val1 - val2);break;
			case '*':push(val1 * val2);break;
			case '/':push(val1 / val2);break;
			}
		}
	}
	return pop();
}

void main()
{
	char expr[2][80] = { "8 2/ 3- 3 2 * +","1 2 / 4 * 1 4 / *" };

	printf("수식: %s = %lf\n", expr[0], calc_postfix(expr[0]));
	printf("수식: %s = %lf\n", expr[1], calc_postfix(expr[1]));
}