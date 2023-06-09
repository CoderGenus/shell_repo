#include "shell.h"

/**
 * *is_prefix - checks if needle starts with haystack
 * @haystack: the string to check
 * @needle: the string to find
 * Return: address of the next char or haystack or NULL
 */

char *is_prefix(const char *haystack, const char *needle)
{
	while (*haystack && *needle)
	{
		if (*haystack++ != *needle++)
		{
			return (0);
		}
	}
	return ((char*)haystack);
}

/**
 * _strlen - function that returns the length of a string
 * @c : the string to be checked
 * Return: integer length of the string
 */

int _strlen(char *c)
{
	int length = 0;

	while (*c != '\0')
	{
		length++;
		c++;
	}
	return (length);
}
/**
 * _myhistory - display the history list
 * @note: struct param
 * Return: always 0
 */
int _myhistory(note_t *note)
{
	print_list(note->history);
	return (0);
}
