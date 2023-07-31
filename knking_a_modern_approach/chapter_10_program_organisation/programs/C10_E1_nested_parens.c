// NESTED PARENTHESES VALIDATOR
// andr-be 07/2023
/*
    Tired of struggling with Lisp bracket madness?
    Unable to accurately pair different types of brackets?
    This program solves all of those issues, by matching the three types!
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

// external variables
char contents[STACK_SIZE];
int top = 0;

// stack functions
void make_empty(void);
bool is_empty(void);
bool is_full(void);
void push(char c);
char pop(void);
void stack_overflow(void);
void stack_underflow(void);
// brace functions
bool left_brace(char c);
bool right_brace(char c);
bool match_brace(char l, char r);

int main(void)
{
  char input[STACK_SIZE];
  printf("Enter parentheses and/or braces: ");
  fgets(input, STACK_SIZE - 1, stdin);

  for (int i = 0; i < STACK_SIZE; i++) 
  {
    if (left_brace(input[i]))
      push(input[i]);

    else if (right_brace(input[i]) && match_brace(pop(), input[i]))
      continue;

    else if (input[i] == '\n' && is_empty()) {
      printf("Parentheses/braces are nested correctly.");
      break;
    }

    else {
      printf("Parentheses/braces are nested incorrectly.");
      break;
    }
  }
  exit(EXIT_SUCCESS);
}

// empty the stack (move the top pointer to 0)
void make_empty(void)
{
    top = 0;
}

// check if the stack is empty
bool is_empty(void)
{
    return top == 0;
}

// check if the stack is full
bool is_full(void)
{
    return top == STACK_SIZE;
}

// add a character to the stack, overflowing if full
void push(char c)
{
    if (is_full())
      stack_overflow();
    else
      contents[top++] = c;
}

// remove a character from the stack, underflowing if empty
char pop(void)
{
    if (is_empty())
      stack_underflow();
    else
      return contents[--top];

    return 0;
}

// end program execution with error message and code
void stack_overflow(void)
{
  printf("\nSTACK OVERFLOW\n");
  exit(EXIT_FAILURE);
}
void stack_underflow(void)
{
  printf("\nSTACK UNDERFLOW\n");
  exit(EXIT_FAILURE);
}

// check that the input char is a left brace
bool left_brace(char c)
{
  switch (c)
  {
  case '(': case '[': case '{':
    return true;
  
  default: 
    return false;
  }
}

// check that the input char is a right brace
bool right_brace(char c)
{
  switch (c)
  {
  case ')': case ']': case '}':
    return true;
  
  default: 
    return false;
  }
}

// check if two braces match
bool match_brace(char l, char r) {
  if (l == '(' && r == ')') return true;
  if (l == '[' && r == ']') return true;
  if (l == '{' && r == '}') return true;

  return false;
}