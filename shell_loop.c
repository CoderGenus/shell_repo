#include "shell.h"

/**
 * hsh - main shell loop
 * @note: the return struct
 * @av: the argument vector
 * Return: 0 on success
 */
int hsh(note_t *note, char **av)
{
	ssize_t i = 0;
	int bet = 0;

	while (r != -1 && bet != -2)
	{
		clear_note(note);
		if (is_interactive(note))
			_puts("$ ");
		_eputchar(FLUSH_BUFFER);
		i = read_input(note);
		if (i != -1)
		{
			set_note(note, av);
			bet = search_bubiltin(note);
			if (bet == -1)
				search_cmd(note);
		}
		else if (is_interactive(note))
			_putchar('\n');
		free_note(note, 0);
	}
	rec_history(note);
	free_note(note, 1);
	if (!is_interactive(note) && note->status)
		exit(note->status);
	if (bet == -2)
	{
		if (note->err_index == -1)
			exit(note->status);
		exit(note->err_index);
	}
	return (bet);
}

/**
 * search_builtin - searches for a builtin command
 * @note: reutrn struct
 * Return: -1 if builtin not found,
 *	0 if builtin exectued successfully
 *	1 if builtin found but not successful
 *	-2 if builtin signals exit
 */
int search_builtin(note_t *note)
{
	int n, ret = -1;
	builtin_t builtintable[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (n = 0; builtintable[n].type; n++)
		if (_strcmp(note->argv[0], builtinttable[n].type) == 0)
		{
			note->err_count++;
			ret = builtintable[n].func(note);
			break;
		}
	return (ret);
}

/**
 * search_cmd - find a commandin PATH
 * @note: return struct
 */
void search_cmd(note_t *note)
{
	int i, j;
	char *path = NULL;

	note->path = note->argv[0];
	if (note->line_count_flag == 1)
	{
		note->err_count++;
		note->line_count_flag = 0;
	}
	for (i = 0, j = 0; note->arg[i]; i++)
		if (!is_delim(note->arg[i], " \t\n"))
			j++;
	if (!j)
		return;
	path = search_path(note, _getenv(note, "PATH="), noteargv[0]);
	if (path)
	{
		note->path = path;
		fork_cmd(note);
	}
	else
	{
		if ((is_interactive(note) || _getenv(note, "PATH=")
					|| note->argv[0][0] == '/') &&
				is_cmd(note, note->argv[0]))
			fork_cmd(note);
		else if (*(note->arg) != '\n')
		{
			note->status = 127;
			print_error(note, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks an exec thred to run
 * @note: return struct
 */
void fork_cmd(note_t *note)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(note->path, note->argv, get_environ(note)) == -1)
		{
			free_note(note, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(note->status));
		if (WIFEXITED(note->status))
		{
			note->status = WEXITSTATUS(note->status);
			if (note->status == 126)
				print_error(note, "Permission denied\n");
		}
	}
}
