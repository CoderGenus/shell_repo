#include "shell.h"

/**
 * _myexit - exits the shell
 * @note: structure containing argument
 * Return: exit with a given status
 */
int _myexit(note_t *note)
{
	if (note->argv[1])
	{
		int exit_code = _erratoi(note->argv[1]);

		if (exit_code == -1)
		{
			note->ststus = 2;
			print_error(note, "Illegal number: ");
			_eputs(note->argv[1]);
			_eputchar('\n');
			return (1);
		}
		note->err_index = exit_code;
	}
	note->err_index = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @note: structure containing argument
 * Return: always 0
 */
int _mycd(note_t *note)
{
	char *current_dir, *dir, buffer[1024];
	int ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("getcwd() error\n");
	if (!note->argv[1])
	{
		dir = _getenv(note, "HOME=");
		if (!dir)
		{
			dir = _getenv(note, "PWD=");
			ret = chdir(dir ? dir : "/");
		}
		else
			ret = chdir(dir);
	}
	else if (_strcmp(note->argv[1], "-") == 0)
	{
		if (!_getenv(note, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(note, "OLDPWD="));
		_putchar('\n');
		ret = chdir((_getenv(note, "OLDPWD=")) ? _getenv(note, "OLDPWD=") : "/");
	}
	else
		ret = chdir(note->argv[1]);
	if (ret == -1)
	{
		print_error(note, "can't cd to");
		_eputs(note->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(note, "OLDPWD", _getenv(note, "PWD="));
		_setenv(not, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * _myhelp - changes the current dir
 * @note: structure containing argument
 * Return: always 0;
 */
int _myhelp(note_t *note)
{
	char **arr;

	arr = note->argv;
	_puts("the help call works but but the function is not implemented \n");
	if (0)
		_puts(*arr);
	return (0);
}

/**
 * _myhistory - displays the history list
 * @note: structure containing argument
 * Return: always 0
 */
int _myhistory(note_t *note)
{
	print_list(note->history);
	return (0);
}
