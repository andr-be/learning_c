// REVERSE POLISH NOTATION
// andr-be 07/2023
/*
    This was a really stupid solution to this, I literally just bundled all of the functionality 
    from rpn_calculator and just chucked it into evaluate_RPN_expression

    original solution was bizarrely overengineered though, so I'm not too fussed
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_SIZE 96 

// prototypes
void rpn_calculator(void);
int evaluate_RPN_expression(const char *expression);
// stack functions
void push(int i);
int pop(void);
void make_empty(void);
bool is_empty(void);
bool is_full(void);
void stack_overflow(void);
void stack_underflow(void);
// character functions
bool is_operator(char c);
bool is_digit(char c);
void perform_operation(char c);

// external variables
int contents[STACK_SIZE];
int top = 0;

int main(void)
{
    for(;;) rpn_calculator();
    
    return 0;
}

void rpn_calculator(void)
{
    char input[STACK_SIZE];
    make_empty();
    printf("Enter an RPN expression: ");
    fgets(input, STACK_SIZE - 1, stdin);
    evaluate_RPN_expression(input);
}

int evaluate_RPN_expression(const char *expression) {
    for (int i = 0; i < STACK_SIZE && expression[i] != '\n'; i++) {
        if (isdigit(expression[i])) {
            push(expression[i] - '0');
            continue;
        }

        else if (is_operator(expression[i])) {
            perform_operation(expression[i]);
            continue;
        }

        else if (expression[i] == '=') {
            int result = pop();
            printf("Value of expression: %d\n", result);
            return result;
        }

        else if (expression[i] == ' ')
            continue;

        else exit(EXIT_SUCCESS);
    }
    return 0;
}

void make_empty(void)
{
    top = 0;
}

bool is_empty(void)
{
    return top == 0;
}

bool is_full(void)
{
    return top == STACK_SIZE;
}

void push(int i)
{
    if (is_full())
      stack_overflow();
    else
      contents[top++] = i;
}

int pop(void)
{
    if (is_empty())
      stack_underflow();
    else
      return contents[--top];

    return 0;
}

bool is_digit(char c) {
    switch (c)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:  return true;
    
    default: return false;
    }
}

bool is_operator(char c) {
    switch (c)
    {
    case '*': 
    case '+': 
    case '-': 
    case '/': return true;

    default:  return false;
    }
}

void perform_operation(char c)
{
    int i_2 = pop(),
        i_1 = pop();

    switch (c)
    {
    case '*':  push(i_1 * i_2);  break;
    case '+':  push(i_1 + i_2);  break;
    case '-':  push(i_1 - i_2);  break;
    case '/':  push(i_1 / i_2);  break;
    }
}

void stack_overflow(void)
{
    printf("Expression is too complex!");
    exit(EXIT_FAILURE);
}

void stack_underflow(void)
{
    printf("Not enough operands in expression!");
    exit(EXIT_FAILURE);
}

