// AVERAGE GRADES ARRAY
// andr-be 07/2023
/*
    prompts for five quiz grades for each of five students
    computes the total score and average score for each student
    computes average score, high score and low score for each quiz
*/

#include <stdio.h>

void get_quiz_scores(int[5][5]);
void print_student_totals(int[5][5]);
void print_quiz_totals(int[5][5]);

int main(void)
{
    int a[5][5] = {0};
    get_quiz_scores(a);
    print_student_totals(a);
    print_quiz_totals(a);
    return 0;
}

void get_quiz_scores(int scores[5][5]) {
    for (int i = 0; i < 5; i++) {
        printf("Enter Grades for Student %d: ", i + 1);
        scanf("%d %d %d %d %d", 
            &scores[i][0], &scores[i][1], &scores[i][2], &scores[i][3], &scores[i][4]);
    }
}

void print_student_totals(int scores[5][5]) {
    printf("STUDENT TOTALS: ");
    for (int i = 0; i < 5; i++) {
        int sum = 0;
        for (int j = 0; j < 5; j++)
            sum += scores[i][j];
        printf("\n  Student %d:\tTotal: %d\n\t\tAverage: %d", i+1, sum, sum / 5);
    }
}

void print_quiz_totals(int score[5][5]) {
    printf("\nQUIZ TOTALS: ");
    for (int i = 0; i < 5; i++) {
        int lowest = 100, highest = 0;
        int sum = 0;
        for (int j = 0; j < 5; j++) {
            sum += score[j][i];
            lowest = (lowest < score[j][i]) ? lowest : score[j][i];
            highest = (highest > score[j][i]) ? highest : score[j][i];
        }
        printf("\n  Quiz %d:\tAverage: %d", i+1, sum / 5);
        printf("\n\t\tLowest: %d\n\t\tHighest: %d", lowest, highest);
    }
}