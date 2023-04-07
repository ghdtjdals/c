#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef char Element;

Element data[MAX];
int top;

void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}

//매우 중요한 스택의 공통 기본 연산
void init_stack() { top = -1; }
int is_empty() { return top == -1; }
int is_full() { return top == MAX - 1; }
int size() { return top + 1; }

//3가지 스택의 필수 개념 함수

void push(Element e)
{
    if (is_full())
        error("에러");
    data[++top] = e;
}

Element pop()
{
    if (is_empty())
        error("에러");
    return data[top--];
}

Element peek()
{
    if (is_empty())
        error("에러");
    return data[top];
}


int main(void)
{
    int i, j;
    char a[MAX], b[MAX];

    printf("입력: ");
    scanf_s("%s", &a, MAX);
    j = strlen(a);

    for (i = 0; i < j; i++)
        b[i] = a[i];
    for (i = 0; i < j; i++)
        push(a[i]);
    for (i = 0; i < j; i++)
        a[i] = pop();
    for (i = 0; i < j; i++)
    {
        if (a[i] == b[i])
            continue;
        else
        {
            printf("애너그램이 아닙니다.");
            return 0;
        }
    }
    printf("애너그램입니다.");
    return 0;
}
