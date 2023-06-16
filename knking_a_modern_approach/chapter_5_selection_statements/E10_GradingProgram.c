// MATHEMATICS GRADE CALCULATOR
// andr-be 06/2023

#include <stdio.h>

int get_score(void);
char get_grade(int);
char switch_grade(int);

int main(void)
{
    while(1){
        int score = get_score();
        char grade = get_grade(score);
        printf("if Grade: %c\n", grade);
        grade = switch_grade(score);
        printf("switch Grade: %c\n", grade);
    }
}

int get_score(void){
    int score = 0;
    printf("Enter numerical grade: ");
    scanf("%d", &score);
    return score;
}
char get_grade(int score){
    if      (score <    0) return 'X';
    else if (score <   60) return 'F';
    else if (score <   70) return 'D';
    else if (score <   80) return 'C';
    else if (score <   90) return 'B';
    else if (score <= 100) return 'A';
    else                   return 'X';
}
char switch_grade(int score){
    switch (10 - score / 10)
    {
    case 0:
    case 1:  return 'A';
    case 2:  return 'B';
    case 3:  return 'C';
    case 4:  return 'D';
    case 5: 
    case 6: 
    case 7: 
    case 8: 
    case 9:  return 'F';  
    default: return 'X';
    }
}