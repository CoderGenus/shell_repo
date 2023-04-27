#include "shell.h"

/**
 * *chars_cp - duplicates characters
 * @pathstr: the path of the string
 * @begin: the starting position
 * @end: the stopping position
 * Return: pointer to a new buffer
 */

char *chars_cp(char *pathstr, int begin, int end)
{
	static char buf[1024];
	int i = 0;
	int j = 0;

	for (j = 0, i = begin; i < end; i++)
		if (pathstr[i] != ':')
			buf[j++] = pathstr[i];
	buf[j] = 0;
	return (buf);
}

/**
 * search_path - function that finds this cmd in the path string
 * @note: the note struct
 * @pathstr: the Path string
 * @cmd: the cmd to be found
 * Return: full path of cmd if found or NULL.
 */

char *search_path(note_t *note, char *pathstr, char *cmd)
{
	int i = 0;
	int pres_pos = 0;
	char *path;

	if (pathstr == NULL)
	{
		return (NULL);
	}

	if ((_strlen(cmd) > 2) && is_prefix(cmd, "./"))
	{
		if (is_cmd(note, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = chars_cp(pathstr, pres_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(note, path))
				return (path);
			if (!pathstr[i])
				break;
			pre_pos = i;
		}
		i++;
	}
	return (NULL);
}


/**
 * is_cmd - determines if a file is anm executable command
 * @note: the note struct
 * @path: path to the file
 *
 * Return: 1 if True, 0 Otherwise
 */

int is_cmd(note_t *note, char *path)
{
	struct stat st;

	(void)note;
	if (!path || stat(path, &st))
	{
		return (0);
	}
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
