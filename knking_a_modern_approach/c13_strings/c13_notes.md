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

### Reading Strings Using `scanf` and `gets`

### Reading Strings Character by Character

## 13.4 Accessing the Characters in a String

## 13.5 Using the C String Library

### `strcpy()` -> String Copy

### `strlen()` -> String Length

### `strcat()` -> String Concatenation

### `strcmp()` -> String Comparison

### Program: Priting a One-Month Reminder List

## 13.6 String Idioms

### Searching for the End of a String

### Copying a String

## 13.7 Arrays of Strings

### Command-Line Arguments

### Program: Checking Planet Names

## Strings: Q&A

## Written Exercises

### 1.

### 2.

### 3.

### 4.

### 5.

### 6.
