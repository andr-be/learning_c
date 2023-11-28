// FILE PRINTER
// andr-be 11/2023
/* 
    Capable of generating a list of unique words when privded an ASCII text file
    that list is sorted in terms of count, and within equivalent counts is printed alphabetically
*/

#include "read_from_file.h"

int main(int argc, char *argv[])
{
    char filename[MAX_FILEPATH] = {0};
    #ifdef DEBUG
    filename = "test_file_small.txt";
    #else 
    if (argc < 2) {
        fprintf(stderr, "Error: no filename provided!");
        return EXIT_FAILURE;
    }
    strcpy(filename, argv[1]);
    #endif  // DEBUG

    FILE *fp = open_file(filename);

    if (!fp) {
        fprintf(stderr, "Error: could not open file %s!\n", filename);
        fclose(fp);
        return EXIT_FAILURE;
    } 

    print_file(fp);
    printf("Total words: %d\n\n\n", count_words(fp));

    WordList tally = generate_word_list(fp);
    if (tally.unique_words < 1) {
        fprintf(stderr, "Error: no unique words found in %s!\n", filename);
        fclose(fp);
        return EXIT_FAILURE;
    }
    print_list(&tally);

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

    while (!feof(file))
    {
        char c = (char) tolower(fgetc(file));
        if (isalpha(c)) {
            word[i++] = c;
        } 
        if (c == ' ' || c == '\n' || c == '-') {
            if (strcmp(word, "") != 0) {
                add_to_list(&new_list, word);
            }
            for (int j = 0; j < LONGEST_WORD; j++) { word[j] = 0; }
            i = 0;
        }
    }
    fseek(file, 0, SEEK_SET);

    sort_by_alpha(&new_list);
    sort_by_count(&new_list);
    return new_list;
}

/// @brief checks to see if a word is unique and adds it to the list or otherwise it increments its count
/// @param list a WordList you want to add a Word to
/// @param word the new Word_t you want to add to the list
void add_to_list(WordList *list, char *word)
{
    if (list->unique_words >= MAX_WORDS)  {
        fprintf(stderr, "ERROR: MAX_WORDS reached in WordList (%d)", MAX_WORDS);
        return;
    }

    Word_t new_word = { .total_count = 1 };
    strcpy(new_word.string, word);

    int index = find_first(list, new_word);
    if (index == -1) 
        list->list[list->unique_words++] = new_word;
    else
        list->list[index].total_count++;
}

/// @brief returns the index of the first match in the list, otherwise returns -1
/// @param list the list to search in
/// @param word the word to search for
/// @return index of first match or -1 if no matches
int find_first(WordList *list, Word_t word)
{
    // for every unique word
    for (int i = 0; i < list->unique_words; i++) {
        char *a = word.string,
             *b = list->list[i].string;
        // check to see if any match, returning the index if one does
        if (strcmp(a, b) == 0) return i;
    }
    return -1;
}

/// @brief bubble sort the list in alphabetical order
/// @param list the list to be sorted
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

/// @brief bubble sort the list in descending count order
/// @param list the list to be sorted
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

/// @brief swaps two words in a list at the two given indexes (with bounds checking)
/// @param list list to perform swap within
/// @param idx_a index of the first word
/// @param idx_b index of the second word
void swap_words(WordList *list, int idx_a, int idx_b)
{
    if (idx_a < 0 || idx_b < 0 || idx_a > list->unique_words || idx_b > list->unique_words)
        return;

    Word_t temp = list->list[idx_a];
    list->list[idx_a] = list->list[idx_b];
    list->list[idx_b] = temp;
}

/// @brief print the supplied WordList in a pleasing format
/// @param list the WordList to be printed
void print_list(WordList *list) 
{
    for (int i = 0; i < list->unique_words; i++)
        printf("%3d:\t%25s\t(%d)\n", i, list->list[i].string, list->list[i].total_count);
}