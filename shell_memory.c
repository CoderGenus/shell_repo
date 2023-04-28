#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @str: the pointer to the memory area
 * @c: bytes to fill str with
 * @n: the amout of byte
 * Return: a pointer to the memory area
 */
char *_memset(char *str, char c, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		str[i] = c;
	return (str);
}

/**
 * free_str -frees a string of strings
 * @str: strings of strings
 */
void free_str(char **str)
{
	char **s = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(s);
}

/**
 * free_ptr - frees a pointer and NULLs the address
 * @p: address of the pointer to free
 * Return: 1 if freedd or 0 otherwise
 */
int free_ptr(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}

/**
 * _realloc - reallocates a block of meomry
 * @p: pointer to the previoud block
 * @old: previous block byes
 * @new: new block bytes
 * Return: pointer to old block
 */
void *_realloc(void *p, unsigned int old, unsigned int new)
{
	char *s;

	if (!p)
		return (malloc(new));
	if (!new)
		return (free(p), NULL);
	if (new == old)
		return (p);
	s = malloc(new);
	if (!s)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		s[old] = ((char *)p)[old];
	free(p);
	return (s);
}
