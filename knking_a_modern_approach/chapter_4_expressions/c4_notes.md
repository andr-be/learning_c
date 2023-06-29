## Chapter 4: Expressions - Notes

### A Partial List of C Operators & Their Precedence

| Precedence | Name             | Symbol(s)         | Associativity |
| :--------: | :--------------: | :---------------: | :-----------: |
| 1          | increment (post) | ++                | left          |
|            | decrement (post) | --                |               |
| 2          | increment (pre)  | ++                | right         |
|            | decrement (pre)  | --                |               |
|            | unary plus       | +                 |               |
|            | unary minus      | -                 |               |
| 3          | multiplicative   | * / %             | left          |
| 4          | additive         | + -               | left          |
| 5          | assignment       | = *= /= %= += -=  | right         |

### Bad Example of Assignment Expression

```C
// UNDEFINED BEHAVIOUR!
a = 5;
c = (b = a + 2) - (a = 1);

// MUCH SAFER
a = 5;
b = a + 2;
a = 1;
c = b - a;

// j CAN HAVE EITHER OF 2 VALUES
i = 2;
j = i * i++;
```

### Q&A Chapter 4

    Q:  I want to apply the `%` operator to a floating-point operand, but my program won't compile. What do I do?

    A:  The `%` operator requires integer operands. Try the `fmod` function instead.
