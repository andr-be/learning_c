# Chapter 10: Program Organisation - Notes

> As Will Rogers would have said, "There is no such thing as a free variable."

This chapter begins with a discussion of the differences between local variables and external variables. 

We then consider blocks (compound statements containing declarations), the scope rules that apply to local names, external names and names declared in blocks. 

Finally we look at how to organise function prototypes, function definitions and variable declarations and the other parts of a C program.

## 10.1 Local Variables

A variable declared in the body of a function is said to be ***local*** to the function. In the following function, `sum` is a local varaible:

```C
int sum_digits(int n)
{
    int sum = 0;        // local variable

    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }

    return sum;
}
```
Local variables have the following properties:

- ***Automatic storage duration.*** Storage is "automatically" allocated to local variables when the enclosing function is called and deallocated when the function returns. Does not retain its value when its enclosing function returns. If called again, there's no guarantee that the variable will have its old value.

- ***Block scope.*** The scope of a variable is the portion of the program where the variable can be referenced. Local variables are only visible from their declaration to the end of the enclosing function body (or block). This means other functions can use the same names for other purposes.

As C99 doesn't require delclarations to happen at the start of functions, it's possible for a local variable to have a very small scope, being declared close to the end of a function body.

### `static` Local Variables

Putting the word `static` in the delcaration of a local variable causes it to have *static storage duration* instead of automatic storage duration. This means it has a permanent storage location, and retains its value throughout the execution of the program.

A static local variable still has block scope, so it's not visible to other functions. Basically, it's a way to hide data from other functions but retain it for future calls of the same function.

### Parameters

Parameters have the same properties as local variables. The only difference between them is that each parameter is initialised automatically.


## 10.2 External Variables

Functions don't just have access to arguments passed to them, they can also communicate through ***external variables*** declared outside of the body of any function. These are also known as ***global variables*** and have different properties from local variables.

- ***Static storage duration.*** External variables have static storage duration, just like those declared explicitly with `static`. A value stored in an external variable will stay there indefinitely.

- ***File scope.*** An external variable has ***file scope***: it is visible from its point of declaration to the end of the enclosing file. This means an external variable can be accessed (and modified) by all functions that follow its declaration.

### Example: Using External Variables to Implement a Stack

Stacks are an abstract data type that, like arrays, can store multiple data items of the same type. A good physical analogy is to imagine a stack of plates in a restaurant; you can only add to the top or take off the top; by ***pushing*** plates onto the top or ***popping*** plates from the top.

We can implement this in C with an array and a separate integer variable that marks the position of the stack's top. All five functions need access to the `top` variable, and two functions need access to `contents`, so we'll make them both external.

```C
#include <stdbool.b>

#define STACK_SIZE 100

// external variables
int contents[STACK_SIZE];
int top = 0;

void make_empty(void)
{
    top = 0;
}

bool is_empty(void)
{
    return top == 0;
}

bool is_full(void)
{
    return top == STACK_SIZE;
}

void push(int i)
{
    if (is_full())
      stack_overflow();
    else
      contents[top++] = i;
}

int pop(void)
{
    if (is_empty())
      stack_underflow();
    else
      return contents[--top];
}
```

### Pros and Cons of External Variables

External variables are convenient when many functions must share a variable or when a few functions share a larghe number of variables. In almost all cases however, it's better for functions to communicate through parameters rather than by sharing variables.

- If we change an external variable during program maintenance we'll need to check every function in the same file to see how the change affects it.

- If an external variable is assigned an incorrect value, it can be very difficult to debug exactly what caused the issue.

- Functions that rely on external variables are really difficult to re-use in other programs without cautious scalpel-work.
  
> *According to the book, some C programmers have a propensity to just like, use fucking a single variable to control all the `i`s in for loops across the entire program?! What the fuck.*
> 
> andr-be

When you use external variables, make sure they have meaningful names. If you find yourself using names like `i` and `temp` for your external variables, that's probably a clue you're being an idiot.

***

### Program: Guessing a Number

This program generates a random number between 1 and 100, which the user attempts to guess in as few tries as possible.

```txt
Guess the secret number between 1 and 100.

A new number has been chosen.
Enter guess: 55
Too low; try again.
Enter guess: 65
Too high; try again.
Enter guess: 60
Too high; try again.
Enter guess: 58
You won in 4 guesses!

Play again? (Y/N) Y

A new number has been chosen.
Enter guess: 78
Too high; try again.
Enter guess: 34
You won in 2 guesses!

Play again? (Y/N) n
```

```C
// guess.c - asks user to guess a hidden number

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBER 100

// external variable
int secret_number;

// prototypes
void initialise_number_generator(void);
void choose_new_secret_number(void);
void read_guesses(void);

int main(void)
{
    char command;
    printf("Guess the secret number between 1 and %d.\n\n", MAX_NUMBER);
    initialise_number_generator();
    do {
        choose_new_secret_number();
        printf("A new number has been chosen.\n");
        read_guesses();
        printf("Play again? (Y/N) ");
        scanf(" %c", &command);
        printf("\n");
    } while (command == 'y' || command == 'Y');

    return 0;
}

// initialises the random number generator using the time of day
void initialise_number_generator(void) 
{
    srand((unsigned) time(NULL))
}

// randomly select number between 1 and MAX_NUMBER and store it in secret_number
void choose_new_secret_number(void)
{
    secret_number = rand() % MAX_NUMBER + 1;
}

// reads the users guesses and evaluates them; returning if they're correct
void read_guesses(void)
{
    int_guess, num_guesses = 0;

    for (;;) {
        num_guesses++;
        printf("Enter guess: ");
        scanf("%d", &guess);
        if (guess == secret_number) {
            printf("You won in %d guesses!\n\n", num_guesses);
            return;
        } else if (guess < secret_number)
            printf("Too low; try again.\n");
        else
            printf("Too high; try again.\n");
    }
}
```

We can, and probably should, refactor this into a form that doesn't rely on external variables.

```C
// guess2.c
// asks user to guess a hidden number

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBER 100

// prototypes
void initialise_number_generator(void);
int new_secret_number(void);
void read_guesses(int secret_number);

int main(void) {
    char command;
    int secret number;

    printf("Guess the secret number between 1 and %d.\n\n", 
            MAXNUMBER);
    initialize_number_generator();
    do {
        secret_number = new_secret_number();
        printf("A new number has been chosen.\n");
        read_guesses(secret_number);
        printf("Play again? (Y/N) ");
        scanf(" %c", &command);
        printf("\n");
    } while (command == 'y' || command == 'Y');

    return 0;
}

// initialises the random number generator using the time of day
void initialise_number_generator(void)
{
    srand((unsigned) time(NULL));
}

// returns a randomly chosen number between 1 and MAX_NUMBER
int new_secret_number(void)
{
    return rand() % MAX_NUMBER + 1;
}

// reads user guesses blah blah
void read_guesses(void)
{
    int_guess, num_guesses = 0;

    for (;;) {
        num_guesses++;
        printf("Enter guess: ");
        scanf("%d", &guess);
        if (guess == secret_number) {
            printf("You won in %d guesses!\n\n", num_guesses);
            return;
        } else if (guess < secret_number)
            printf("Too low; try again.\n");
        else
            printf("Too high; try again.\n");
    }
}
```

## 10.3 Blocks

C allows compound statements to contain declarations as well as statements.

```C
{  declarations  statements  }
```

Here's an example of a block:

```C
if (i > j) {
    // swap values of i and j
    int temp = i;
    i = j;
    j = temp;
}
```

The storage duration of a variable declared in a block is automatic: storage for the variable is allocated when the block is entered and deallocated when the block is exited, unless you declare it as `static`.

The body of a function is also a block. Blocks are useful when we need variables for temporary use. In this example, we used a block to swap the two values. This has two advantages:

- It avoids cluttering the declarations at the beginning of the function body.
- It helps to reduce name conflicts. 

C99 allows variables to be declared anywhere within a block, just as it allows variables to be declared anywhere within a function.

## 10.4 Scope

In a C program, the same identifier may have several different meanings. C's scope rules enable the programmer (and compiler) to determine which meaning is relevant at a given point in the program.

When a declaration inside a block names an identifier that's already visible, the new declaration temporarily "hides" the old one, and the identifier takes on a new meaning. At the end of the block, the identifier regains its old meaning.

```C
// a somewhat extreme example

int i;              // declaration 1

void f(int i) {     // declaration 2
    i = 1;         
}

void g(void) {
    int i = 2;      // declaration 3

    if (i > 0) {
        int i;      // declaration 4
        i = 3;
    }

    i = 4;
}

void h(void) {
    i = 5;
}
```

- in declaration 1, i is a variable with static storage duration and file scope
- in declaration 2, i is a parameter with block scope
- in declaration 3, i is an automatic variable with block scope
- in declaration 4, i is also automatic and has block scope

i is used five times. C's scope rules allow us to determine the meaning of i in each case:

- The `i = 1` assignment refers to the parameter in Declaration 2, not the variable in Declaration 1, since Declaration 2 hides Declaration 1.
- The `i > 0` test refers to the variable in Declaration 3, since Declartation 3 hides Declaration 1 and Declaration 2 is out of scope.
- The `i = 3` assignment refers to the variable in Declaration 4, which hides Declaration 3.
- The `i = 4` assignment refers to the variable in Declaration 3. It can't refer to Declaration 4, which is out of scope.
- The `i = 5` assignment refers to the variable in Declaration 1.

> what the fuck was the point of this section lmao

## 10.5 Organising a C Program

Now that we've seen the major elements that make up a C program, it's time to develop a strategy for their arrangement. For now, we'll assume that a program always fits into a single file.

So far, we've seen that a program may contain the following:

- **Preprocessing directives** - do not take place until the line on which they appear
- **Type definitions** - types can't be used until they've been defined
- **Declarations of external variables** - variables can't be used until declared
- **Function prototypes** - required before call in C99
- **Function definitions** - required before call in C99

One possible ordering common in 2008 and representative of the programs we've written so far, is the following:

1. `#include` directives
2. `#define` directives
3. `typedef` declarations
4. Declarations of external variables
5. Prototypes for functions other than `main`
6. Definition of `main`
7. Definitiions of other functions

It's also useful to precede each function with a quick comment that explains its purpose (the ***why*** is important, the how is already evident). It's also useful to list any side effects if it has any.

***

### Program - Classifying a Poker Hand

To demonstrate how we might organise a C program, let's attempt something a little bit more complex than our previous examples. 

The program will read and classify a poker hand. Each card in the hand has a

- **SUIT**: Clubs, Diamonds, Hearts and Spades 
- **RANK**: two, three, four, five, six, seven, eight, nine, ten, Jack, Queen, King and Ace

We won't allow Jokers and will assume Aces are high. The program will read a hand of 5 cards and then classify that hand into one of the following categories:

- **straight flush** - both a straight and a flush
- **four-of-a-kind** - four cards of the same rank
- **full house** - a three-of-a-kind and a pair
- **flush** - five cards of the same suit
- **straight** - five cards with consecutive ranks
- **two pairs**
- **pair** - two cards of the same rank
- **high card** - any other hand

If a hand falls into two or more categories, the program will choose the best one. For input purposes, we'll abbreviate the ranks and suits as follows:

```C
RANKS = {2, 3, 4, 5, 6, 7, 8, 9, t, j, q, k, a}
SUITS = {c, d, h, s}
```

If the user enters an illegal card or tries to enter the same card twice, the program will ignore the card, issue an error message and then request another card. Entering the number 0 will cause the program to terminate. The program's output should resemble the following:

```txt
Enter a card: 2s
Enter a card: 5s
Enter a card: 4s
Enter a card: 3s
Enter a card: 6s
Straight Flush!

Enter a card: 8c
Enter a card: as
Enter a card: 8c
Duplicate card; ignored.
Enter a card: 7c
Enter a card: ad
Enter a card: 3h
Pair!

Enter a card: 6s
Enter a card: d2
Bad card; ignored.
Enter a card: 2d
Enter a card: 9c
Enter a card: 4h
Enter a card: ts
High card!

Enter a card: 0
```

From this description, we see the program has 3 tasks, so it would make sense to divide it into 3 functions:

1. `read_cards()` - Read a hand of five cards
2. `analyse_hand()` - Analyse the hand for pairs, straights and so forth
3. `print_result()` - Print the classification of the hand

`main` does nothing but call these functions inside an endless loop. The functions will need to share a fairly large amount of information, so we'll have to use external variables.

```C
// initial sketch

/* #include directives go here */

/* #define directives go here */

/* declarations of external variables go here */

/* prototypes */
void read_cards(void);
void analyse_hand(void);
void print_result(void);

// calls read_cards, analyse hand and print_result repeatedly
int main(void)
{
    for (;;)
    {
        read_cards();
        analyse_hand();
        print_result();
    }
}

// reads cards into ext. variables, checks for bad and duplicate cards
void read_cards(void)
{
    ...
}

// determines whether the hand contains a valuable result, stores into ext. vars
void analyse_hand(void)
{
    ...
}

// notifies the user of the result, using the ext. vars set by analyse_hand
void print_result(void)
{
    ...
}
```

The most important unresolved question that remains is how to represent the hand of cards. `analyse_hand` will need to know how many cards are in each rank and each suit. This suggests that we use two arrays, `num_in_rank` and `num_in_suit`.

We'll encode ranks as numbers between 0 and 12, and suits as numbers between 0 and 3. 

We'll also need a third array `card_exists` so that `read_cards` can detect duplicate cards. Each time `read_cards` reads a card with rank `r` and suit `s`, it checks whether the value of `card_exists[r][s]` is `true`. If so, it was already entered. If not, `read_cards` assigns `true` to `card_exists[r][s]`.

Both `read_cards` and `analyse_hand` will need access to the `num_in_rank` and `num_in_suit` arrays, so we'll make them external variables. As a rule, variables should only be made external if necessary.

```C
// poker.c
// classifies a poker hand

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

// external variables
int num_in_rank[NUM_RANKS];
int num_in_suit[NUM_SUITS];
bool straight, flush, four, three;
int pairs;  // can be 0, 1, or 2

// prototypes
void read_cards(void);
void analyse_hand(void);
void print_result(void);

// calls the three main functions in a loop
int main(void)
{
    for (;;) {
        read_cards();
        analyse_hand();
        print_result();
    }
}

// reads the cards into ext. vars, checks for and rejects bad/duplicate cards
void read_cards(void)
{
    bool card_exists[NUM_RANKS][NUM_SUITS];
    char ch, rank_ch, suit_ch;
    int rank, suit;
    bool bad_card;
    int cards_read = 0;

    for (rank = 0; rank < NUM_RANKS; rank++) {
        num_in_rank[rank] = 0;
        for (suit = 0; suit < NUM_SUITS; suit++)
            card_exists[rank][suit] = false;
    }

    for (suit = 0; suit < NUM_SUITS; suit++)
        num_in_suit[suit] = 0;

    while (cards_read < NUM_CARDS) {
        bad_card = false;

        printf("Enter a card: ");

        rank_ch = getchar();
        switch (rank_ch) {
            case '0':           exit(EXIT_SUCCESS);
            case '2':           rank =  0; break;
            case '3':           rank =  1; break;
            case '4':           rank =  2; break;
            case '5':           rank =  3; break;
            case '6':           rank =  4; break;
            case '7':           rank =  5; break;
            case '8':           rank =  6; break;
            case '9':           rank =  7; break;
            case 't': case 'T': rank =  8; break;
            case 'j': case 'J': rank =  9; break;
            case 'q': case 'Q': rank = 10; break;
            case 'k': case 'K': rank = 11; break;
            case 'a': case 'A': rank = 12; break;
            default:            bad_card = true;
        }

        suit_ch = getchar();
        switch (suit_ch) {
            case 'c': case 'C': suit = 0; break;
            case 'd': case 'D': suit = 1; break;
            case 'h': case 'H': suit = 2; break;
            case 's': case 'S': suit = 3; break;
            default:            bad_card = true;
        }

        while ((ch = getchar()) != '\n')
            if (ch != ' ') bad_card = true;

        if (bad_card)
            printf("Bad card; ignored.\n");
        else if (card_exists[rank][suit])
            printf("Duplicate card; ignored.\n");
        else {
            num_in_rank[rank]++;
            num_in_suit[suit]++;
            card_exists[rank][suit] = true;
            cards_read++;
        }
    }
}

// determines whether the hand contains a valuable result, stores into ext. vars
void analyse_hand(void)
{
    int num_consec = 0;
    int rank, suit;
    straight = false;
    flush = false;
    four = false;
    three = false;
    pairs = 0;

    // check for flush
    for (suit = 0; suit < NUM_SUITS; suit++)
        if (num_in_suit[suit] == NUM_CARDS)
            flush = true;

    // check for straight
    rank = 0;
    while (num_in_rank[rank] == 0) rank++;
    for (; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
        num_consec++;
    if (num_consec == NUM_CARDS) {
        straight = true;
        return;
    }

    // check for 4-of-a-kind, 3-of-a-kind and pairs
    for (rank = 0; rank < NUM_RANKS; rank++) {
        if (num_in_rank[rank] == 4) four = true;
        if (num_in_rank[rank] == 3) three = true;
        if (num_in_rank[rank] == 2) four = pairs++;
    }
}

// notifies the user of the result, using the ext. vars set by analyse_hand
void print_result(void)
{
    if (straight && flush)  printf("Straight Flush!");
    else if (four)          printf("Four of a Kind!");
    else if (three && 
             pairs == 1)    printf("Full house!");
    else if (flush)         printf("Flush!");
    else if (straight)      printf("Straight!");
    else if (pairs == 2)    printf("Two Pairs!");
    else if (pairs == 1)    printf("Pair.");
    else                    printf("High card...");

    printf("\n\n");
}
```

## Organising C Programs: Q&A

Q: What impact do local variables with static storage duration have on recursive functions?

A: When a function is called recusrively, fresh copies are made of its automatic variales for each call. This doesn't occur for static variables, though. Instead, ***all calls of the function share the same static variables***.
