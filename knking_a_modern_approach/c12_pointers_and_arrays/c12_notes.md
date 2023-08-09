# Chapter 12: Pointers and Arrays

> *Optimisation hinders evolution.*

When pointers point to array elements, C allows us to perform arithmetic on the pointers, which leads to an alterative way of precessing arrays in which pointers take the place of array subscripts.

One thing to be aware of is that one of the main reasons people used array arithmetic was that it was extra efficient; however now (in 2008) compilers have improved to the extent that this is somewhat less of a factor.

## 12.1 Pointer Arithmetic

Suppose that `a` and `p` have been declared: `int a[10], *p;` we can make `p` point to `a[0]` by writing `p = &a[0];` which means We can now access `a[0]` through `p`. 

e.g. we can store the value 5 in `a[0]` by writing: `*p = 5`.

Making a pointer `p` point to an element of an array isn't particular groundbreaking. By performing ***pointer arithmetic*** (address arithmetic) on `p`, we can access the other elements of `a`. C supports 3 forms of pointer arithmetic:

- Adding an integer to a pointer
- Subtracting an integer from a pointer
- Subtracting one pointer from another

The following examples assume:

```C
int a[10], *p, *q, i;
```

### Adding an Integer to a Pointer

