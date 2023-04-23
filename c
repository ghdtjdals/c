#include <stdio.h>
#include <stdlib.h>

#define MAX 100
typedef double Element;

Element data[MAX];
int top;
char pf[MAX];
int j = 0;

void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}

void init_stack() { top = -1; }
int is_empty() { return top == -1; }
int is_full() { return top == MAX - 1; }
int size() { return top + 1; }

void push(Element e)
{
    if (is_full())
        error("push 에러");
    data[++top] = e;
}

Element pop()
{
    if (is_empty())
        error("pop 에러");
    return data[top--];
}

Element peek()
{
    if (is_empty())
        error("peek 에러");
    return data[top];
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

void infix_to_postfix(char expr[])
{
    int i = 0;
    char c, op;

    init_stack();
    while (expr[i] != '\0') {
        c = expr[i++];
        if ((c >= '0' && c <= '9')) {
            pf[j++] = c;
            printf("%c", c);
        }
        else if (c == '(')
            push(c);
        else if (c == ')') {
            while (is_empty() == 0) {
                op = (int)pop();
                if (op == '(') break;
                else {
                    pf[j++] = op;
                    printf("%c", op);
                }
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (is_empty() == 0) {
                op = (int)peek();
                if (precedence(c) <= precedence(op)) {
                    pf[j++] = op;
                    printf("%c", op);
                    pop();
                }
                else break;
            }
            push(c);
        }
    }
    while (is_empty() == 0) {
        pf[j++] = (int)peek();
        printf("%c", (int)pop());
    } 
    printf("\n");
}

double calc_postfix(char expr[])
{
    char c;
    int i = 0;
    double val, val1, val2;

    init_stack();
    while (expr[i] != '\0') {
        c = expr[i++];
        if ((c >= '0' && c <= '9')) {
            val = c - '0';
            push(val);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            val2 = pop();
            val1 = pop();
            switch (c) {
            case '+': push(val1 + val2); break;
            case '-': push(val1 - val2); break;
            case '*': push(val1 * val2); break;
            case '/': push(val1 / val2); break;
            }
        }
    }
    return pop();
}

int main()
{
    double calc;
    char expr[MAX] = { "8 / 2 - 3" };

    printf("후위 표기 계산 식: ");
    infix_to_postfix(expr);
    calc = calc_postfix(pf);
    printf("계산 결과: %lf", calc);

    return 0;
}
