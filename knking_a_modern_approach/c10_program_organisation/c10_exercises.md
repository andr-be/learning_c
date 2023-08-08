# Chapter 10: Program Organisation - Exercises

## 1. The following program outline shows only function definitions and variable declarations; for each of the following scopes, list all variable and parameter names visible in that scope

```C
int a;

void f(int b)
{
    int c;
}

void g(void)
{
    int d;
    {
        int e;
    }
}

int main(void)
{
    int f;
}
```

1. the `f` function - `a`, `b`, `c`
2. the `g` function - `a`, `d`, `e`
3. the block in which `e` is declared - `a`, `d`, `e`
4. the `main` function - `a`, `f`

***

## 2. The following program outline shows only function definitions and variable definitions. For each of the following scopes, list all variable and parameter names visible in that scope

```C
int b, c;

void f(void)
{
    int b, d;
}

void g(int a)
{
    int c;
    {
        int a, d;
    }
}

int main(void)
{
    int c, d;
}
```

1. the `f` function - `b`, `c`, `d`
2. the `g` function - `a`, `b`, `c`, `d`
3. the block in which `a` and `d` are declared - `a`, `b`, `c`, `d`
4. the `main` function - `b`, `c`, `d`

***

## 3. Suppose that a program has only one function (`main`). How many different variables named `i` could this program contain?

Functionally, probably infinitely many. You could just keep nesting scope after scope to keep shadowing the initial `i`.

```C
int main(void)
{
    int i = 0;
    {
        int i = 1;
        {
            int i = 2;
            {
                int i = 3;
                {
                    ...
                }
            }
        }
    }
}
```

## Programming Exercise 7: ASCII ART NUMERALS

```txt
Enter a number: 491-9014
     _       _   _      
|_| |_|   | |_| | |   | |_|    
  |  _|   |  _| |_|   |   |    
```

```txt
 _       _   _       _   _   _   _   _                                      
| |   |  _|  _| |_| |_  |_    | |_| |_|                                     
|_|   | |_   _|   |  _| |_|   | |_|   |                                      

 _       _   _       _   _   _   _   _ 
| |   |  _|  _| |_| |_  |_    | |_| |_|
|_|   | |_   _|   |  _| |_|   | |_|   |

ENTER A NUMBER: 012

y x z, y x z, y x z

0 0 0, 0 0 1, 0 0 2     // 1st row of 0
1 0 0, 1 0 1, 1 0 2     // 1st row of 1
2 0 0, 2 0 1, 2 0 2     // 1st row of 2

0 1 0, 0 1 1, 0 1 2     // 2nd row of 0    
1 1 0, 1 1 1, 1 1 2     // 2nd row of 1
2 1 0, 2 1 1, 2 1 2     // 2nd row of 2 

0 2 0, 0 2 1, 0 2 2     // 3rd row of 0
1 2 0, 1 2 1, 1 2 2     // 3rd row of 1
2 2 0, 2 2 1, 2 2 2     // 3rd row of 2

x = row
y = num
z = segment
```