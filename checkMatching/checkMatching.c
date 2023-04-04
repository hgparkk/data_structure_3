
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

void main()
{
	char expr[4][80] = { "{A[(i+1)]=0;}","if ((i == 0) && (j == 0)","A[(i+1])=0;","A[i]=f)(;" };
	int errCode, i;
	for (i = 0;i < 4;i++) {
		errCode = check_matching(expr[i]);
		if (errCode == 0)
			printf(" 정상:%s \n", expr[i]);
		else
			printf(" 오류:%s (조건%d 위반)\n",expr[i],errCode);
	}
}