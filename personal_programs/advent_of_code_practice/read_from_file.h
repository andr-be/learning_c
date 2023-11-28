#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_FILEPATH 1024
#define LINE_MAX 1024
#define MAX_WORDS 10000
#define LONGEST_WORD 50
#define MAX_ITER 1024 * 10

typedef struct Word_t {
    int total_count;
    char string[LONGEST_WORD];
} Word_t;

typedef struct WordList {
    int unique_words;
    Word_t list[MAX_WORDS];
} WordList;

FILE *open_file(const char *filename);
void print_file(FILE *file);
int count_words(FILE *file);

WordList generate_word_list(FILE *file);
void add_to_list(WordList *list, char *word);
void print_list(WordList *list); 
void sort_by_count(WordList *list);
void sort_by_alpha(WordList *list);
void swap_words(WordList *list, int idx_a, int idx_b);
int find_first(WordList *list, Word_t word);