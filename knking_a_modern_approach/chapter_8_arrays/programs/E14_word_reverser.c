// WORD REVERSER
// andr-be 07/2023
/*
    reverses the words in a sentence
    > Enter a sentence: you can cage a swallow can't you?
    > Reversal of sentence: you can't swallow a cage can you?
    
    read characters one by one and store them in a one-dimensional array
    have the loop stop at terminating character, save in separate ch variable
    use second loop to search backwards to beginning of last word
    print the last word, then search backward for the next to last word
    repeat until the beginning of the array is reached
    print the terminating character
*/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFFSIZE 50 

int get_last_char_idx(char input[BUFFSIZE]);
int get_next_space_idx(char input[BUFFSIZE], int c_index);
bool is_terminator(char input);

int main(void)
{
    char buffer[BUFFSIZE],
         terminator;
    int start_index = 0,
        end_index = 0;

    printf("Enter a sentence: ");
    fgets(buffer, BUFFSIZE-1, stdin);

    // walk backwards through the buffer until you get a non \0 character
    end_index = get_last_char_idx(buffer);

    // walk backwards until you reach a space
    while (end_index > 0) {
        start_index = get_next_space_idx(buffer, end_index);
        for (int i = start_index; i < end_index; i++) {
            if (isalpha(buffer[i]) || buffer[i] == '\'')
                printf("%c", buffer[i]);
            if (is_terminator(buffer[i])) 
                terminator = buffer[i];
        }
        if (start_index != 0) printf("%c", ' ');
        end_index = start_index;
    }
    putchar(terminator);
    return 0;
}

int get_last_char_idx(char input[BUFFSIZE]) {
    for (int i = 0; i < BUFFSIZE; i++)
        if (input[i] == '\n') return i;
    
    return BUFFSIZE;
}

int get_next_space_idx(char input[BUFFSIZE], int c_index) {
    for (int i = c_index - 1; i > 0; i--)
        if (input[i] == ' ') return i;
    
    return 0;
}

bool is_terminator(char input) {
    if (input == '.' || input == '?' || input == '!') 
        return true;
    else 
        return false;
}