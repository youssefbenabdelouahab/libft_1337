#include "libft.h"
#include <stdio.h>
#include <string.h>

int    main(void)
{
    char    dst[3] = {'A', 'B', 'C'};

    printf("Return: %zu\n", ft_strlcat(dst, "Hello", 3));
    printf("Return: %zu\n", strlcat(dst, "Hello", 3));
    return (0);
}