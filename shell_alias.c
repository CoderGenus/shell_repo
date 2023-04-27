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
	del_ret = delete_node_at_index(&(note->alias),
		get_node_index(note->alias, node_dtsrtd_with(info->alias, p_str, -1)));
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

	f = _strchr(str, '=');
	if (f == NULL)
	{
		return (1);
	}
	if (*++f == NULL)
	{
		return (unset_alias(note, p_str));
	}
	unset_alias(note, p_str);
	return (add_node_end(&(note->alias), p_str, 0) == NULL);
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

	if (node == NULL)
	{
		return (1);
	}
	else
	{
		*equal_sign = _strchr(fud->str, '=');
		for (x = fud->str; x <= equal_sign; x++)
			_putchar(*x);
		_putchar('\'');
		_putchar(' ');
		_puts(p + 1);
		_putchar('\n');
		return (0);
	}
	return (0);
}
