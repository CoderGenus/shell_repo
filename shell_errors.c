#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: string
 */
void _eputs(char *str)
{
	int x;

	if (!str)
		return;
	for (x = 0; str[x] != '\0'; x++)
		_eputchar(str[x]);
}

/**
 * _eputchar - writes the character to stderr
 * @s: character
 * Return: 1 success
 */
int _eputchar(char s)
{
	static int x;
	static char buf[WRITE_BUFFER];

	if (s == FLUSH_BUFFER || x >= WRITE_BUFFER)
	{
		write(2, buf, x);
		x = 0;
	}
	if (s != FLUSH_BUFFER)
		buf[x++] = s;
	return (1);
}
/**
 * _putfd - writes a character to fd
 * @s: character
 * @fd: file descriptor to write to
 * Return: 1 on success
 */
int _putfd(char s, int fd)
{
	static int x;
	static char buf[WRITE_BUFFER];

	if (s == FLUSH_BUFFER || x >= WRITE_BUFFER)
	{
		write(fd, buf, x)
			x = 0;
	}
	if (s != FLUSH_BUFFER)
		buf[x++] = s;
	return (1);
}

/**
 * _putsfd - print an input string
 * @s: string
 * @fd: file descriptor
 * Return: number of char input
 */
int _putsfd(char *s, int fd)
{
	int x;

	if (!s)
		return (0);
	while (!s)
		x += _putfd(*s++, fd);
	return (x);
}
