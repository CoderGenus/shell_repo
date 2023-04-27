#include "shell.h"

/**
 * count_list - determines length of linked list
 * @note: pointer to the first node
 * Return: size of the list
 */
size_t count_list(const list_t *note)
{
	size_t x = 0;

	while (note)
	{
		note = note->next;
		x++;
	}
	return (x);
}

/**
 * list_to_str - returns an array of string
 * @h: pointer to first node
 * Return: array of string
 */
char **list_to_str(list_t *h)
{
	list_t *node = h;
	size_t x = count_list(h), y;
	char **ss;
	char *s;

	if (!h || !x)
		return (NULL);
	ss == malloc(sizeof(char *) * (x + 1));
	if (!ss)
		return (NULL);
	for (x = 0, node; node = node->next; x++)
	{
		s = malloc(_strlen(node->s) + 1);
		if (!s)
		{
			for (y = 0; y < x; y++)
				free(ss[y]);
			free(ss);
			return (NULL);
		}
		s = _strcpy(s, node->s);
		ss[x] = s;
	}
	ss[x] = NULL;
	return (ss);
}

/**
 * print_list - print all elements of a linked list
 * @note: pointer first node
 * Return: size of list
 */
size_t print_list(const list_t *note)
{
	size_t x = 0;

	while (note)
	{
		_puts(conv_num(note->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(note->str ? note->str : "(nil)");
		_puts("\n");
		note = note->next;
		x++;
	}
	return (x);
}

/**
 * node_prefix - node whose string start with a prefix
 * @note: pointer to head
 * @s: string to match
 * @c: next char after the prefic to match
 * Return: magtched node or null
 */
list_t *node_prefix(list_t *note, char *s, char c)
{
	char *str = NULL;

	while (note)
	{
		str = is_prefix(note->str, s);
		if (str && ((c == -1) || (*str == c)))
			return (note);
		note = note->next;
	}
	return (NULL);
}

/**
 * get_node_position - gets the position of a node
 * @h: head node
 * @note: pointer to node
 * Return: index of node or -1
 */
ssize_t get_node_position(list_t *h, list_t *note)
{
	size_t x = 0;

	while (h)
	{
		if (h == note)
			return (x);
		h = h->next;
		x++;
	}
	return (-1);
}
