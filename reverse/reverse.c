/*
프로그램 내용 : 문자열을 역순으로 출력하는 프로그램
실습일 : 2023.04.08
실습자 : 박현규
학번 : 202111678
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int Element;

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

void char_reverse(char expr[], char reverse[])
{
	char c;
	int i = 0;
	init_stack();
	while (expr[i] != '\0')
	{
		c = expr[i++];
		push(c);
	}
	i = 0;
	while (is_empty() == 0)
		reverse[i++] = pop();
	reverse[i] = '\0';
}

int main()
{
	char expr[80];
	char reverse[80];
	printf("문자열을 입력하세요 >>");
	scanf("%s", &expr);
	char_reverse(expr, reverse);
	printf("%s", reverse);
}