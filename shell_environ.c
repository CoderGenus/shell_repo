#include "shell.h"

/**
 * _myenv - prints the current environment
 * @note: struct oara
 * Return: always 0
 */
int _myenv(note_t *note)
{
	display_list_str(note->env);
	return (0);
}

/**
 * _getenv - get the value of an environ variable
 * @note: struct para
 * @var: env var name
 * Return: value
 */
char *_getenv(note_t *note, const char *var)
{
	list_t *n = note->env;
	char *c;

	while (n)
	{
		c = is_prefix(n->str, var);
		if (c && *c)
			return (c);
		n = n->next;
	}
	return (NULL);
}

/**
 * _mysetenv - new enviraon variable
 * @note: struct para
 * Return: always 0
 */
int _mysetenv(note_t *note)
{
	if (note->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(note, note->argv[1], note->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - remove an eviron variable
 * @note: struct para
 * Return: always 0
 */
int _myunsetenv(note_t *note)
{
	int n;

	if (note->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (n = 1; n <= note->argc; n++)
		_unsetenv(note,  note->argv[n]);
	return (0);
}

/**
 * build_env_list - populate env list
 * @note: struct para
 * Return: always 0
 */
int build_env_list(note_t *note)
{
	list_t *nod = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		append_node(&nod, environ[n], 0);
	note->env = nod;
	return (0);
}
