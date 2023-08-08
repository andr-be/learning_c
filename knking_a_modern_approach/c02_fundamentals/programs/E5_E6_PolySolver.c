// POLYNOMIAL SOLVER
// andr-be 2023

#include <stdio.h>

int power(int operand, int exponent)
{
  int result = 1;
  for (int i = 0; i < exponent; i++){
    result *= operand;
  }
  return result;  
}

int question_5(int x)
{
  int y;

  y = (3 * power(x, 5)) 
    + (2 * power(x, 4)) 
    - (5 * power(x, 3)) 
    - (1 * power(x, 2))
    + (7 * power(x, 1)) 
    - (6 * power(x, 0));

  return y;
}

int question_6(int x)
{
  int y;

  y = ((((3 * x + 2) * x - 5) * x - 1) * x + 7) * x - 6;

  return y;
} 
   
int main(){
  int x, y; 
 
  printf("\nPlease enter a value for x: ");
  scanf("%d", &x);

  y = question_5(x);
  printf("\nQ5: %d", y); 

  y = question_6(x);
  printf("\nQ6: %d", y);

  return 0;
}