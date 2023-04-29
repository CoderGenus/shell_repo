#include "shell.h"

/**
 * set_note - function initializes note_t struct
 * @note: pointer holds struct address
 * @arg_v: argumeny vector
 *
 * Return; Nothing.
 */

void set_note(note_t *note, char **arg_v)
{
	int a = 0;

	note->filename = arg_v[0];
	if (note->arg != 0)
	{
<<<<<<< HEAD
		note->argv = split_string(note->arg, " \t");
=======
		note->argv = strtok(note->arg, " \t");
>>>>>>> f074dab0e685f83569d5dca556fa1d7160970375
		if (note->argv == NULL)
		{
			note->argv = malloc(sizeof(char *) * 2);
			if (note->argv != 0)
			{
				note->argv[0] = _strdup(note->arg);
				note->argv[1] = NULL;
			}
		}

		for (a = 0; note->argv && note->argv[a]; a++)
			;
		note->argc = 1;

		resolve_alias(note);
		resolve_vars(note);
	}
}

/**
 * free_note - function that frees note_t struct fields
 * @note: pointer holds struct address
 * @every: true if every field is free
 */

void free_note(note_t *note, int every)
{
	free_str(note->argv);
	note->path = NULL;
	note->argv = NULL;

	if (every)
	{
		if (!note->cmd_buffer)
			free(note->arg);
		if (!note->env)
			free_list(&(note->env));
		if (note->history)
			free_list(&(note->history));
		if (note->alias)
			free_list(&(note->alias));
		free_str(note->environ);
			note->environ = NULL;
		free_ptr((void **)note->cmd_buffer);
		if (note->readfd > 2)
			close(note->readfd);
		_putchar(FLUSH_BUFFER);
	}
}

/**
 * clear_note - clears note_t struct
 * @note: pointer holds struct address
 *
 */

void clear_note(note_t *note)
{
	note->arg = NULL;
	note->argv = NULL;
	note->path = NULL;
	note->argc = 0;
}
