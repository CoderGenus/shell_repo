#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no number otherwise -1
 */
int _erratoi(char *str)
{
	int n = 0;
	unsigned long int number = 0;

	if (*str == '+')
		s++;

	for (n = 0; str[n] != '\0'; n++)
	{
		if (str[n] >= '0' && str[n] <= '9')
		{
			number *= 10;
			number += (str[n] - '0');
			if (number > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (number);
}

/**
 * print_error - prints an error message
 * @note: the return struct
 * @err: the containing the error
 */
void print_error(note_t *note, char *err)
{
	_eputs(note->filename);
	_eputs(": ");
	print_dec(note->err_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(note->argv[0]);
	_eputs(": ");
	_eputs(err);
}
