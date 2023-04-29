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

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!c)
		c = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], c) && (is_delim(str[x + 1], c) || !str[x + 1]))
			w_count++;
	if (w_count == 0)
		return (NULL);
	m = malloc((1 + w_count) * sizeof(char *));
	if (!m)
		return (NULL);
	for (x = 0, y = 0; y < w_count; y++)
	{
		while (is_delim(str[x], c))
			x++;
		z = 0;
		while (!is_delim(str[x + z], c) && str[x + z])
			z++;
		m[y] = malloc((z + 1) * sizeof(char));
		if (!m[y])
		{
			for (z = 0; z < y; z++)
				free(m[z]);
			free(m);
			return (NULL);
		}
		for (l = 0; l < z; l++)
			m[y][l] = str[x++];
		m[y][l] = 0;
	}
	m[y] = NULL;
	return (m);
}

/**
 * **split_string2 -splits a string into words
 * @str: the inputed string
 * @c: the delimiter
 * Return: a pointer to an array of strings or NULL on faliure
 */
char **split_string2(char *str, char c)
{
	int x, y, z, l, w_count = 0;
	char **m;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != c && str[x + 1] == c) ||
				(str[x] != c && !str[x + 1]) || str[x + 1] == c)
			w_count++;
	if (w_count == 0)
		return (NULL);
	m = malloc((1 + w_count) * sizeof(char *));
	if (!m)
		return (NULL);
	for (x = 0, y = 0; y < w_count; y++)
	{
		while (str[x] == c && str[x] != c)
			x++;
		z = 0;
		while (str[x + z] != c && str[x + z] && str[x + z] != c)
			z++;
		m[y] = malloc((z + 1) * sizeof(char));
		if (!m[y])
		{
			for (z = 0; z < y; z++)
				free(m[z]);
			free(m);
			return (NULL);
		}
		for (l = 0; l < z; l++)
			m[y][l] = str[x++];
		m[y][l] = 0;
	}
	m[y] = NULL;
	return (m);
}
