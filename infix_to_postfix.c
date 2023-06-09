#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char stack[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

void push(Stack *s, char element) {
    if (s->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    s->stack[++s->top] = element;
}

char pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return s->stack[s->top--];
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return -1;
}

void infixToPostfix(char *expression, char *postfix) {
    Stack stack;
    initialize(&stack);
    int i, j;

    for (i = 0, j = 0; expression[i] != '\0'; i++) {
        if (expression[i] >= 'a' && expression[i] <= 'z') {
            postfix[j++] = expression[i];
        } else if (isOperator(expression[i])) {
            while (stack.top != -1 && precedence(stack.stack[stack.top]) >= precedence(expression[i])) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, expression[i]);
        } else if (expression[i] == '(') {
            push(&stack, expression[i]);
        } else if (expression[i] == ')') {
            while (stack.top != -1 && stack.stack[stack.top] != '(') {
                postfix[j++] = pop(&stack);
            }
            if (stack.top == -1) {
                printf("Invalid expression\n");
                return;
            }
            pop(&stack);
        }
    }

    while (stack.top != -1) {
        if (stack.stack[stack.top] == '(') {
            printf("Invalid expression\n");
            return;
        }
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strlen(infix) - 1] = '\0';

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
