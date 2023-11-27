// FILE PRINTER
// andr-be 11/2023
/* 
    Reads a file and prints it line by line, prefixed by line numbers.
*/
#include "read_from_file.h"
#define DEBUG 

int main(void)
{
    char *filename = "test_file.txt";
    #ifdef DEBUG_SMALL
    filename = "test_file_small.txt";
    #endif // DEBUG_SMALL
    FILE *fp = open_file(filename);

    if (fp) {
        print_file(fp);
        printf("Total words: %d\n", count_words(fp));
        WordList tally = generate_word_list(fp);
        #ifdef DEBUG
        for (int i = 0; i < tally.unique_words; i++)
            printf("%3d:\t%25s\t(%d)\n", i, tally.list[i].string, tally.list[i].total_count);
        #endif // DEBUG
    } 
    else { 
        printf("Error: could not open file %s\n", filename);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

/// @brief when given a filename, returns a file pointer
/// @param filename name of file to open (with extension)
/// @return file pointer to opened file, NULL if not found
FILE *open_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return NULL;
    }
    return fp;
}

/// @brief print each line in file, prefixed with a line number
/// @param file a valid file pointer
void print_file(FILE *file) 
{
    for (int line_number = 1; !feof(file); line_number++)
    {
        char *line = calloc(LINE_MAX, sizeof(char));
        fgets(line, LINE_MAX, file);
        printf("%3d:\t%s", line_number, line);
        free(line);
    }
    putchar('\n');
    fseek(file, 0, SEEK_SET);
    return;
}

/// @brief counts the number of individual words in a file
/// @param file pointer to a file
/// @return the number of individual words
int count_words(FILE *file)
{
    int word_count = 0;
    for (int line_number = 0; !feof(file); line_number++)
    {
        char *line = calloc(LINE_MAX, sizeof(char));
        fgets(line, LINE_MAX, file);

        for (char *fp = line; *fp; fp++)
            if (*fp == ' ') word_count++;

        free(line);
    }
    fseek(file, 0, SEEK_SET);
    return word_count;
}

/// @brief creates a new word list from the provided .txt file
/// @param file a file pointer to the .txt file
/// @return a fully sorted and alphabetised list of unique words in the file
WordList generate_word_list(FILE *file)
{
    char word[LONGEST_WORD] = {0};
    WordList new_list = {0};
    int i = 0;

    for (; !feof(file);)
    {
        char c = (char) tolower(fgetc(file));
        if (isalpha(c)) 
        {
            word[i++] = c;
        } 
        if (c == ' ' || c == '\n' || c == '-') 
        {
            Word_t new_word = {
                .total_count = 1
            };
            strcpy(new_word.string, word);
            add_to_list(new_word, &new_list);
            for (int j = 0; j < LONGEST_WORD; j++) 
                word[j] = 0;
            i = 0;
        }
    }
    sort_by_alpha(&new_list);
    sort_by_count(&new_list);
    fseek(file, 0, SEEK_SET);

    return new_list;
}

void add_to_list(Word_t word, WordList *list)
{
    for (int i = 0; i < list->unique_words; i++) {
        if (strcmp(word.string, list->list[i].string) == 0) 
        {
            list->list[i].total_count++;
            return;
        }
    }
    list->list[list->unique_words++] = word;
}

void sort_by_alpha(WordList *list)
{
    int swaps = 0;
    do {
        swaps = 0;
        for (int i = 0; i < list->unique_words - 1; i++) 
        {
            char *a = list->list[i].string, 
                 *b = list->list[i + 1].string;

            if (strcmp(a, b) > 0) {
                swap_words(list, i, i+1);
                swaps++;
            }
        }
    } while (swaps > 0);
}

void sort_by_count(WordList *list)
{
    int swaps = 0;
    // BUBBLE SORT; FUCK IT
    do {
        swaps = 0;
        for (int i = 0; i < list->unique_words - 1; i++) {
            if (list->list[i].total_count < list->list[i + 1].total_count) {
                swap_words(list, i, i + 1);
                swaps++;
            }
        }
    } while (swaps > 0);
}

void swap_words(WordList *list, int idx_a, int idx_b)
{
    if (idx_a < 0 || idx_b < 0 || idx_a > list->unique_words || idx_b > list->unique_words)
        return;

    Word_t temp = list->list[idx_a];
    list->list[idx_a] = list->list[idx_b];
    list->list[idx_b] = temp;
}

bool check_sort(WordList *list)
{
    for (int i = 0; i <= list->unique_words - 1; i++)
        if (list->list[i + 1].total_count > list->list[i].total_count) {
            return false;
        } 

    return true;
}