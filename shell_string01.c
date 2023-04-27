#include "shell.h"

/**
 * *_strcat - function that concatenates two strings
 * @final: the destination buffer
 * @origin: the source buffer
 *
 * Return: the pointer to dest buffer
 */

char *_strcat(char *final, char *origin)
{
	char *c = final;

	while (*c != '\0')
		c++;

	while (origin != '\0')
		*c++ = *origin++;
	*c = '\0';
	return (final);
}

/**
 * _strcmp - compares two strings sequentially from left to right
 * @s1: first string to compare
 * @s2: second string to compare
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 *
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
	{
		return (0);
	} else if (*s1 < *s2)
	{
		return (-1);
	}
	return (1);
}
