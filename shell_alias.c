#include "shell.h"

/**
 * remove_alias - function that unsets alias string.
 * @note: struct parameter.
 * @p_str: pointer to the string alias.
 *
 * Return: Always 0 (Success), 1 on error.
 */

int remove_alias(note_t *note, char *p_str)
{
	char *a;
	char s;
	int del_ret;

	a = _strchr(p_str, '=');
	if (a == NULL)
	{
		return (1);
	}
	s = *a;
	*a = 0;
	del_ret = remove_node_at_index(&(note->alias),
		get_node_position(note->alias, node_prefix(note->alias, p_str, -1)));
	*a = s;
	return (del_ret);
}

/**
 * set_alias - sets an alias string
 * @note: struct argument
 * @p_str: pointer to the string alias
 *
 * Return: Always 0 (Success), 1 on error.
 */

int set_alias(note_t *note, char *p_str)
{
	char *f;

	f = _strchr(p_str, '=');
	if (!f)
	{
		return (1);
	}
	if (!*++f)
	{
		return (remove_alias(note, p_str));
	}
	remove_alias(note, p_str);
	return (append_node(&(note->alias), p_str, 0) == NULL);
}

/**
 * print_alias - function that prints an alias string
 * @fud: the alias node
 *
 * Return: Always 0 (Success), 1 on error
 */

int print_alias(list_t *fud)
{
	char *equal_sign = NULL;
	char *x = NULL;

	if (fud == NULL)
	{
		return (1);
	}
	else
	{
		equal_sign = _strchr(fud->str, '=');
		for (x = fud->str; x <= equal_sign; x++)
			_putchar(*x);
		_putchar('\'');
		_putchar(' ');
		_puts(equal_sign + 1);
		_putchar('\n');
		return (0);
	}
	return (0);
}
