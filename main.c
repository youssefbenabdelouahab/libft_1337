
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char **result;
    int total = 0;
    int passed = 0;
    int failed = 0;
    int i;
    int ok;

    const char *inputs[] = {
        "hello world",
        "hello",
        "",
        "     ",
        "   hello   ",
        "a,,b,,,c",
        ",hello,",
        "one two three",
        "42 school 1337",
        "hello\tworld\ttest",
        "abc",
        "a:b:c",
        "one  two",
        "aaaaa",
        "x",
        ",,hello,,,world,,",
        "a b c",
        "  one two  "
    };

    const char delimiters[] = {
        ' ', ' ', ' ', ' ', ' ', ',', ',', ' ', ' ',
        '\t', '\0', 'x', ' ', 'a', 'x', ',', ' ', ' '
    };

    const char *expected[][4] = {
        {"hello", "world", NULL},
        {"hello", NULL},
        {NULL},
        {NULL},
        {"hello", NULL},
        {"a", "b", "c", NULL},
        {"hello", NULL},
        {"one", "two", "three", NULL},
        {"42", "school", "1337", NULL},
        {"hello", "world", "test", NULL},
        {"abc", NULL},
        {"a:b:c", NULL},
        {"one", "two", NULL},
        {NULL},
        {NULL},
        {"hello", "world", NULL},
        {"a", "b", "c", NULL},
        {"one", "two", NULL}
    };

    int count = sizeof(inputs) / sizeof(inputs[0]);

    printf("========== FT_SPLIT TESTS ==========\n");

    for (int t = 0; t < count; t++)
    {
        total++;
        printf("\nTest %d: \"%s\", delimiter '%c'\n",
            t + 1, inputs[t], delimiters[t]);

        result = ft_split(inputs[t], delimiters[t]);
        ok = (result != NULL);

        if (ok)
        {
            i = 0;
            while (expected[t][i] && result[i])
            {
                if (strcmp(expected[t][i], result[i]) != 0)
                    ok = 0;
                i++;
            }
            if (expected[t][i] != NULL || result[i] != NULL)
                ok = 0;
        }

        if (ok)
        {
            passed++;
            printf("[PASS]\n");
        }
        else
        {
            failed++;
            printf("[FAIL]\n");
            printf("Expected: ");
            i = 0;
            while (expected[t][i])
                printf("\"%s\" ", expected[t][i++]);
            printf("\nGot: ");

            if (result == NULL)
                printf("NULL");
            else
            {
                i = 0;
                while (result[i])
                    printf("\"%s\" ", result[i++]);
            }
            printf("\n");
        }

        if (result != NULL)
        {
            i = 0;
            while (result[i])
                free(result[i++]);
            free(result);
        }
    }

    printf("\n========== SUMMARY ==========\n");
    printf("Total tests : %d\n", total);
    printf("Passed      : %d\n", passed);
    printf("Failed      : %d\n", failed);
    printf("================================\n");

    return (failed != 0);
}
