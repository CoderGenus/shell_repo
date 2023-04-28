#include "shell.h"

/**
 * resolve_vars - replaces vars in the tokenized string
 * @note: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int resolve_vars(note_t *note)
{
	int i = 0;
	list_t *node;

	for (i = 0; note->argv[i]; i++)
	{
		if (note->argv[i][0] != '$' || !note->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			resolve_string(&(note->argv[i]),
				_strdup(conv_num(note->status, 10, 0)));
			continue;
		}
		if (!_strcmp(note->argv[i], "$$"))
		{
			resolve_string(&(note->argv[i]),
				_strdup(conv_num(getpid(), 10, 0)));
			continue;
		}
		node = node_prefix(note->env, &note->argv[i][1], '=');
		if (node)
		{
			resolve_string(&(note->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		resolve_string(&note->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * is_chain - tests if current char in buffer is a chain delimeter
 * @note: the parameter struct
 * @buffer: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_chain(note_t *note, char *buffer, size_t *p)
{
	size_t i = *p;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		note->cmd_buffer_type = OR_CMD;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		note->cmd_buffer_type = AND_CMD;
	}
	else if (buffer[i] == ';') /* found end of this command */
	{
		buffer[i] = 0; /* replace semicolon with null */
		note->cmd_buffer_type = CHAIN_CMD;
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * resolve_alias - replaces an aliases in the tokenized string
 * @note: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int resolve_alias(note_t *note)
{
	int i;
	list_t *node;
	char *b;

	for (i = 0; i < 10; i++)
	{
		node = node_prefix(note->alias, note->argv[0], '=');
		if (!node)
			return (0);
		free(note->argv[0]);
		b = _strchr(node->str, '=');
		if (!b)
			return (0);
		b = _strdup(b + 1);
		if (!b)
			return (0);
		note->argv[0] = b;
	}
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @note: the parameter struct
 * @buffer: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buffer
 *
 * Return: Void
 */
void check_chain(note_t *note, char *buffer, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (note->cmd_buffer_type == AND_CMD)
	{
		if (note->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	if (note->cmd_buffer_type == OR_CMD)
	{
		if (!note->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * resolve_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int resolve_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
