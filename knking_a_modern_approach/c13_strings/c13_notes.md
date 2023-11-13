# Chapter 13: Strings

> *It's difficult to extract sense from strings, but they're the only communication coin we can count on.*

We've utilised methods that work on `char` variables and arrays of `char`s, but we haven't yet established a convenient way of handling *sequences of characters* (strings). This chapter will cover **string constants** (or ***literals***, in C terminology) and **string variables**, which can change during the execution of a program.

## 13.1 String Literals

A string literal is a sequence of characters enclosed within double quotes:

```C
"When you come to a fork in the road, take it."
```

We first encountered this type of string in Chapter 2 as format strings in calls of `printf` and `scanf`.

### Escape Sequences in String Literals

String literals may contain the same escape sequences as character constants, such as the newline character:

```C
"Candy\nIs dandy\nBut liquor\nIs quicker. \n  --Ogden Nash\n"
```

```txt
Candy
Is dandy
But liquor
Is quicker.
  --Ogden Nash
```

Octal and Hexadecimal escapes are also legal in string literals, but they're less commonly used.

Be careful when using octal and hexadecimal escape sequences in string literals. An octal escape ends after three digits or with the first non-octal character. For example, the string `"\1234"` contains two characters: (`\123` and `4`) and the string `"\189"` contains three characters (`\1`, `8` and `9`).

A hexadecimal escape on the other hand, isn't limited to three digits; it doesn't end until the first non-hex character. Consider what happens if a string contains the escape `\xfc` which represents the character `ü` in a common extension of ASCII. 

The string `"Z\xfcrich"` (`"Zürich"`) has six characters (`Z`, `\xfc`, `r`, `i`, `c` and `h`), but the string `"\xfcber"` (`über`) is read as only having two: `\xfcbe` and `r`.

Fortunately, most compilers will object to the latter string, as hex escapes are usually limited to the range `\x0`-`\xff`.

### Continuing a String Literal

If a string literal is too long to fit on a single line, C allows us to continue it on the next line if we end it with a backslash (`\`):

```C
printf("When you come to a fork in the road, take it.   \
--Yogi Berra");
```

In general, the `\` character can be used to join two or more lines of a program into a single line, this is called ***splicing***, and will be described more thoroughly in the next chapter.

The `\` technique has one drawback: the string must continue at the end of the next line, which breaks the program's indented structure. However, when two or more string literals are adjacent (only separated by whitespace) the compiler will join them into a single string.

```C
printf("When you come to a fork in the road, take it."
        "--Yogi Berra");
```

### How String Literals are Stored

When we call `printf` and supply a string literal as an argument, what are we actually passing? C treats string literals as character arrays.

When a C compiler encounters a string literal of length `n` in a program, it sets aside `n + 1` bytes of memory for the string: the characters in the string plus the null character to mark the end.

> Don't confuse the null character (`'\0'`) with the zero character (`0`): the null character has the code 0, the zero character has a different code. (48 in ASCII)

The string literal `"abc"` is stored as an array of four characters:

```C
"abc" == ['a']['b']['c']['\0']
```

or may be empty; the string "" is stored as a single null character:

```C
"" == ['\0']
```

Because it treats them as arrays, string literals behave like pointers of type `char *`. Both `printf` and `scanf`, for example, expect a value of type `char *` as their first argument. When `printf("abc")` is called, it's passed the address of `"abc"` (a pointer to where `a` is stored in memory).

### Operations on String Literals

We can use a string literal wherever C allows a `char *` pointer, including on the right hand side of a pointer assignment. The assignment doesn't copy the characters in `"abc"`, it just makes `p` point to the first character.

```C
char *p;

p = "abc";
```

C allows pointers to be subscripted, so we can subscript using string literals:

```C
char ch;

ch = "abc"[1];

printf("%c", ch);   // prints: b

// [0] == a, [2] == c, [3] == \0
```

The following function converts a number between 0 and 15 into a character that represents the equivalent hex digit:

```C
char digit_to_hex_char(int digit)
{
    return "0123456789ABCDEF"[digit];
}
```

Attempting to modify a string literal causes undefined behaviour, and any program that tries to change a string literal may crash or behave eratically.

```C
char *p = "abc";

*p = 'd';           // WRONc1I1â1I6A¬¬Ñá4♦
```

### String Literals versus Character Constants

A string literal containing a single character is not the same as a character constant. `"a" != 'a'`

The string literal `"a"` is represented by a pointer to a memory location that contains the characters `a` & `\0`. The character constant `a` is represented by an integer (the numerical code for the character).

Never use a character when a string is required, or vice versa. `printf("\n");` is legal, `printf('\n');` would not be.

## 13.2 String Variables

C doesn't have a special `string` type for declaring string variables: any one-dimensional array of characters can be used to store a string, with the understanding that the string is terminated by a null character.

This simple approach comes with particular difficulties: 

- it is hard to tell whether an array of characters is being used as a string
- when we write our own string handling functions we need to deal with the null character

Finding null is also typically the fastest way to determine the length of a string.

If we need a variable capable of storing a string of up to 80 characters, we have to declare the array with an array size of 81:

```C
#define STR_LEN 80
...
char str[STR_LEN+1];
```

We define `STR_LEN` to be `80` rather than `81` to demonstrate that it should be 80 characters max, and just `+1` when using it in declarations. This is a common practice among C programmers. 

Failing to do this causes the well known category of error in which insane zalgo garbage is printed to the terminal instead of text, among other nose-goblin related terrors.

Declaring a character array to have length `STR_LEN + 1` doesn't mean that it always contains a string of `STR_LEN` characters, as this depends on where the null character is it can hold strings of various lengths, ranging from empty to the full length of `STR_LEN`.

### Initialising a String Variable

A string variable can be initialised at the same time it's declared; the compiler will put the characters from `"June 14"` int the `date1` array then add a null character to terminate the string.

```C
char date1[8] = "June 14";
// is equivalent to
char date1[8] = {'J', 'u', 'n', 'e', '1', '4', '\0'};
// date1 [ J ][ u ][ n ][ e ][   ][ 1 ][ 4 ][\0 ]
```

When an array initialiser is shorter than the total length of the array in C, all remaining elements are initialised to `0`. By initialising the leftover elements of a character array to `\0`, the compiler is simply following the same rule.

```C
char date2[9] = "June 15";
// date2 [ J ][ u ][ n ][ e ][  ][ 1 ][ 4 ][\0 ][\0 ]
```

It's illegal for C string initialisers to be longer than the string variable they're to be stored in. However, it's actually possible (in 2008) to assign incorrectly if the lengths are the same; this makes the sequence unusable as a string because it omits the null character.

You can also omit the number within the initialiser to have the compiler autocalculate it. This can be useful in the event you're declaring a particularly long string and calculating it by hand would be longwinded. (???)

```C
char date4[] = "June 16";
```

### Character Arrays versus Character Pointers

`char date[] = "June 14";`

- characters stored in `date` can be modified, like elements of an array
- `date` is an array name

`char date* = "June 14";`

- `date` points to a string literal, and cannot be modified
- `date` is a variable that can be made to point to other strings during runtime

If we need a string that can be modified, it's our responsibility to set up an array of characters in which to store the string. The declaration `char *p;` causes the compiler to only set aside enough memory for a pointer variable; not for a full string.

Before we can use `p` as a string, it must point to an array of characters, like by making it point to a string variable:

```C
char str[STR_LEN+1], *p;

p = str;
```

`p` now points to the first character of `str`, so we can use `p` as a string. Another possibility is to make `p` point to a dynamically allocated string.

Using an uninitialised pointer variable as a string is a serious error as trying to write or read characters into or from a random area of memory is a severe case of undefined behaviour.

## 13.3 Reading and Writing Strings

Writing a string is simple enough, as `printf` and `puts` are easy to handle functions.

Reading a string is somewhat harder; there's a possibility when reading that the input string may be longer than the variable in which you attempt to store it.

To read a string in a single step, we can either use `scanf` or `gets`, or we can read them one character at a time.

### Writing Strings Using `printf` and `puts`

The `%s` conversion specifier allows `printf` to write a string. 

```C
char str[] = "Are we having fun yet?";

printf("%s!\n", str);    // Are we having fun yet?!
```

`printf` writes characters one by one until it encounters a null character. If it's missing, it'll continue past the end of the string until it eventually finds a null character somewhere in memory.

To print just part of a string, we can use the conversion specification `%.ps`, where `p` is the number of characters to be displayed.

```C
printf("%.6s\n", str); // prints: Are we
```

Strings can also be printed within fields. The `%ms` conversion specifier will display a streing in a field of size `m`. A string with more than `m` characters will be printed in full, not truncated.

If the string has fewer than `m` characters, it will be right-justified within the field, but we can force left justification with a minus sign in front of the `m`.

The `m` and `p` values can be used in combination; `%m.ps` causes the first `p` characters of a string to be displayed in a field of size `m`.

In addition to `printf`, the C standard library also provides us with `puts`: it has only one argument and always writes an additional new-line character to advance to the beginning of the next output line.


```C
char str[] = "Are we having fun yet?";
puts(str);
```

### Reading Strings Using `scanf` and `gets`

The `%s` conversion specification allows `scanf` to read a string into a character array:

```C
scanf("%s", str);
```

There's no need to put the `&` operator in front of `str` because, as we've covered, array names are treated as pointers when passed to a function.

When `scanf` is called, it skips white space then reads characters and stores them in `str` until it encounters a white-space character. `scanf` always stores a null character at the end of the string. Consequently, a string read with `scanf` will never contain white space.

To read an entire line of input at the same time, we can use `gets`, which reads input characters into an array and then stores a null character. It differs in a few respects:

- `gets` doesn't skip white space before starting to read the string (`scanf` does).
- `gets` reads until it finds a new-line character (`scanf` stops at any white-space character). Incidentally, `gets` discards the new-line character instead of storing it in the array; the null character takes its place.

```C
char sentence[SENT_LEN+1];

printf("Enter a sentence:\n");
scanf("%s", sentence);          // only stores the first word!
puts(sentence);
putchar('\n');

printf("Enter a sentence:\n");
gets(sentence);                 // stores the entire line!
puts(sentence);
```

```txt
Enter a sentence:
To C, or not to C: that is the question.
To

Enter a sentence:
To C, or not to C: that is the question.
To C, or not to C: that is the question.
```

As they read characters into an array, `scanf` and `gets` have no way to detect when it's full. Consequently, they may store characters past the end of the array, causing undefined behaviour. 

`scanf` can be made safer by using the conversion specifier `%ns` instead, where `n` is an integer indicating the maximum number of characters to be stored. `gets`, unfortunately, is inherently unsafe; `fgets` is a much better alternative.

### Reading Strings Character by Character

Since both `scanf` and `gets` are risky and insufficiently flexible for many applications, C programmers often write their own input functions. By reading strings one `char` at a time, these functions provide a greater degree of control than the standard library functions.

If we decide to design our own input function, we'll need to consider the following issues:

- **Should the function skip whitespace** before beginning to store the string?
- **What character causes the function to stop reading**: a new-line character, any white-space character, or some other character? Is this character stored in the string or discarded?
- **What should the function do if the input string is too long to store**: discard the extra characters or leave them for the next input operation?

Suppose we need a function that doesn't skip white-space, stops reading at newline characters (which aren't stored) and discards extra characters. The function might have the following prototype:

```C
int read_line(char str[], int n);
```

`str` represents the array into which we'll store the input, and `n` is the maximum number of characters to be read. If the input line contains more than `n` characters, `read_line` will discard the additional ones. We'll have `read_line` return the number of characters it stores in `str` (anywhere from 0 to `n`). We may not need the return value, but it doesn't hurt to have it available.

```C
int read_line(char str[], int n)
{
  int ch, i = 0;

  while ((ch = getchar()) != '\n')
    if (i < n) str[i++] = ch;

  str[i] = '\0';      // terminates the string
  return i;           // returns number of stored chars
}
```

Note that `ch` has `int` type rather than `char` type, because `getchar` returns the character that it reads as an `int` value.

Before returning `read_line` puts a null character at the end of the string. Standard functions such as `scanf` and `gets` automatically put a null character at the end of an input string, if we're writing our own we must take on that responsibility.

## 13.4 Accessing the Characters in a String

As strings are stored as arrays, we can use subscripting to access the individual characters in them. e.g. to process every character in `s`, we can set up a loop that increments `i` such that `s[i]` is each character.

```C
int count_spaces(const char s[])
{
  int count = 0, i;

  for (i = 0; s[i] != '\0'; i++)
    if (s[i] == ' ') count++;

  return count;
}
```

`const` has been included in the declaration of `s` to show that `count_spaces` does not and shouldn't change the array that `s` points to.

If `s` were not a string, the function would need a second argument specifying the length of the array, but because it's a string we can simply test for the null character.

Many C programmers would much prefer to write `count_spaces` using pointer arithmentic instead of array subscripting. 

```C
int count_spaces(const char *s)
{
  int count = 0;

  for (; *s != '\0'; s++)
    if (*s == ' ') count++;
  
  return count;
}
```

Note that in this example, `const` doesn't prevent `count_spaces` from modifying `s`; it's there to prevent the function from modifying what `s` points to. As `s` is a copy of the pointer that's passed to `count_spaces` incrementing it doesn't affect the original pointer.

This raises some questions about how best to write string functions:

- ***Is it better to use array operations or pointer operations to access the characters in a string?*** We're free to use whichever is more convenient; we can exen mix the two. Traditionally, C programmers prefer pointer operations for processing strings.
- ***Should a string parameter be declared as an array or as a pointer?*** The two versions of `count_spaces` illustrate the options. There are no differences between the two declarations, as the compiler treats an array parameter as though it had been declared as a pointer.
- ***Does the form of the parameter (`s[]` or `*s`) affect what can be supplied as an argument?*** No. When `count_spaces` is called, the argument could be an array name, a pointer variable or a string literal; `count_spaces` can't tell the difference.

## 13.5 Using the C String Library

Other programming languages can use operators to copy, compare, concatenate, select substrings, etc. In contrast, C's operators are essentially useless for working with string; they're treated as arrays and so are subject to the same restrictions.

In particular, they cannot be copied or compared using operators. 

***

Direct attempts to copy or compare strings will fail. Copying a string into a character array using the `=` operator is not possible.

```C
char str1[10], str2[10];

str1 = "abc"; // WRONG
str2 = str1;  // WRONG
```

However, we can still initialise character arrays using the `=` operator:

```C
char str1[10] = "abc";
```

Attempting to compare strings using a relational or equality operator is legal, but it won't produce the desired result:

```C
if (str1 == str2) ...   // WRONG!
```

This will instead compare `str1` and `str2` as pointers; it doesn't compare the contents of the two arrays. These strings will necessarily have different addresses even if they have the same letters, so will always return 0.

***

Fortunately, the C library provides a rich set of functions for performing operations on strings in the `<string.h>` header.

Most of the functions declared in `<string.h>` require at least one string as an argument, declared to have type `char *`. This allows the argument to be a character array, a variable of type `char *`, or a string literal. 

What out for string parameters that aren't declared `const` as such parameters may be modified when the function is called, meaning they can't be passed string literals.

In subsequent examples, assume that `str1` and `str2` are character arrays used as strings.

### `strcpy()` -> String Copy

```C
char *strcpy(char *s1, const char *s2);
```

`strcpy` copies the string `s2` into the string `s1`; it copies characters from `s2` to `s1` up to and including the first null character in `s2`. `strcpy` returns `s1` (a pointer to the destination string). The string pointed to by `s2` isn't modified, so it's declared `const`. 

The existence of `strcpy` compensates for the fact that we can't use the assignment operator to copy strings. Suppose that we can't to store a string in `str2`; we can't use the assignment

```C
str2 = "abcd";    // WRONG
```

because `str2` is an array name and can't appear on the left side of an assignment. Instead, we call `strcpy`:

```C
strcpy(str2, "abcd");   // str2 now contains "abcd"
```

Similarly, we can't assign `str2` to `str1` directly, but we can call `strcpy`:

```C
strcpy(str1, str2);   // str1 now contains "abcd"
```

Typically we discard the return value of `strcpy`, but it can sometimes be useful to call it as part of a larger expression in order to use its return value, such as in a chain call:

```C
strcpy(str1, strcpy(str2, "abcd"));
  // both str1 and str2 now contain "abcd"
```

***

*In the call `strcpy(str1, str2)`, `strcpy` has no way to check that the string pointed to by `str2` will actually fit in the array pointed to by `str1`.*

*Suppose that `str1` points to an array of length `n`, if `str2` has `n-1` or fewer letters, everything will be fine. However, if `str2` is longer than that, undefined behaviour occurs.*

*This is because `strcpy` always copies to the first null character and will continue copying past the end of the array that `str1` points to.*

***

A safer, albeit slower, way to copy a string is to use `strncpy`, which has a third argument that limits the number of characters that will be copied. To copy `str2` into `str1` we could use the following call of `strncpy`:

```C
strncpy(str1, str2, sizeof(str1));
```

This approach isn't without its dangers though; if a length of `str2` is greater than or equal to the size of the array, it will leave it without a terminating character.

```C
strncpy(str1, str2, sizeof(str1) -1);
str1[sizeof(str1)-1] = '\0';
```

This ensure that `str1` is always null-terminated, even if `strncpy` fails to copy a null character from `str2`. 

### `strlen()` -> String Length

```C
size_t strlen(const char *s);
```

`size_t` is a `typedef` name that represents one of C's unsigned integer types. Unless we're dealing with extremely long strings, we can simply treat the return value of `strlen` as an integer.

`strlen` returns the length of a string `s`; the number of characters in `s` up to but not including the first null character:

```C
int len;

len = strlen("abc");  // len is now 3
len = strlen("");     // len is now 0
strcpy(str1, "abc");  
len = strlen(str1);   // len is now 3
```

The last example illustrates an important point: when given an array as its argument, `strlen` doesn't measure the length of the array itself: it returns the length of the string stored in the array.

### `strcat()` -> String Concatenation

```C
char *strcat(char *s1, const char *s2);
```

`strcat` appends the contents of the string `s2` to the end of the string `s1`: it returns `s1` (a pointer to the resulting string).

```C
strcpy(str1, "abc");
strcat(str1, "def");    // str1 now contains "abcdef"
...
strcpy(str1, "abc"); 
strcpy(str2, "def");
strcat(str1, str2);     // str1 now contains "abcdef"
```

As with `strcpy`, the value returned by `strcat` is normally discarded. The following example shows how the return value might be used:

```C
strcpy(str1, "abc");
strcpy(str2, "def");
strcat(str1, strcat(str2, "ghi"));
  // str1 now contains "abcdefghi"; str2 contains "defghi"
```

***

*The effect of the call `strcat(str1, str2)` is undefined if the array pointed to by `str1` isn't long enough to accomodate the additional characters from `str2`. Consider the following example:*

```C
char str1[6] = "abc";
strcat(str1, "def");    // WRONG!
```

*`strcat` will attempt to add the characters `def` and `\0` to the end of the string already stroed in `str1`. Unfortunately, `str1` is limited to six characters, causing `strcat` to write past the end of the array.*

***

`strncat` is the safer but slower version of `strcat`. Like `strncpy` it has a third argument that limits the number of characters it will copy.

```C
strncat(str1, str2, sizeof(str1) - strlen(str1) - 1);
```

`strncat` will terminate `str1` with a null character, which isn't included in the third argument (the number of characters to be copied). In this example, we calculated the amount of remaining space in `str1` and then subtracted 1 to make sure there was enough room for the null character.

### `strcmp()` -> String Comparison

```C
strcmp(const char *s1, const char *s2);
```

`strcmp` compares the strings `s1` and `s2`, returning a value less than, equal to, or greater than 0, depending on whether `s1` is less than, equal to, or greater than `s2`.

```C
// test if str1 is less than str2
if (strcmp(str1, str2) < 0)
  ...
// test if str1 is less than or equal to str2
if (strcmp(str1, str2) <= 0)
```

`strcmp` compares strings based on their lexicographic ordering, which resembles the way words are arranged in a dictionary. More precisely, `strcmp` considers `s1` to be less than `s2` if either one of the following conditions is satisfied:

- the first `i` characters of `s1` and `s2` match, but the `i+1`st character of `s1` is less than the `i+1`st character of `s2`. e.g. `"abc"` is less than `"bcd"`; `"abd"` is less than `"abe"`
- all characters of `s1` match `s2` but `s1` is shorter than `s2`. e.g. `"abc"` is less than `"abcd"`

As it compares characters from two strings, `strcmp` looks at the numerical codes that represent the characters, which have a few important properties to remember to fully understand `strcmp`.

- The characters in each of the sequences A-Z, a-z and 0-9 have consecutive codes.
- All upper-case letters are less than all lower-case letters. (In ASCII, codes between 65 and 90 represent upper-case letters: codes between 97 and 122 represent lower-case letters.)
- Digits are less than letters. (Codes between 48 and 57 represent digits.)
- Spaces are less than all printing characters. (The space character has the value 32 in ASCII.)

### Program: Priting a One-Month Reminder List

To illustrate the use of the C string library, we'll now develop a program that prints a one-month list of daily reminders. The user will enter reminders, with each prefixed by a day of the month. When they enter 0 instead of a valid day the program will print a list of all reminders entered, sorted by day.

```txt
Enter day and reminder: 24 Susan's Birthday
Enter day and reminder: 5 6:00 - Dinner with Marge and Russ
Enter day and reminder: 26 Movie - "Chinatown"
Enter day and reminder: 7 10:30 - Dental Appointment
Enter day and reminder: 12 Movie - "Dazed and Confused"
Enter day and reminder: 5 Saturday Class
Enter day and reminder: 12 Saturday Class
Enter day and reminder: 0

Day Reminder
  5 Saturday Clas
  5 6:00 - Dinner with Marge and Russ
  7 10:30 - Dental appointment
 12 Saturday class
 12 Movie - "Dazed and Confused"
 24 Susan's Birthday
 26 Movie - "Chinatown" 
```

To read the days, we'll use `scanf`; to read the reminders we'll use the `read_line` function from section 13.3.

We'll store the strings in a two-dimensional array of characters, with each row of the array containing one string. 

After the program reads a day and its associated reminder, it will search the array to determine where the day belongs, using `strcmp` for comparisons. It will then use `strcpy` to move all strings *below* that point down one position.

Finally, the program will copy the day into the array and call `strcat` to append the reminder to the day. 

The call `sprintf(day_str, "%2d", day);` writes the value of `day` into `day_str`. 

We'll also make sure the user doesn't enter more than two digits with the following call to `scanf`:

```C
scanf("%2d", &day);
```

```C
// remind.c
// prints an ordered one-month reminder list

#include <stdio.h>
#include <string.h>

#define MAX_REMIND 50   // maximum number of reminders
#define MSG_LEN 60      // max length of reminder messages

int read_line(char str[], int n);

int main(void)
{
  char reminders[MAX_REMIND][MSG_LEN+3];
  char day_str[3], msg_str[MSG_LEN+1];
  int day, i, j, num_remind = 0;

  for (;;) {
    if (num_remind == MAX_REMIND) {
      printf("-- No space left --\n");
      break;
    }

    printf("Enter day and reminder: ");
    scanf("%2d", &day);
    if (day == 0)
      break;
    sprintf(day_str, "%2d", day);
    read_line(msg_str, MSG_LEN);

    for (i = 0; i < num_remind; i++)
      if (strcmp(day_str, reminders[i]) < 0)
        break;
    for (j = num_remind; j > i; j--)
      strcpy(reminders[j], reminders[j-1]);

    strcpy(reminders[i], day_str);
    strcat(reminders[i], msg_str);

    num_remind++;
  }

  printf("\nDay Reminder\n");
  for (i = 0; i < num_remind; i++)
    printf(" %s\n", reminders[i]);

  return 0;
}

int read_line(char str[], int n)
{
  int ch, i = 0;

  while ((ch = getchar()) != '\n')
    if (i < n) str[i++] = ch;

  str[i] = '\0';
  return i;
}
```

While *remind.c* is useful for demonstrating the `strcpy`, `strcat` and `strcmp` functions, it lacks something as a practical reminder program. There are obviously a number of improvements needed, ranging from minor tweaks to major enhancements (such as saving the reminders in a file when the program terminates!).

We'll discuss several improvements in the programming projects at the end of this chapter and in later chapters.

## 13.6 String Idioms

A lot of C idioms are dedicated to the manipulation of strings. We'll explore some of the more famous idioms by using them to write `strlen` and `strcat` functions.

The concise style used in this section is popular with many C programmers, and should be mastered even if you plan to adopt a different style as you're likely to encounter it in code written by others.

As section 21.1 explains, we're not allowed to write a function that has the same name as a standard library function, even if we don't include the header to which the function belongs. In fact, all names that begin with `str` and a lower-case letter are reserved (to allow functions to be added to the `<string.h>` header in the future).

### Searching for the End of a String

Many string operations require searching for the end of a string. `strlen` is a prime example. The following version searches its string argument to find the end, using a variable to track it.

```C
size_t strlen(const char *s)
{
  size_t n;

  for (n = 0; *s != '\0'; s++)
    n++;

  return n;
}
```

How do we condense this function? 

- move the initialisation of `n` to its declaration
- `*s != '\0'` == `*s! = 0` == `*s`
- increment `s` and test `*s` in the same expression
- replace the `for` loop with a `while`

```C
size_t strlen(const char *s)
{
  size_t n = 0;

  while (*s++) n++;

  return n;
}
```

While more condensed, this isn't actually any faster. However, we can conceive of a version that *should* run faster, with some compilers anyway.

```C
size_t strlen(const char *s)
{
  const char *p = s;

  while (*s) s++;

  return s - p;
}
```

This version of `strlen` computes the length of the string by locating the position of the null character, then subtracting it from the position of the first-character in the string. The improvement in speed comes from not having to increment `n` inside the `while` loop.

```C
// idiom 1
while (*s)
  s++;

// idiom 2
while (*s++)
  ;
```

Both of these fragments mean *"search for the null character at the end of a string"*. The first leaves the pointer pointing at a null character. The second version is more concise, but leaves `s` pointing just past the null character.

### Copying a String

Copying a string is another common operation. To introduce C's string copy idiom, we'll develop two versions. Let's start with a straightforward but somewhat lengthy version of the `strcat` function: 

```C
char *strcat(char *s1, const char *s2)
{
  char *p = s1;

  while (*p != '\0') 
    p++;

  while (*s2 != '\0') {
    *p = *s2;
    p++;
    s2++;
  }

  *p = '\0';
  return s1;
}
```

This is a two-step algorithm:

1) Locate the null character at the end of the string `s1` and make `p` point to it
2) Copy characters one by one from `s2` where `p` is pointing

The first while statement in the function performs step 1. `p` is set to point to the fitst character in the s1 string. `p` is then incremeneted as long as it doesn't point to a null character. When the loop terminates, `p` must be pointing to the null character.

The second while statement implements step 2. The loop body copies one character from where `s2` points to where `p` points, then increments both `p` and `s2`. The loop terminates when `s2` points to the null character. AFter putting a null character where `p` is pointing, `strcat` returns.

By a process similar to the one we used for `strlen`, we can also condense this function into the following:

```C
char *strcat(char *s1, const char *s2)
{
  char *p = s1;

  while (*p) 
    p++;
  while (*p++ = *s2++)
    ;
  return s1;
}
```

Pay special attention to the `while (*p++ = *s2++)` line; it copies a character from where `s2` points to where `p` points. After the assignment, both `p` and `s2` are incremented, thanks to the `++` operators. Repeatedly executing this expression has the effect of copying a series of characters from where `s2` points to where `p` points.

What causes the loop to terminate? As the primary operator inside the brackets is assignment, the `while` statement tests the value of the assignment: the character that was copied. All characters except the null character test true, so the loop won't terminate until the null character has been copied. Similarly, as the loop terminates *after* the assignment, we don't need a separate statement that puts a null character at the end of the new string.

## 13.7 Arrays of Strings

One question you'll encounter often is "What is the best way to store an array of strings?" 

The obvious answer is to create a two-dimensional array of characters, then satore the strings in the array, one per row. 

```C
char planets[][8] = { "Mercury", "Venus", "Earth",
                      "Mars", "Jupiter", "Saturn",
                      "Uranus", "Neptune", "Pluto" };
```

Note that we're allowed to omit the number of rows in the `planets` array - since that's obvious from the number of elements in the initialiser - C still requires that we specify the number of columns.

Not all of our strings were long enough to fill an entire row of the array, so C padded them will null characters.

```C
    0   1   2   3   4   5   6   7   
0   M   e   r   c   u   r   y   \0 
1   V   e   n   u   s   \0  \0  \0 
2   E   a   r   t   h   \0  \0  \0 
3   M   a   r   s   \0  \0  \0  \0 
4   J   u   p   i   t   e   r   \0 
5   S   a   t   u   r   n   \0  \0 
6   U   r   a   n   u   s   \0  \0 
7   N   e   p   t   u   n   e   \0 
8   P   l   u   t   o   \0  \0  \0 
```

The inefficiency of these examples is common when working with strings, since most string collections will contain a mixture of long and short strings. 

Instead, we need a *ragged array*: a 2d array whose rows can have different lengths. There's no native data type for this, instead we creatre an array whose elements are pointers to strings.

```C
char *planets[] = { "Mercury", "Venus", "Earth",
                    "Mars", "Jupiter", "Saturn",
                    "Uranus", "Neptune", "Pluto" };
```

This is a minor syntactical shift, but the effect on the storage efficiency is notable.

```C
planets    
0 [-]->  M e r c u r y \0 
1 [-]->  V e n u s \0 
2 [-]->  E a r t h \0   
3 [-]->  M a r s \0 
4 [-]->  J u p i t e r \0 
5 [-]->  S a t u r n \0 
6 [-]->  U r a n u s \0 
7 [-]->  N e p t u n e \0 
8 [-]->  P l u t o \0 
```

To access one of the planet names, all we need to do iss subscript the `planets` array, in the same way we would access an element in a two dimensional array.

To search the planets array for strings beginning with the letter M, we could use the following loop:

```C
for (i = 0; i < 9; i++)
  if (planets[i][0] == 'M')
    printf("%s begins with M\n", planets[i]);
```

### Command-Line Arguments

When we run a program, we'll often need to supply it with information; often things like filenames or option tags to alter the way the program runs. Consider the UNIX `ls` command:

```shell
ls             "lists every non-hidden file and directory in the current directory"
ls -l          "formats the output to be much more detailed with permissions, sizes, etc."
ls -l remind.c "will only display detailed information about the file 'remind.c'"
```

Command line information is available to all programs, not just operating system commands. To get access to these ***command-line arguments***, also known as program parameters, we must define `main` in a particular way:

```C
int main(int argc, char *argv[])
{
  ...
}
```

`argc` or **Argument Count** is the number of command-line arguments supplied to the program (including the name of the program itself)

`argv` or **Argument Vector** is an array of pointers to the command-line arguments, which are stored in string form. `argv[0]` points to the name of the program, while `argv[1]` through `argv[argc-1]` point to the remaining command-line arguments. `argv` has one additional element, `argv[argc]`, which is always a *null pointer* - a special pointer that points to nothing.

If the user enters the command `ls -l remind.c`  :

- `argc` will be 3
- `argv[0]` will point to a string containing the program name
- `argv[1]` will point to the string `"-l"`
- `argv[2]` will point to the string `"remind.c"`
- `argv[3]` will be a null pointer

```C
 argv    
0 [-]--> // program name 
1 [-]--> - l \0 
2 [-]--> r e m i n d . c \0  
3 [/]
```

Depending on your operating system, the program name can include a path or other information. If the program name isn't available, `argv[0]` points to an empty string.

As `argv` is an array of pointers, accessing command-line arguments is quite easy. Typically, a program that expects them will set up a loop that examines each argument in turn. The following loop prints the command-line arguments, one per line:

```C
int i;

for (i = 1; i < argc; i++)
  printf("%s\n", argv[i]);
```

Another technique is to set up a pointer to `argv[1]`, then increment the pointer repeatedly to step through the rest of the array. Since the last element of `argv`is always a null pointer, the loop can terminate when it finds a null pointer in the array.

```C
char **p;

for (p = &argv[1]; *p != NULL; p++)
  printf("%s\n", *p);
```

`p` is a pointer to a pointer to a character, we've got to use it carefully. Setting `p` equal to `&argv[1]` makes sense; `argv[1]` is a pointer to a character, so `&argv[1]` is a pointer to a pointer. 

The test `*p != NULL` is fine, since `*p` and `NULL` are both pointers. 

Incrementing `p` looks good, `p` points to an array element, so incrementing it will advance it to the next element.

Printing `*p` is fine, since `*p` points to the first character in a string.

### Program: Checking Planet Names

This program is designed to check a series of strings to see which ones are names of planets. When the program is run, the user will put the strings to be tested on the command line:

```text
planet Jupiter venus Earth fred
```

The program will indicate whether or not each string is a planet name: if it is, the program will also display the planet's number (with planet 1 being the one closest to the Sun):

```text
Jupiter is planet 5
venus is not a plent
Earth is planet 3
fred is not a planet
```

Notice that the program doesn't recognise a string as a planet name unless its first letter is upper-case and its remaining letters are lower-case.

```C
// planet.c
// checks planet names

#include <stdio.h>
#include <string.h>

#define NUM_PLANETS 9

int main(int argc, char *argv[])
{
  char *planets[] = { "Mercury", "Venus", "Earth",
                      "Mars", "Jupiter", "Saturn",
                      "Uranus", "Neptune", "Pluto" };

  int i, j;

  for (i = 1; i < argc; i++) {
    for (j = 0; j < NUM_PLANETS; j++)
      if (strcmp(argv[i], planets[j]) == 0) {
        printf("%s is planet %d\n", argv[i], j + 1);
        break;
      }
    if (j == NUM_PLANETS)
      printf("%s is not a planet\n", argv[i]);
  }

  return 0;
}
```

## Strings: Q&A

**Q: How long can a string literal be?**

A: The C89 standard specifies that compilers must allow string literals to be at least 509 characters long. (Don't ask...) C99 increases the minimum to 4095 characters.

**Q: Why aren't string literals called "string constants"?**

A: Because they're not necessarily constant. Since string literals are accessed through pointers, there's nothing to prevent a program from attempting to modify the characters in a string literal.

**Q: How do we write a string literal that represents "über" if "\xfcber" doesn't work?**

A: The secret is to write two adjacent string literals and let the compiler join them into one. In this example, writing "\xfc" "ber" will give us a string literal that represents the word "über".

**Q: If `printf` and `scanf` expect their first argument to have type `char *`, does that mean that the argument can be a string variable instead of a string literal?**

A: Yes, here's an example:

```C
char fmt[] = "%d\n";
int i;

printf(fmt, i);
```

This ability opens the door to some intriguing possibilities - reading a format string as input, for example.

**Q: How can `read_line` detect whether `getchar` has failed to read a character?**

A: If it can't read a character, either because of an error or because of end-of-file, `getchar` returns the value `EOF`, which has type `int`. Here's a revised version of `read_line` that tests whether the return value of `getchar` is `EOF`.

```C
int read_line(char str[], int n)
{
  int ch, i = 0;

  while ((ch = getchar()) != '\n' && ch != EOF)
    if (i < n)
      str[i++] = ch;
    str[i] = '\0';
    return i;
}
```

## Written Exercises

### 1. The following function calls supposedly write a single new-line character, but some are incorrect. Identify which calls don't work and explain why:

```C
a) printf("%c", '\n');    // correct
b) printf("%c", "\n");    // wrong: you're trying to print a string as a char

c) printf("%s", '\n');    // wrong: you're trying to print a char as a string
d) printf("%s", "\n");    // correct

e) printf('\n');          // wrong, printf requires a string literal / variable
f) printf("\n");          // correct

g) putchar('\n');         // correct
h) putchar("\n");         // wrong, putchar can't put a string literal

i) puts('\n');            // wrong, puts() only prints strings
j) puts("\n");            // wrong, prints two newlines
k) puts("");              // correct, puts() appends a newline to the output
```

### 2. Suppose that `p` has been declared as follows: `char *p = "abc";`

Which of the following function calls are legal? Show the output produced by each legal call and explain why the others are illegal.

```C
a) putchar(p);    // wrong: trying to place a pointer variable as a character

b) putchar(*p);   // legal

c) puts(p);       // legal

d) puts(*p);      // wrong
```

### 3. Suppose that we call `scanf` as follows: `scanf(%d%s%d", &i, s, &j);`

If the user enters `12abc34 56def78`, what will be the values of `i`, `s` and `j` after the call? (Assume that `i` and `j` are `int` variables and `s` is an array of characters.)

- `i`: 12
- `s`: abc34
- `j`: 56

`scanf` parses the `'1'`, then the `'2'`, then it hits an `'a'` and halts, because it cannot build an integer with a character. `12` is assigned to `i`.

`scanf` then parses `abc34` as a string variable, stopping at the `' '` character `abc34` is assigned to `s`.

`scanf` then ignores the whitespace and parses `'5'` and `'6'`, halting on `'d'`. This assigns the value of `56` to `j`.

### 4. Modify the `read_line` function in each of the following ways:

```C
int read_line(char str[], int n)
{
  int ch, i = 0;

  while ((ch = getchar()) != '\n')
    if (i < n) str[i++] = ch;

  str[i] = '\0';      // terminates the string
  return i;           // returns number of stored chars
}

// a) Have it skip white space before beginning to store input characters.
int read_line_skip_whitespace(char str[], int n)
{
  int ch, i = 0;

  while ((ch = getchar()) != '\n') 
  {
    if ((i == 0) && (ch == ' ')) 
      continue;

    if (i < n) 
      str[i++] = ch;
  }

  str[i] = '\0';
  return i;
}

// b) Have it stop reading at the first white-space character. Hint: To determine whether or 
//    not a character is white space, call the `isspace` function.
#include <stdbool.h>
int read_line_until_whitespace(char str[], int n)
{
  int ch, i = 0;

  while ((ch = getchar()) != '\n' && isspace(ch) == false)
    if (i < n) str[i++] = ch;

  str[i] = '\0';
  return i;
}

// c) Have it stop reading at the first new-line character, then store the new-line character 
//    in the string.
int read_line_until_newline_and_store(char str[], int n)
{
  int ch, i = 0;

  while ((ch = getchar()) != '\n') {
    if (i < n) 
      str[i++] = ch;
  }

  if (ch == '\n') {
    str[i++] = ch;
  }
  
  str[i] = '\0';
  return i;
}

// d) Have it leave behind characters that it doesn't have room to store.
int read_line(char str[], int n)
{
  int ch, i = 0;

  while (ch != '\n') {
    scanf("%c", &ch)
    if (i < n) 
      str[i++] = ch;
  }

  str[i] = '\0';      // terminates the string
  return i;           // returns number of stored chars
}

```

### 5. Write a function named capitalize that capitalizes all letters in its argument. The argument will be a null-terminated string containing arbitrary characters, not just letters.

a) Use array subscripting to access the charactes in the string. *Hint: Use the `toupper` function to convert each character to upper-case.*

```C
#include <ctype.h>

int capitalize(char str[])
{
  int edits = 0;

  for (int i = 0; str[i] != '\0'; i++) {
    if (isalpha(str[i])) {
      str[i] = toupper(str[i]);
      edits++;
    }
  }

  return edits;
}
```

b) Rewrite the `capitalize` function, this time using pointer arithmetic to access the characters in the string.

```C
int capitalize_ptr(char *str)
{
  int edits = 0;

  for (char *p = str; *p != '\0'; p++) {
    if (isalpha(*p)) {
      *p = toupper(*p);
      edits++;
    }
  }

  return edits;
}
```

### 6. Write a function named `censor` that modifies a string by replacing every occurence of `foo` by `xxx`. For example, the string `"food fool"` would become `"xxxd xxxl"`. Make the function as short as possible without sacrificing clarity.

```C
int censor(char str[])
{
  int edits = 0;

  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == 'f' && str[i + 1] == 'o' && str[i + 2] == 'o') {
      for (int j = 0; j < 3; j++)  {
        str[i++] = 'x';
      }
      edits++;
    }
  }

  return edits;
}
```

This actually worked first time with no edits wtf lmao

## 7. Suppose that `str` is an array of characters. Which one of the following statements is not equivalent to the other three?

```C
a) *str = 0;

b) str[0] = '\0';

c) strcpy(str, "");

d) strcat(str, "");
```

Statement d will not produce the same result if there are already characters in `str`. The resultant `str` will remain unchanged.

## 8. What will be the value of the string `str` after the following statements have been executed? 

```C
strcpy(str, "tire-bouchon");    // tire-bouchon

strcpy(&str[4], "d-or-wi");     // tired-or-wi

strcat(str, "red?");            // tired-or-wired?
```

"tired-or-wired?"

## 9. What will be the value of the string `s1` after the following statements have been executed?

```C
strcpy(s1, "computer");

strcpy(s2, "science");

if (strcmp(s1, s2) < 0)     
  strcat(s1, s2);           // computerscience

else
  strcat(s2, s1);

s1[strlen(s1)-6] = '\0';    // computers
```

"computers"

## 10. The following function supposedly creates an identical copy of a string. What's wrong with the function?

```C
char *duplicate(const char *p)
{
  char *q;

  strcpy(q, p);
  return q;
}
```

```txt
warning: 'q' is used uninitialized in this function [-Wuninitialized]
   strcpy(q, p);
   ^~~~~~~~~~~~
```

We've not defined a size for the string that `q` points to, so anything we copy will overflow, I think.

## 11. The Q&A section at the end of this chapter shows how the `strcmp` function might be written using array subscripting. Modify the function to use pointer arithmetic instead.

```C
int strcmp(char *s, char *t)
{
  int i;
 
  for (i = 0; s[i] == t[i]; i++)
    if (s[i] == '\0')
      return 0;
 
  return s[i] - t[i];
}
```

```C
int strcmp(char *s, char *t)
{
  while (*s++ == *t++)
    if (*s == '\0')
      return 0;
 
  return *s - *t;
}
```

## 12. Write the following function: `void get_extension(const char *file_name, char *extension);`

- `file_name` points to a string containing a file name.
- The function should store the extension on the file name in the string pointed to by `extension`. For example, if the file name is `"memo.txt"`, the function will store `"txt"` in the string pointed to by `extension`.
- If the file name doesn't have an extension, the functions should store an empty string (a single null character) in the string pointed to by `extension`.
- Keep the function as simple as possible by having it use the `strlen` and `strcpy` functions.

```C
// index subscripting version
#include <string.h>

void get_extension(const char *file_name, char *extension)
{
  int dot_idx = 0;

  for (int i = strlen(filename); i > 0; i--) {
    if (file_name[i] == '.') {
      dot_idx = i;
      break;
    }
  }

  if (dot_idx == 0) {
    strcpy(extension, "");
  } else {
    for (int j = dot_idx + 1, k = 0; j < strlen(file_name); j++) {
      extension[k++] = file_name[j]
    }
  } 
}
```

```C
// pointer arithmetic version
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void get_extension(const char *file_name, char *extension)
{
  char const *s = file_name;
  bool copy = false;
  int i = 0;

  while (*s++) {
    if (copy)
        extension[i++] = *s;

    if (*s == '.') {
        copy = true;
        strcpy(extension, "");
        i = 0;
    }
  }
}
```

## 13. Write the following function: `void build_index_url(const char *domain, char *index_url);`

- `domain` points to a string containing an Internet domain, such as "knking.com".
- the function should add "http://www." to the beginning of this string and "/index.html" to the end of the string, storing the result in the string pointed to by `index_url`
- You may assume that `index_irl` points to a variable this is long enough to hold the resulting string.
- Keep the function as simple as possible by having it use the `strcat` and `strcpy` functions.

```C
void build_index_url(const char *domain, char *index_url)
{
  char *entry = "http://www.",
       *index = "/index.html";

  strcpy(index_url, entry);
  strcat(index_url, domain);
  strcat(index_url, index);
}
```

## 14. What does the following program print?

```C
#include <stdio.h>

int main(void)
{
  char s[] = "Hsjodi", *p;

  for (p = s; *p; p++)
    --*p;

  puts(s);

  return 0;
}
```

That's quite clever; it prints "Grinch".

It does so because for every character, it prints the previous ASCII character i.e. 'b' becomes 'a', 'z' becomes 'y'.

## 15. Let `f` be the following function:

```C
int f(char *s, char *t)
{
  char *p1, *p2;

  for (p1 = s; *p1; p1++) {
    for (p2 = t; *p2; p2++)
      if (*p1 == *p2) break;
    if (*p2 == '\0') break;
  }
  return p1 - s;
}
```

- what is the value of `f("abcd", "babc")`?
- what is the value of `f("abcd", "bcd")`?
- In general, what value does `f` return when passed two strings `s` and `t`?

- 0
- 3
- the index of the first character in `s` that matches any character in `t`

## 16. Use the techniques of Section 13.6 to condense the `count_spaces` function of Section 13.4. In particular, replace the `for` statement by a `while` loop.

```C
int count_spaces_condensed(const char *s)
{
  int n = 0;

  while (*s++)
    if (*s == ' ') n++;

  return n;
}
```

## 17. Write the following function: `bool test_extension(const char *file_name, const char *extension);`

- `file_name` points to a string containing a file name.
- the function should return `true` if the file's extension matches the string pointed to by `extension`, ignoring the case of letters.
- for example, the call `test_extension("memo.txt", "TXT")` should return `true`.
- incorporate the 'search for the end of a string' idiom into your function.
- HINT: Use the `toupper` function to convert characters to upper-case before comparison.

```C
#include <string.h>
#include <ctype.h>

bool test_extension(const char *file_name, const char *extension)
{
  char const *f = file_name;
  char const *e = extension;

  f += (strlen(file_name) - strlen(extension));

  while(*f)
    if (toupper(*f++) != toupper(*e++)) 
      return false;
  
  return true;
}
```

## 18. Write the following function: `void remove_filename(char *url);`

- `url` points to a string containing a URL (Uniform Resource Locator) that ends with a file name (such as "http://www.knking.com/index.html")
- the function should modify the string by removing the file-name and the preceding slash (in this example, the result will be "http://www.knking.com")
- incorporate the "search for the end of a string" idiom into your function. 
- HINT: have the function replace the last slash in the string by a null character.

```C
void remove_filename(char *url)
{
  char *u = url + strlen(url);

  while (u - url > 0) {
    if (*u == '/') {
        *u = '\0';
        break;
    }
    u--;
  }
}

void remove_filename_for(char *url)
{
  for (char *u = url + strlen(url); u - url > 0; u--)
    if (*u == '/') { 
      *u = '\0'; 
      break; 
    }
}
```
