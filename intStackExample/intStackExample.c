/*
프로그램 내용 : 정수로된 스택 예제 프로그램
실습일 : 2023.03.23
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
int size() { return top+1; }

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

void print_stack(char msg[]) 
{
	int i;
	printf("%s[%2d]=", msg, size());
	for (i = 0;i < size();i++)
		printf("%2d", data[i]);
	printf("\n");
}

int main()
{
	int i;

	init_stack();
	for (i = 1;i < 10;i++)
		push(i);
	print_stack("스택 push 9회");
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());
	print_stack("스택 pop 3회");
}