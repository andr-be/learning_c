// REPDIGIT4.c
// andr-be 07/2023
/*
    Looping program that continually asks the user to provide
    a number, and then breaks down what digits are in the number.
*/

#include <stdbool.h>
#include <stdio.h>

int main(void)
{
  while (true) {
      int digit_seen[10] = {0},
          digit;
      long n;
  
      printf("\nEnter a number (0 to exit): ");
      scanf("%ld", &n);
      if (n == 0) break;
  
      for (; n > 0; n /= 10) {
          digit = n % 10;
          digit_seen[digit] += 1;
      }
  
      printf("Digit:\t\t");
      for (int i = 0; i < 10; i++) 
          printf("%d  ", i);
  
      printf("\nOccurences:\t");
      for (int i = 0; i < 10; i++) 
          printf("%d  ", digit_seen[i]);
      }
  return 0;
}
