#include "shell.h"

/**
 * ret_hist_file - gets the history file
 * @note: struct para
 * Return: allocated str containing history file
 */
char *ret_hist_file(note_t *note)
{
	char *d, *buffer;

	d = _getenv(note, "HOME=");
	if (!d)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(d) + _strlen(FILE_HISTORY) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, d);
	_strcat(buffer, "/");
	_strcat(buffer, FILE_HISTORY);
	return (buffer);
}

/**
 * rec_history - creates a file
 * @note: struct param
 * Return: 1 on succes or -1 otherwise
 */
int rec_history(note_t *note)
{
	ssize_t f;
	char *fn = ret_hist_file(note);
	list_t *n = NULL;

	if (!fn)
		return (-1);
	f = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (f == -1)
		return (-1);
	for (n = note->history; n; n = n->next)
	{
		_putsfd(n->str, f);
		_putfd('\n', f);
	}
	_putfd(FLUSH_BUFFER, f);
	close(f);
	return (1);
}

/**
 * rd_hist - reads the history from file
 * @note: struct param
 * Return: historry count
 *
 */
int rd_hist(note_t *note)
{
	int i, n = 0, count = 0;
	ssize_t f, len, size = 0;
	char *buffer = NULL, *fn = ret_hist_file(note);
	struct stat st;

	if (!fn)
		return (0);
	f = open(fn, O_RDONLY);
	free(fn);
	if (f == -1)
		return (0);
	if (!fstat(f, &st))
		size = st.st_size;
	if (size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (size + 1));
	if (!buffer)
		return (0);
	len = read(f, buffer, size);
	buffer[size] = 0;
	if (len <= 0)
		return (free(buffer), 0);
	close(f);
	for (i = 0; i < size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			append_hist_list(note, buffer + n, count++);
			n = i + 1;
		}
	if (n != i)
		append_hist_list(note, buffer + n, count++);
	free(buffer);
	note->hist_count = count;
	while (note->hist_count-- >= MAX_HISTORY)
		remove_node_at_index(&(note->history), 0);
	reindex_history(note);
	return (note->hist_count);
}

/**
 * append_hist_list - adds to a history list
 * @note:  struct param
 * @buf: buffer
 * @count: the history line count
 * Return: always 0
 */
int append_hist_list(note_t *note, char *buf, int count)
{
	list_t *n = NULL;

	if (note->history)
		n = note->history;
	append_node(&n, buf, count);

	if (!note->history)
		note->history = n;
	return (0);
}

/**
 * reindex_history - reindex the history list after change
 * @note: struct param
 *
 * Return: new count
 */
int reindex_history(note_t *note)
{
	list_t *n = note->history;
	int x = 0;

	while (n)
	{
		n->index = x++;
		n = n->next;
	}
	return (note->hist_count = x);
}
