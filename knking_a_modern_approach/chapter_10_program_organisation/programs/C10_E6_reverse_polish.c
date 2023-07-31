// REVERSE POLISH NOTATION
// andr-be 07/2023
/*
    solves expressions using reverse polish notation (RPN) with a stack-based approach
    operators are placed after their operands instead of between their operands
    e.g. 1 + 2      ->  1 2 +
         1 + 2 * 3  ->  1 2 3 * +

    - when an operand is encountered, push it onto the stack
    - when an operator is encountered, pop its operands from the stack, perform the operation
      on those operands, and then push the result onto the stack
    - the equals (=) operator causes the top stack item to be displayed
    - afterwards, the stack is cleared and the user is prompted to enter a new expression
    - if the stack overflows: "Expression is too complex"
    - if the stack underflows "Not enough operands in expression"
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_SIZE 96 

// prototypes
void rpn_calculator(void);
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

    for (int i = 0; i < STACK_SIZE && input[i] != '\n'; i++) {
        if (isdigit(input[i])) {
            push(input[i] - '0');
            continue;
        }

        else if (is_operator(input[i])) {
            perform_operation(input[i]);
            continue;
        }

        else if (input[i] == '=') {
            printf("Value of expression: %d\n", pop());
        }

        else if (input[i] == ' ')
            continue;

        else exit(EXIT_SUCCESS);
    }
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

