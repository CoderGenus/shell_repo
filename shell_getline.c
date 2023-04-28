#include "shell.h"

/**
 * input_buffer - bufer input
 * @note: struct argument
 * @buffer: address for buffer
 * @var: address of var
 * Return: read bytes
 */
ssize_t input_buffer(note_t *note, char **buffer, size_t *var)
{
	ssize_t s = 0;
	size_t p = 0;

	if (!*var)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigint_handler);
#if GETLINE
		s = getline(buffer, &p, stdin);
#else
		s = _getline(note, buffer, p);
#endif
		if (s > 0)
		{
			if ((*buffer)[s - 1] == '\n')
			{
				(*buffer)[s - 1] = '\0';
				s--;
			}
			note->line_count_flag = 1;
			del_comments(*buffer);
			append_hist_list(note, *buffer, note->host_count++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*var = r;
				note->cmd_buffer = buffer;
			}
		}
	}
	return (s);
}

/**
 * read_input - reads a line minus the new line
 * @note: struct parameter
 * Return: bytes read
 */
ssize_t read_input(note_t *note)
{
	char **buffer_ptr = &(note->arg), *ptr;
	ssize_t s = 0;
	static size_t i, j, var;
	static char *buffer;

	_putchar(FLUSH_BUFFER);
	S = input_buffer(note, &buffer, &var);
	if (s == -1)
		return (-1);
	if (var)
	{
		j = i;
		ptr = buffer + i;

		check_chain(note, buffer, &j, i, var);
		while (j < var)
		{
			if (is_chain(note, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= var)
		{
			i = var = 0;
			note->cmd_buffer_type = NORMAL_CMD;
		}

		*buffer_ptr = ptr;
		return (_strlen(ptr));
	}
	*buffer_ptr = buffer;
	return (s);
}

/**
 * read_buffer - reads a buffer
 * @note: struct para
 * @buffer: buffer
 * @s: size
 * Return: size of buffer
 */
ssize_t read_buffer(note_t *note, char *buffer, size_t *s)
{
	ssize_t t = 0;

	if (*s)
		return (0);
	t = read(note->readfd, buffer, READ_BUFFER);
	if (t >= 0)
		*s = t;
	return (t);
}

/**
 * _getline - gets the next line of input from stdin
 * @note: struct para
 * @ptr: address of pointer to buffer
 * @var: size of preallocated ptr
 * Return: size
 */
int _getline(note_t *note, char *ptr, size_t *var)
{
	char *p = NULL, *new_ptr = NULL, *cm;
	static size_t i, length;
	size_t j;
	ssize_t x = 0, y = 0;
	static char buffer[READ_BUFFER];

	p = *ptr;
	if (p && var)
		y = *var;
	if (i == length)
		i = length = 0;
	x = read_buffer(note, buffer, &length);
	if (x == -1 || (x == 0 && length == 0))
		return (-1);
	cm = _strchr(buffer + i. '\n');
	j = cm ? 1 + (unsigned int)(cm - buffer) : length;
	new_ptr = _realloc(p, y, y ? y + j : j + 1);
	if (!new_ptr)
		return (p ? free(p), -1 : -1);
	if (y)
		_strcat(new_ptr, buffer + i, j - i);
	else
		_strncpy(new_ptr, buffer + i, j - i + 1);
	y += j - i;
	i = j;
	p = new_ptr;

	if (var)
		*var = y;
	*ptr = p;
	return (y);
}
/**
 * sigint_handler - block of ctrl-c
 * @num: the signal number
 */
void sigint_handler(__attribute__((unused))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUFFER);
}
