#include "shell.h"

/**
 * main - entry point
 * @ac: argument word count
 * @av: argument vector
 * Return: 0 on success else 1
 */
int main(int ac, char **av)
{
	note_t note[] = { FUNC_INIT };
	int f = 2;

	asm ("mov %1, %0\n\t" "add $3, %0" : "=r" (f) : "r" (f));

	if (ac == 2)
	{
		f = open(av[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(FLUSH_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		note->readfd = f;
	}
	build_env_list(note);
	rd_hist(note);
	hsh(note, av);
	return (EXIT_SUCCESS);
}
