*This project has been created as part of the 42 curriculum by yben-abd.*

# Libft

## Description

**Libft** is the first project of the 42 curriculum. The goal is to build your own C library, `libft.a`, containing general-purpose functions that you will reuse in your future C projects.

The project helps you understand how standard C library functions work internally by re-implementing them from scratch, and teaches you to manage memory, strings, and linked lists properly while respecting the 42 Norm.

The library is organised in three parts:

1. **Libc functions**: re-implementations of standard functions, prefixed with `ft_` (e.g. `strlen` becomes `ft_strlen`).
2. **Additional functions**: utility functions that are not in the libc or exist in a different form.
3. **Linked list functions**: a small API to manipulate singly linked lists built on the `t_list` structure.

### Library details

#### Part 1 - Libc functions

| Category | Functions |
|----------|-----------|
| Character checks | `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint` |
| Character conversion | `ft_toupper`, `ft_tolower` |
| String functions | `ft_strlen`, `ft_strlcpy`, `ft_strlcat`, `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_strnstr`, `ft_strdup` |
| Memory functions | `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`, `ft_calloc` |
| Conversion | `ft_atoi` |

The character classification functions return `1` if the character matches the class and `0` otherwise. `ft_calloc` returns a unique pointer that can be passed to `free()` when `nmemb` or `size` is `0`.

#### Part 2 - Additional functions

| Function | Description |
|----------|-------------|
| `ft_substr` | Returns a newly allocated substring of `s`, starting at `start`, with a maximum length `len`. |
| `ft_strjoin` | Returns a new string resulting from the concatenation of `s1` and `s2`. |
| `ft_strtrim` | Returns a copy of `s1` with characters from `set` removed from the beginning and the end. |
| `ft_split` | Splits `s` using `c` as a delimiter and returns a NULL-terminated array of newly allocated strings. |
| `ft_itoa` | Converts an integer (including negative numbers) to a newly allocated string. |
| `ft_strmapi` | Applies `f(index, char)` to each character of `s` and returns a new string with the results. |
| `ft_striteri` | Applies `f(index, &char)` to each character of `s`, allowing in-place modification. |
| `ft_putchar_fd` | Writes a character to the given file descriptor. |
| `ft_putstr_fd` | Writes a string to the given file descriptor. |
| `ft_putendl_fd` | Writes a string followed by a newline to the given file descriptor. |
| `ft_putnbr_fd` | Writes an integer to the given file descriptor. |

#### Part 3 - Linked list

The following structure is declared in `libft.h`:

```c
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
```

| Function | Description |
|----------|-------------|
| `ft_lstnew` | Creates a new node with the given content and `next` set to `NULL`. |
| `ft_lstadd_front` | Adds a node at the beginning of the list. |
| `ft_lstsize` | Counts the number of nodes in the list. |
| `ft_lstlast` | Returns the last node of the list. |
| `ft_lstadd_back` | Adds a node at the end of the list. |
| `ft_lstdelone` | Frees a single node's content (using `del`) and the node itself. |
| `ft_lstclear` | Deletes and frees a node and all its successors, then sets the list pointer to `NULL`. |
| `ft_lstiter` | Applies a function to the content of each node. |
| `ft_lstmap` | Creates a new list by applying a function to each node's content, using `del` to clean up on failure. |

### Technical constraints

- Written in C, following the 42 Norm.
- Compiled with `cc -Wall -Wextra -Werror`.
- No global variables.
- Helper functions are declared `static`.
- The library is built with `ar` (`libtool` is forbidden).
- No memory leaks and no unexpected crashes (segfault, double free, etc.).

## Instructions

### Compilation

At the root of the repository, run:

```sh
make
```

This produces `libft.a` at the root of the repository.

### Makefile rules

| Rule | Action |
|------|--------|
| `make` / `make all` | Builds `libft.a`. |
| `make clean` | Removes the object files. |
| `make fclean` | Removes the object files and `libft.a`. |
| `make re` | Rebuilds everything from scratch. |

The Makefile does not relink unnecessarily.

### Usage

Include the header in your source files and link against the library:

```c
#include "libft.h"

int	main(void)
{
	ft_putendl_fd("Hello, libft!", 1);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c -L. -lft -o my_program
```

### Testing against the system functions

On glibc systems, `strlcpy`, `strlcat` and `bzero` may not be available by default. To compare your implementations with the system versions in your own tests, include `<bsd/string.h>` and compile with `-lbsd`.

## Resources

### References

- `man 3` pages for each re-implemented function (`man 3 strlen`, `man 3 memmove`, ...)
- [The C Programming Language](https://en.wikipedia.org/wiki/The_C_Programming_Language) by Kernighan & Ritchie
- [GNU C Library documentation](https://www.gnu.org/software/libc/manual/)
- [42 Norm](https://github.com/42School/norminette)
- `man ar` for building static libraries
- Peer discussions and peer evaluations

### Use of AI

AI was used to help draft this `README.md` (structure and formatting of the documentation). It was not used to write the library functions themselves: all the C code was written and understood by the author(s).