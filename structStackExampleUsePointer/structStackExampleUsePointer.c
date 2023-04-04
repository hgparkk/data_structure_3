/*
프로그램 내용 : 포인터를 이용한 스택구조 예제 프로그램
실습일 : 2023.03.23
실습자 : 박현규
학번 : 202111678
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef struct Student
{
	int id;
	char name[32];
	char dept[32];
} Student;
typedef Student Element;

typedef struct stack 
{                          
	Element data[MAX_STACK_SIZE];
	int top;
} Stack;

void error(char str[])
{
	printf("%s\n", str);
	exit(1);
}

void init_stack(Stack*s) { s->top = -1; }
int is_empty(Stack*s) { return s->top == -1; }
int is_full(Stack*s) { return s->top == MAX_STACK_SIZE; }
int size(Stack*s) { return s->top + 1; }

void push(Stack* s,Element e)
{
	if (is_full(s))
		error("스택 포화 에러");
	s->data[++s->top] = e;
}

Element pop(Stack* s)
{
	if (is_empty(s))
		error("스택 포화 에러");
	return s->data[s->top--];
}

Element peek(Stack* s)
{
	if (is_empty(s))
		error("스택 공백 에러");
	return s->data[s->top];
}

void print_stack(Stack s, char msg[])
{
	int i;
	printf("%s[%2d]=", msg, size(&s));
	for (i = 0;i < size(&s);i++)
		printf("\n\t%-15d %-10s %-20s", s.data[i].id, s.data[i].name, s.data[i].dept);
	printf("\n");
}

Student get_student(int id, char name[], char dept[])
{
	Student s;
	s.id = id;
	strcpy(s.name, name);
	strcpy(s.dept, dept);
	return s;
}

int main()
{
	Stack s;
	Element e;
	init_stack(&s);
	push(&s, get_student(2018130007, "홍길동", "컴퓨터공학과"));
	push(&s, get_student(2018130007, "이순신", "기계공학과"));
	push(&s, get_student(2018130007, "김연아", "체육과"));
	push(&s, get_student(2018130007, "황희", "법학과"));
	print_stack(s,"친구 4명 삽입 후");
	pop(&s);
	print_stack(s,"친구 1명 삭제 후");
	e = peek(&s);
	printf("ID = %d, Name =%s, Dept= %s \n", e.id, e.name, e.dept);
	print_stack(s, "After peek()");
	return 0;
}