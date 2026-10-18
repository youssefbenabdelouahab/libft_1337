/* Libft tester: compile with ASan so heap overflows (e.g. substr SIZE_MAX) show up.
 *   cc -Wall -Wextra -Werror -g -fsanitize=address,undefined main.c ft_*.c -o test && ./test
 * (use your own ft_*.c list or libft.a; ft_split is tested only if -DTEST_SPLIT)
 */
#include "libft.h"
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <ctype.h>
#include <fcntl.h>

/* prototypes in case libft.h is missing them (compatible redeclaration is fine) */
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);

static int g_pass, g_fail;

#define CHECK(name, cond) do { \
	if (cond) g_pass++; \
	else { g_fail++; printf("  \033[31mFAIL\033[0m %s\n", name); } \
} while (0)

static int sgn(int a) { return (a > 0) - (a < 0); }
static void title(const char *s) { printf("\n== %s ==\n", s); }

/* portable reference implementations */
static size_t ref_strlcpy(char *d, const char *s, size_t n)
{
	size_t l = strlen(s), c;
	if (n) { c = l >= n ? n - 1 : l; memcpy(d, s, c); d[c] = 0; }
	return l;
}
static size_t ref_strlcat(char *d, const char *s, size_t n)
{
	size_t dl = 0, sl = strlen(s), c;
	while (dl < n && d[dl]) dl++;
	if (dl == n) return n + sl;
	c = sl >= n - dl - 1 ? n - dl - 1 : sl;
	memcpy(d + dl, s, c); d[dl + c] = 0;
	return dl + sl;
}
static char *ref_strnstr(const char *h, const char *nd, size_t n)
{
	size_t nl = strlen(nd), i;
	if (!nl) return (char *)h;
	for (i = 0; i + nl <= n && h[i]; i++)
		if (!strncmp(h + i, nd, nl)) return (char *)h + i;
	return NULL;
}

/* run substr and compare with the expected string */
static void sub(const char *s, unsigned int start, size_t len, const char *exp, const char *name)
{
	char *r = ft_substr(s, start, len);
	CHECK(name, exp == NULL ? r == NULL : (r && strcmp(r, exp) == 0));
	free(r);
}

static void test_substr(void)
{
	title("ft_substr");
	sub("hello world", 6, 5, "world", "substr normal");
	sub("hello world", 0, 5, "hello", "substr from start");
	sub("hello", 1, 100, "ello", "substr len > remaining");
	sub("hello", 0, 0, "", "substr len 0");
	sub("hello", 5, 3, "", "substr start == strlen");
	sub("hello", 10, 3, "", "substr start > strlen");
	sub("hello", UINT_MAX, 3, "", "substr start = UINT_MAX");
	sub("", 0, 5, "", "substr empty string");
	sub("", 0, 0, "", "substr empty string len 0");
	sub(NULL, 0, 5, NULL, "substr NULL -> NULL");
	sub("hello", 4, 1, "o", "substr last char");
	sub("hello", 0, 5, "hello", "substr whole string");
	sub("tripouille", 0, 42000000, "tripouille", "substr len 42M");
	sub("hello", 1, INT_MAX, "ello", "substr len INT_MAX");
	sub("hello", 1, SIZE_MAX - 1, "ello", "substr len SIZE_MAX-1 (not NULL)");
	sub("hello", 1, SIZE_MAX, "ello", "substr len SIZE_MAX (len+1 overflow)");
	sub("hello", 3, SIZE_MAX, "lo", "substr start 3, len SIZE_MAX");
	{ /* result must be an independent malloc'd copy */
		char src[] = "abcdef"; char *r = ft_substr(src, 1, 3);
		src[1] = 'X';
		CHECK("substr returns independent copy", r && strcmp(r, "bcd") == 0);
		free(r);
	}
}

static void test_ctype(void)
{
	int c, ok = 1;
	title("is*/to*");
	for (c = 0; c < 256; c++)
	{
		if (!!ft_isalpha(c) != !!isalpha(c) && c < 128) ok = 0;
		if (!!ft_isdigit(c) != !!isdigit(c)) ok = 0;
		if (!!ft_isalnum(c) != !!isalnum(c) && c < 128) ok = 0;
		if (!!ft_isprint(c) != !!isprint(c) && c < 128) ok = 0;
		if (ft_toupper(c) != toupper(c) && c < 128) ok = 0;
		if (ft_tolower(c) != tolower(c) && c < 128) ok = 0;
		if (!!ft_isascii(c) != (c < 128)) ok = 0;
	}
	CHECK("is*/to* for 0..255", ok);
	CHECK("isalpha(-1)/isdigit(300) == 0", !ft_isalpha(-1) && !ft_isdigit(300) && !ft_isascii(128) && !ft_isascii(-1));
	CHECK("toupper/tolower passthrough", ft_toupper('1') == '1' && ft_tolower('!') == '!' && ft_toupper(200) == 200);
}

static void test_atoi(void)
{
	const char *a[] = {"0", "42", "-42", "+42", "  \t\n\v\f\r 7x", "2147483647", "-2147483648",
		"2147483648", "-2147483649", "4294967296", "9223372036854775807", "9223372036854775808",
		"-9223372036854775808", "-9223372036854775809", "99999999999999999999", "+-1", "-+1",
		"--1", "  -0", "0042", "abc", "", " ", "- 1", "1 2", NULL};
	int i, ok = 1;
	title("ft_atoi");
	for (i = 0; a[i]; i++)
		if (ft_atoi(a[i]) != atoi(a[i]))
		{ ok = 0; printf("  atoi('%s'): got %d expected %d\n", a[i], ft_atoi(a[i]), atoi(a[i])); }
	CHECK("atoi vs libc (incl. overflow)", ok);
}

static void test_mem(void)
{
	title("mem*");
	{ char a[20], b[20]; memset(a, 'A', 20); memset(b, 'A', 20);
	  ft_bzero(a, 5); bzero(b, 5); CHECK("bzero", !memcmp(a, b, 20));
	  ft_bzero(a, 0); CHECK("bzero n=0", !memcmp(a, b, 20)); }
	{ char a[20], b[20]; memset(a, 'A', 20); memset(b, 'A', 20);
	  CHECK("memset ret", ft_memset(a, 'x' + 256, 7) == a);
	  memset(b, 'x' + 256, 7); CHECK("memset c>255", !memcmp(a, b, 20)); }
	{ char a[20] = "abcdef", b[20] = "XXXXXXXXXXXX";
	  CHECK("memcpy ret", ft_memcpy(b, a, 7) == b); CHECK("memcpy", !memcmp(a, b, 7));
	  CHECK("memcpy n=0", ft_memcpy(b, "zzz", 0) == b && b[0] == 'a'); }
	{ char a[16] = "0123456789", b[16] = "0123456789";
	  ft_memmove(a + 2, a, 8); memmove(b + 2, b, 8); CHECK("memmove overlap fwd", !memcmp(a, b, 16));
	  ft_memmove(a, a + 2, 8); memmove(b, b + 2, 8); CHECK("memmove overlap back", !memcmp(a, b, 16));
	  ft_memmove(a, a, 5); CHECK("memmove same ptr", !memcmp(a, b, 16));
	  CHECK("memmove n=0", ft_memmove(a, b, 0) == a); }
	{ const char *s = "tripouille"; const char u[] = {'a', (char)200, 'b', 0};
	  CHECK("memchr found", ft_memchr(s, 'p', 10) == memchr(s, 'p', 10));
	  CHECK("memchr not in range", ft_memchr(s, 'p', 3) == NULL);
	  CHECK("memchr n=0", ft_memchr(s, 't', 0) == NULL);
	  CHECK("memchr '\\0'", ft_memchr(s, 0, 11) == memchr(s, 0, 11));
	  CHECK("memchr c+256", ft_memchr(s, 'p' + 256, 10) == memchr(s, 'p' + 256, 10));
	  CHECK("memchr byte 200", ft_memchr(u, 200, 4) == memchr(u, 200, 4)); }
	CHECK("memcmp equal", ft_memcmp("abc", "abc", 3) == 0);
	CHECK("memcmp diff sign", sgn(ft_memcmp("abc", "abd", 3)) == sgn(memcmp("abc", "abd", 3)));
	CHECK("memcmp n=0", ft_memcmp("a", "b", 0) == 0);
	CHECK("memcmp unsigned", sgn(ft_memcmp("\200", "\0", 1)) == sgn(memcmp("\200", "\0", 1)));
	CHECK("memcmp stops at n", ft_memcmp("abcX", "abcY", 3) == 0);
}

static void test_str(void)
{
	title("str*");
	CHECK("strlen", ft_strlen("hello") == 5 && ft_strlen("") == 0);
	{ int bad = 0; size_t n;
	  for (n = 0; n < 14; n++)
	  { char d[32], e[32]; memset(d, 'Z', 32); memset(e, 'Z', 32);
		if (ft_strlcpy(d, "hello world", n) != ref_strlcpy(e, "hello world", n) || memcmp(d, e, 32)) { bad = 1; printf("  strlcpy n=%zu\n", n); } }
	  CHECK("strlcpy all sizes", !bad); }
	{ int bad = 0; size_t n;
	  for (n = 0; n < 20; n++)
	  { char d[32] = "abc", e[32] = "abc"; size_t r1, r2;
		memset(d + 4, 'Z', 28); memset(e + 4, 'Z', 28);
		r1 = ft_strlcat(d, "defgh", n); r2 = ref_strlcat(e, "defgh", n);
		if (r1 != r2 || memcmp(d, e, 32))
		{ bad = 1; printf("  strlcat n=%zu: ret %zu/%zu dst '%.9s' vs '%.9s'\n", n, r1, r2, d, e); } }
	  CHECK("strlcat all sizes (null-term, return)", !bad); }
	{ const char *s = "tripouille"; const char u[] = {'a', (char)200, 'b', 0};
	  CHECK("strchr found", ft_strchr(s, 'p') == strchr(s, 'p'));
	  CHECK("strchr first of many", ft_strchr(s, 'i') == strchr(s, 'i'));
	  CHECK("strchr '\\0'", ft_strchr(s, 0) == strchr(s, 0));
	  CHECK("strchr absent", ft_strchr(s, 'z') == NULL);
	  CHECK("strchr c+256", ft_strchr(s, 't' + 256) == strchr(s, 't' + 256));
	  CHECK("strchr byte 200", ft_strchr(u, 200) == strchr(u, 200));
	  CHECK("strrchr last of many", ft_strrchr(s, 'i') == strrchr(s, 'i'));
	  CHECK("strrchr '\\0'", ft_strrchr(s, 0) == strrchr(s, 0));
	  CHECK("strrchr absent", ft_strrchr(s, 'z') == NULL);
	  CHECK("strrchr c+256", ft_strrchr(s, 'i' + 256) == strrchr(s, 'i' + 256));
	  CHECK("strrchr byte 200", ft_strrchr(u, 200) == strrchr(u, 200)); }
	CHECK("strncmp equal", ft_strncmp("abc", "abc", 5) == 0);
	CHECK("strncmp diff", sgn(ft_strncmp("abc", "abd", 3)) == sgn(strncmp("abc", "abd", 3)));
	CHECK("strncmp n limits", ft_strncmp("abc", "abd", 2) == 0);
	CHECK("strncmp n=0", ft_strncmp("abc", "xyz", 0) == 0);
	CHECK("strncmp empty", ft_strncmp("", "", 3) == 0 && sgn(ft_strncmp("", "a", 1)) < 0);
	CHECK("strncmp unsigned", sgn(ft_strncmp("test\200", "test\0", 6)) == sgn(strncmp("test\200", "test\0", 6)));
	CHECK("strncmp prefix", sgn(ft_strncmp("abc", "abcd", 10)) == sgn(strncmp("abc", "abcd", 10)));
	{ const char *h = "lorem ipsum dolor sit amet";
	  CHECK("strnstr empty needle", ft_strnstr(h, "", 5) == h);
	  CHECK("strnstr found", ft_strnstr(h, "ipsum", 15) == ref_strnstr(h, "ipsum", 15));
	  CHECK("strnstr len too short", ft_strnstr(h, "ipsum", 10) == NULL);
	  CHECK("strnstr end of hay", ft_strnstr(h, "amet", 26) == ref_strnstr(h, "amet", 26));
	  CHECK("strnstr absent", ft_strnstr(h, "xyz", 26) == NULL);
	  CHECK("strnstr needle > len", ft_strnstr("abc", "abcd", 3) == NULL);
	  CHECK("strnstr empty hay", ft_strnstr("", "a", 5) == NULL);
	  CHECK("strnstr len 0", ft_strnstr("abc", "a", 0) == NULL);
	  CHECK("strnstr exact len", ft_strnstr("abc", "abc", 3) != NULL);
	  CHECK("strnstr partial then match", ft_strnstr("aaabc", "aabc", 5) == ref_strnstr("aaabc", "aabc", 5)); }
	{ char *p = ft_strdup("hello"); CHECK("strdup", p && !strcmp(p, "hello")); free(p);
	  p = ft_strdup(""); CHECK("strdup empty", p && !*p); free(p);
	  { char src[] = "abc"; p = ft_strdup(src); src[0] = 'X'; CHECK("strdup independent", p && p[0] == 'a'); free(p); } }
}

static void test_calloc(void)
{
	title("ft_calloc");
	{ int *p = ft_calloc(1000, sizeof(int)), i, ok = p != NULL;
	  for (i = 0; ok && i < 1000; i++) if (p[i]) ok = 0;
	  CHECK("calloc zeroed", ok); free(p); }
	{ void *p = ft_calloc(0, 0); CHECK("calloc(0,0) non-NULL", p != NULL); free(p);
	  p = ft_calloc(0, 5); CHECK("calloc(0,5) non-NULL", p != NULL); free(p);
	  p = ft_calloc(5, 0); CHECK("calloc(5,0) non-NULL", p != NULL); free(p); }
	{ void *p = ft_calloc(SIZE_MAX, SIZE_MAX); CHECK("calloc(MAX,MAX) NULL", p == NULL); free(p);
	  p = ft_calloc(SIZE_MAX / 2 + 2, 2); CHECK("calloc(MAX/2+2,2) NULL", p == NULL); free(p);
	  p = ft_calloc((size_t)1 << 32, (size_t)1 << 32); CHECK("calloc(2^32,2^32) NULL", p == NULL); free(p); }
}

static void test_join_trim_itoa(void)
{
	char *s; int v[] = {0, 1, -1, 9, 10, -10, 42, -42, 100, 12345, INT_MAX, INT_MIN, INT_MAX - 1, INT_MIN + 1};
	size_t i; int ok = 1;
	title("strjoin / strtrim / itoa");
	s = ft_strjoin("foo", "bar"); CHECK("strjoin", s && !strcmp(s, "foobar")); free(s);
	s = ft_strjoin("", "bar"); CHECK("strjoin empty s1", s && !strcmp(s, "bar")); free(s);
	s = ft_strjoin("foo", ""); CHECK("strjoin empty s2", s && !strcmp(s, "foo")); free(s);
	s = ft_strjoin("", ""); CHECK("strjoin both empty", s && !*s); free(s);
	s = ft_strtrim("  \t hi there \t ", " \t"); CHECK("strtrim", s && !strcmp(s, "hi there")); free(s);
	s = ft_strtrim("xxxx", "x"); CHECK("strtrim all trimmed", s && !*s); free(s);
	s = ft_strtrim("abc", ""); CHECK("strtrim empty set", s && !strcmp(s, "abc")); free(s);
	s = ft_strtrim("", "abc"); CHECK("strtrim empty string", s && !*s); free(s);
	s = ft_strtrim("abcba", "ab"); CHECK("strtrim both ends", s && !strcmp(s, "c")); free(s);
	s = ft_strtrim("xaxbx", "x"); CHECK("strtrim keeps inner", s && !strcmp(s, "axb")); free(s);
	for (i = 0; i < sizeof(v) / sizeof(*v); i++)
	{ char b[32]; sprintf(b, "%d", v[i]); s = ft_itoa(v[i]);
	  if (!s || strcmp(s, b)) { ok = 0; printf("  itoa(%d) -> '%s' expected '%s'\n", v[i], s ? s : "(null)", b); }
	  free(s); }
	CHECK("itoa values (0, negatives, INT_MIN/MAX)", ok);
}

static void test_fd(void)
{
	char buf[64]; int fd; ssize_t n;
	title("put*_fd (written to a temp file)");
	fd = open("/tmp/libft_fd_test.txt", O_CREAT | O_TRUNC | O_RDWR, 0600);
	CHECK("open temp file", fd >= 0);
	if (fd < 0) return;
	ft_putchar_fd('A', fd); ft_putstr_fd("bc", fd); ft_putendl_fd("de", fd);
	ft_putnbr_fd(0, fd); ft_putchar_fd(' ', fd); ft_putnbr_fd(-42, fd); ft_putchar_fd(' ', fd);
	ft_putnbr_fd(INT_MIN, fd); ft_putchar_fd(' ', fd); ft_putnbr_fd(INT_MAX, fd);
	lseek(fd, 0, SEEK_SET); n = read(fd, buf, 63); buf[n > 0 ? n : 0] = 0; close(fd);
	CHECK("put* output", !strcmp(buf, "Abcde\n0 -42 -2147483648 2147483647"));
	if (strcmp(buf, "Abcde\n0 -42 -2147483648 2147483647")) printf("  got: '%s'\n", buf);
}

// #ifdef TEST_SPLIT
// static void test_split(void)
// {
// 	char **r; int i;
// 	title("ft_split");
// 	r = ft_split("a b  c", ' ');
// 	CHECK("split basic", r && !strcmp(r[0], "a") && !strcmp(r[1], "b") && !strcmp(r[2], "c") && r[3] == NULL);
// 	for (i = 0; r && r[i]; i++) free(r[i]);
// 	free(r);
// 	r = ft_split("", ' '); CHECK("split empty -> {NULL}", r && r[0] == NULL); free(r);
// 	r = ft_split("   ", ' '); CHECK("split only seps -> {NULL}", r && r[0] == NULL); free(r);
// 	r = ft_split("abc", 'x'); CHECK("split no sep", r && !strcmp(r[0], "abc") && r[1] == NULL);
// 	if (r) { free(r[0]); free(r); }
// 	r = ft_split("xxabcxx", 'x'); CHECK("split edge seps", r && !strcmp(r[0], "abc") && r[1] == NULL);
// 	if (r) { free(r[0]); free(r); }
// 	r = ft_split("a,b", '\0'); CHECK("split sep '\\0'", r && !strcmp(r[0], "a,b") && r[1] == NULL);
// 	if (r) { free(r[0]); free(r); }
// 	CHECK("split NULL string -> NULL", ft_split(NULL, ' ') == NULL);
// }
// #endif

int main(void)
{
	test_substr();
	test_ctype();
	test_atoi();
	test_mem();
	test_str();
	test_calloc();
	test_join_trim_itoa();
	test_fd();
#ifdef TEST_SPLIT
	test_split();
#endif
	printf("\n==== %d passed, %d failed ====\n", g_pass, g_fail);
	return g_fail != 0;
}