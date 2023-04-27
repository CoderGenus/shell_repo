#include "shell.h"

/**
 * is_delim - checks character if a delimeter
 * @d: char to be checked
 * @meteD: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char d, char *meteD)
{
	while (*meteD)
	{
		if (*meteD++ == c)
		{
			return (1);
		}
		return (0);
	}
}

/**
 * _isalpha - checks if character is alphabetic
 * @s: The character to input
 *
 * Return: 1 if s is alphabetic, 0 otherwise
 */

int _isalpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * *_strncpy - function copies a string
 * @dest: the destination string to be copied to
 * @origin: the source string
 * @a: the maximum number of characters to be copied
 *
 * Return: the concatenated string
 */

char *_strncpy(char *dest, char *origin, int a)
{
	int i;

	for (i = 0; i < a && origin[i] != '\0'; i++)
	{
		dest[i] = origin[i];
	}

	for (; i < a; i++)
	{
		dest[i] = '\0';
	}
	return (dest);
}

/**
 * *_strncat - function that concatenates two strings
 * @dest: pointer to the destination string
 * @origin: pointer to the source string
 * @n: maximum number of characters to append
 *
 * Return: the destination string
 */

char *_strncat(char *dest, char *origin, int n)
{
	char *p = desti;

	while (*p != '\0')
	{
		p++;
	}

	int i = 0;

	while (*origin != '\0' && i < n)
	{
		*(p++) = *(origin++);
		i++;
	}

	*p = '\0';
	return (dest);
}

/**
 * *_strchr - function that locates the character in a string
 * @str: the string to be parsed
 * @a: the character to look for
 *
 * Return: pointer to string
 */

char *_strchr(char *str, char a)
{
	while (*str != '\0')
	{
		if (*str == a)
		{
			return (str);
		}
		str++;
	}
	if (a == '\0')
	{
		return (str);
	}
	return (NULL);
}
