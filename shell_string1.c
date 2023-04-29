#include "shell.h"

/**
 * _strncpy - copies a string
 * @start: string source
 * @end: destination
 * @x: number of characters copied
 * Return: concatenated string
 */
char *_strncpy(char *start, char *end, int x)
{
	int m, n;
	char *str = end;

	for (m = 0; start[m] != '\0' && m < x - 1; m++)
		end[m] = start[m];
	if (m < x)
		for (n = m; n < x; n++)
			end[n] = '\0';
	return (str);
}

/**
 * _puts - prints an input string
 * @s: string
 */
void _puts(char *s)
{
	int m;

	if (!s)
		return;
	for (m = 0; s[m] != '\0'; m++)
		_putchar(s[m]);
}

/**
 * _strdup - duplicates a string
 * @s: string
 * Return: pointer to the string
 */
char *_strdup(const char *s)
{
	int var = 0;
	char *c;

	if (s == NULL)
		return (NULL);
	while (*s++)
		var++;
	c = malloc(sizeof(char) * (var + 1));
	if (!c)
		return (NULL);
	for (var++; var--;)
		c[var] = *--s;
	return (c);
}

/**
 * _putchar - write a character to stdout
 * @c: character
 * Return: 1 on success
 */
int _putchar(char c)
{
	static int x;
	static char buffer[WRITE_BUFFER];

	if (c == FLUSH_BUFFER || x >= WRITE_BUFFER)
	{
		write(1, buffer, x);
		x = 0;
	}
	if (c != FLUSH_BUFFER)
		buffer[x++] = c;
	return (1);
}

/**
 * print_dec - prints decimal
 * @num: input number
 * @f: file descriptor to write
 * Return: number of charracter print
 */
int print_dec(int num, int f)
{
	int x, ct = 0;
	unsigned int _abs_, ret;
	int (*__putchar)(char) = _putchar;

	if (f == STDERR_FILENO)
		__putchar = _eputchar;
	if (num < 0)
	{
		_abs_ = -num;
		__putchar('-');
		ct++;
	}
	else
		_abs_ = num;
	ret = _abs_;
	for (x = 100000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + ret / x);
			ct++;
		}
		ret %= x;
	}
	__putchar('0' + ret);
	ct++;

	return (ct);
}
