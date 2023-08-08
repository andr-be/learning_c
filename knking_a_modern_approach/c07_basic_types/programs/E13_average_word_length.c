// AVERAGE WORD LENGTH CALCULATOR
// andr-be 07/2023
/*
    Calculates the average word length for a given sentence.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/// @brief holds the ongoing totals and sums
typedef struct Total {
    float letters;
    float count;
    float words;
} Total;

Total update(Total);
void print(Total);

int main(void)
{
    Total total = { .letters = 0, .count = 0, .words = 0 };
    printf("Enter a sentence: ");
    for ( char ch = getchar(); ch != '\n'; ch = getchar() ) {
        total.count += (isalpha(ch)) ? 1.0f : 0.0f; 
        if (ch == ' ') total = update(total); 
    }
    total = update(total);
    print(total);
    return 0;
}

/// @brief updates the totals to reflect the end of a word
/// @param input the current totals
/// @return the updated totals
Total update(Total input) {
    input.letters += input.count;
    input.words += 1.0f;
    input.count = 0.0f;
    return input;
}

/// @brief displays the current number of words, letters and the average
/// @param input current totals
void print(Total input) {
    printf("\nWORDS: %1.0f\nLETTERS: %1.0f\n", input.words, input.letters);
    printf("AVERAGE: %3.2f", input.letters / input.words);
}