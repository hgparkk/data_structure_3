/*
프로그램 내용 : 회문인지 아닌지 확인하는 프로그램
실습일 : 2023.04.08
실습자 : 박현규
학번 : 202111678
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void check_palindrome(char expr[])
{
	char c;
	char renew[80];
	char reverse[80];
	int i = 0;
	int j = 0;
	init_stack();
	while (expr[i] != '\0')
	{
		c = expr[i++];
		if ((c >= 'A') && (c <= 'Z'))
		{
			c = c - 'A' + 'a';
			renew[j++] = c;
			push(c);
		}
		else if (c == '.' || c == ',' || c == '!' || c == '?'|| c == ' '|| c == '\'')
		{

		}
		else
		{
			renew[j++] = c;
			push(c);
		}
	}
	renew[j] = '\0';
	i = 0;
	while (is_empty() == 0)
		reverse[i++] = pop();
	reverse[i] = '\0';
	if (strcmp(renew, reverse) == 0)
		printf("이 문자열은 회문입니다.");
	else
		printf("이 문자열은 회문이 아닙니다.");
}

int main()
{
	char expr[80];
	printf("문자열을 입력하세요 >>");
	scanf("%[^\n]", &expr);
	check_palindrome(expr);
}