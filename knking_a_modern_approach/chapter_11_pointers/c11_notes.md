# Chapter 11: Pointers

> The 11th commandment was "Thou Shalt Compute" or "Thou Shalt Not Compute" - I forget which.

Pointers are one of C's most important - and most often misunderstood - features. Because of their importance, this will be the first of 3 chapters that focus specifically on pointers. This chapter covers the basics, chapters 12 and 17 will cover more advanced uses.

## 11.1 Pointer Variables

In most modern computers, main memory is divided into *bytes*, with each byte capable of storing eight bits of information:

```txt
[0][1][0][1][0][0][1][1]    (int) 83; (char) 'S';
```

Each byte has a unique *address* to distinguish it from the other bytes in memory. If the are $n$ bytes in memory, we can think of addresses as numbers that range from $0$ to $n - 1$.

An executable program consists of both code (machine instructions built from the C source) and data (variables in the original program). Each variable in the program occupies one or more bytes of memory:

| Address | Contents     |
| :-----: | :----------: |
|  `0`    | `[01010011]` |
|  `1`    | `[01110101]` |
|  `2`    | `[01110011]` |
|  `3`    | `[01100001]` |
|  `4`    | `[01101110]` |
|         |     ...      |
|  `n-1`  | `[01000011]` |

The address of the first byte is said to be the address of the variable. In the following figure, the variable `i` occupies the bytes at addresses 2000 and 2001, so `i`'s address is 2000:

```txt
        [ ... ]
2000    [  i  ] 
2001    [  i  ]
        [ ... ]
```

This is where pointers come in. Although addresses are represented by numbers, their range of values may differ from that of integers, so we can't necessarily store them in ordinary integer variables. We can however store them in special ***pointer variables***. 

When we store the address of a variable `i` in the pointer variable `p`, we say that `p` "points to" `i`. In other words, a pointer is nothing more than an address, and a pointer variable is just a variable that stores an address.

### Declaring Pointer Variables

