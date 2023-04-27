#include "shell.h"

/**
 * **split_string - splits a string into two words
 * @str: input string
 * @c: delimiter
 * Return: pointer  to an array of string
 */
char **split_string(char *str, char *c)
{
	int x, y, z, l, w_count = 0;
	char **m;

	if (str == NULL || str[0] == )
		return (NULL);
	if (!c)
		c = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], c) && (is_delim(str[x + 1], c) || !str[x + 1]))
			
