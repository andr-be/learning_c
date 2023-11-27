#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define LINE_MAX 1024
#define MAX_WORDS 10000
#define LONGEST_WORD 50
#define MAX_ITER 1024 * 10

typedef struct Word_t {
    char string[LONGEST_WORD];
    int total_count;
} Word_t;

typedef struct WordList {
    Word_t list[MAX_WORDS];
    int unique_words;
} WordList;

FILE *open_file(const char *filename);
void print_file(FILE *file);
int count_words(FILE *file);

WordList generate_word_list(FILE *file);
void sort_by_count(WordList *list);
void sort_by_alpha(WordList *list);
void add_to_list(Word_t word, WordList *list);
void swap_words(WordList *list, int idx_a, int idx_b);
bool check_sort(WordList *list);