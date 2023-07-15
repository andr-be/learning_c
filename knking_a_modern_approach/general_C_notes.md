# General C Programming Notes

## Modern C and What We Can Learn From It - Luca Sas [ ACCU 2021 ]

*Sunday, 18th June 2023 - 08:30 -* [Link to talk](https://youtu.be/QpAhX-gsHMs)

### Type-Checked Compile Time Generics

```C
float minf(float, float);
float mini(int, int);

// FUNCTION OVERLOADING!
#define min(a, b) _Generic((a), float: minf(a, b), int: mini(a, b))
```

### Defer Macro

```C
// Initial Definition
#define macro_var(name) concat(name, __LINE__)
#define defer(start, end) for (      \
    int macro_var(_i_) = (start, 0); \
    !macro_var(_i_);                 \
    (macro_var(_i_) += 1), end)      \

defer(begin(), end())
{
    ...
}

// Applications
#define profile defer(profile_begin(), profile_end())
profile
{
    ...
}

#define gui defer(gui_begin(), gui_end())
gui
{
    ...
}

file_handle_t file = file_open(filename, file_mode_read);
scope(file_close(file))
{
    ...
}
```

### API Design in Modern C: Math

```C
// Old C Style
struct vec2 { float x, y; };

void vec2_add(const struct vec2* a, const struct vec2* b, struct vec2* out)
{
    out->x = a->x + b->x;
    out->y = a->y + b->y;
}

// Modern C
typedef struct vec2 { float x, y; } vec2;

vec2 vec2_add(vec2 a, vec2 b)
{
    vec2 result = { a.x + b.x, a.y + b.y };
    return result;
}

vec2 v = vec2_add(a, (vec2){...})
```

### Hand Made Math:  API Example

```C
typedef union hmm_vec2
{
    struct { float X, Y; };
    struct { float U, V; };
    struct { float Left, Right: };
    struct { float Width, Height; };
    float Elements[2];
} hmm_vec2;
```

This code actually allows you to use any of the given struct names for the contents inside; i.e.

```C
hmm_vec2 classic =  { .X = 1.50, .Y = 2.50 };
hmm_vec2 novel =    { .Width = 0.14414, .Height = 1.1241 };
```

### API Design in Modern C: Error Handling

```C
typedef struct file_contents_t
{
    char* data;
    isize_t size;
    valid_t valid;
} file_contents_t;

file_contents_t read_file_contents(const char*);
```

```C
file_contents_t fc = read_file_contents("milo.cat");
if (fc.valid)
{
    ...
}
```

```C
file_contents_t fc = read_file_contents("milo.cat");
image_t img = load_image_from_file_contents(fc);
texture_t texture = load_texture_from_image(img);

if (texture.valid)
{
    ...
}
```

```C
image_t get_cute_cat(image_t img)
{
    img = crop_to_cat(img);
    img = add_bow_tie(img);
    img = make_eyes_sparkle(img);
    img = make_smaller(img);
    img = add_rainbow(img);
    return img;
}

image_t img = get_cute_cat(some_cat_image);
if (img.valid)
{
    ...
}
```

### API Design in Modern C: Error Codes

```C
typedef struct file_contents_t
{
    char* data;
    isize_t size;
    error_code_t error_code;
} file_contents_t;
```

### Generic APIs in C: Dynamic Arrays

- C lacks generic programming (eg: templates)
- C can also force us to think outside of the box and not rely excessively on templates

```C++
// C++ Dynamic Array
std::vector<int> v;
v.push_back(1);
```

```C
// Modern C Dynamic Array
#define dynarray(T) T*

typedef struct dynarray_info
{
    isize_t size;
    isize_t capacity;
    isize_t element_size;
} dynarray_info;

#define dynarray_add(arr, ...) dynarray_ensure_capacity(arr); (*arr)[dynarray_size(*arr)] = __VA_ARGS__

dynarray(int) arr = dynarray_init(int, 10);
dynarray_add(&arr, 99);
```

This, by the admission of the author, is 'a bit hacky`.

### Generic APIs in C: Map

<https://github.com/nothings/std/blob/master/stb_ds.h>

```C
typedef struct kv
{
    const char* key;
    value_t value;
} kv;

#define hash_map(KV) KV*
```

### Libraries in C

- historically messy due to no standard and loads of build systems
- single header library arises as a convenient way to solve this problem

```C
#define LIB_IMPLEMENTATION
#include "lib.h"
```

- Sane CMake is another good opion. Single headers can optionally be auto-generated.

### Old C String Handling & C Standard Library

- historical disaster
- terrible standard API (`strstr`, `strtok`, `strpbrk`)
- avoid `libc` - The Standard C Library
  - very slow
  - very old
  - terrible API design
  - very few parts are actually useful (`stdint.h`, `memmove`/`memcpy`/`memset`, `math.h`)
- `NULL` terminated strings are the devil

### Replacing `libc` functionality: `printf`

```C
typedef struct cat {...} cat;
void print_cat(cat*);

logger_register_printer("cat", print_cat);

cat c = ...;
log("Cat: {cat}", c);
```

### String Handling in Modern C

```C
typedef struct str
{
    char*   data;
    isize_t size;
} str;

typedef struct str_buf
{
    char* data;
    isize_t size;
    isize_t capacity;
    allocator_cb allocator;
} str_buf;
```

```C
str_buf str_buf_make(isize_t size, allocator_cb allocator);
void str_buf_append(str_buf*, str);
void str_buf_insert(str_buf*, str, isize_t);
void str_buf_remove(str_buf*, isize_t, isize_t);
str str_buf_str(str_buf);
...
bool str_valid(str);
bool str_match(str a, str b);
bool str_contains(str haystack, str needle);
str str_sub(str src, isize_t begin, isize_t end);
str str_find_first(str haystack, str needle);
str str_find_last(str haystack, str needle);
str str_remove_prefix(str src, str prefix);
str str_remove_suffix(str src, str prefix);
```

```C
str str_pop_first_split(str* src, str split_by);
// ...
str date = cstr("2021/03/12");
str year = str_pop_first_split(&date, cstr("/"));
str month = str_pop_first_split(&date, cstr("/"));
str day = str_pop_first_split(&date, cstr("/"));
```

### String handling in Old C

```C
// has to be an array...
char date[] = "1981/04/01";
char* year, month, day;

// BECAUSE strtok() INSERTS NULL CHARACTERS!
year = strtok(date, "/");
month = strtok(NULL, "/");
year = strtok(NULL, "/");
```

### String handling in Modern C: overloading

```C
str str_pop_first_split_impl(str* src, str split_by);

#define str_pop_first_split(str, split_by)                      \
    _Generic(split_by,                                          \
    const char*: str_pop_first_split_impl(str, cstr(split_by)), \
    default: str_pop_first_split_impl(str, split_by))

//...

str date = cstr("2021/03/12");
str year = str_pop_first_split(&date, "/");
str month = str_pop_first_split(&date, "/");
str day = str_pop_first_split(&date, "/");
```

```C
#define for_str_split(iter, src, split_by)
    for (
        str macro_var(src_) = src,                               \
        iter = str_pop_first_split(&macro_var(src_), split_by),  \
        macro_var(split_by_) = split_by;                         \
                                                                 \
        str_valid(macro_var(src_));                              \
                                                                 \
        iter = str_pop_first_split()                             \
    )

// ...

str date = cstr("2021/03/12");
for_str_split(it, date, "/")
{
    print("{str}", it);
}
```

***

## General Update on Note-taking

`14/07/2023`

Annoyingly, I keep breaking the history of the md notes I'm creating. 
Because of this, I've decided to avoid doing much in the way of notes for the next few chapters and see if it affects my understanding. I'll still read everything in the book and note the programs, but I won't be basically retyping the notes. The exercises will all still be done in full.

It's too much of a faff and it's drastically slowing down how fast I end up going through the book because I have to work my way up to doing something very, very boring every now and again.

***