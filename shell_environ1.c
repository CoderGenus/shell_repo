#include "shell.h"

/**
 * _setenv - function that initializes a new env variable
 *or modifies the existing one
 * @note: structure with arguments
 * @varab: the pointer to env var
 * @val: pointer to env var
 *
 * Return: Always 0.
 */

int _setenv(note_t *note, char *varab, char *val)
{
	list_t *nod;
	char *new_var = NULL;
	char *b;
<<<<<<< HEAD
=======
	size_t var_len = _strlen(varab);
	size_t val_len = _strlen(val);
>>>>>>> 79c21b3296715902c8a6394600c70e6815593217

	if (varab == NULL || val == NULL)
	{
		return (-1);
	}

<<<<<<< HEAD
	new_var = malloc(_strlen(varab) + 1 + _strlen(val) + 1);
=======
	new_var = (char *) malloc(var_len + 1 + val_len + 1);
>>>>>>> 79c21b3296715902c8a6394600c70e6815593217

	if (new_var == NULL)
	{
		return (-1);
	}

<<<<<<< HEAD
	_strcpy(new_var, varab);
=======
	_strcpy(new_var, val);
>>>>>>> 79c21b3296715902c8a6394600c70e6815593217
	_strcat(new_var, "=");
	_strcat(new_var, val);
	nod = note->env;

	while (nod != NULL)
	{
		b = is_prefix(nod->str, varab);
		if (b && *b == '=')
		{
			free(nod->str);
			nod->str = new_var;
			note->environ_changed = 1;
			return (0);
		}
		nod = nod->next;
	}
	append_node(&(note->env), new_var, 0);
	free(new_var);
	note->environ_changed = 1;
	return (0);
}

/**
 * get_environ - function returns a string array copy of env var
 * @note: structure with arguements
 *
 * Return: Always 0 (Success);
 */

char **get_environ(note_t *note)
{
	{
<<<<<<< HEAD
		if (note->environ == NULL || note->environ_changed != 0)
		{
			note->environ = list_to_str(note->env);
			note->environ_changed = 0;
		}
		return (note->environ);
	}
	return (NULL);
=======
		note->environ = list_to_str(note->env);
		note->environ_changed = 0;
	}

	return (note->environ);
>>>>>>> 79c21b3296715902c8a6394600c70e6815593217
}

/**
 * _unsetenv - function removes an env var
 * @note: structure containing arguements
 * @varab: the string environ variable
 *
 * Return: 1 on delete, 0 on  otherwise
 */

int _unsetenv(note_t *note, char *varab)
{
	char *s;
	list_t *ext = note->env;
	size_t i = 0;

	if (ext == NULL || varab == NULL)
	{
		return (0);
	}

	while (ext != NULL)
	{
		s = is_prefix(ext->str, varab);
		if (s && *s == '=')
		{
			note->environ_changed = remove_node_at_index(&(note->env), i);
			i = 0;
			ext = note->env;
			continue;
		}
		ext = ext->next;
		i++;
	}
<<<<<<< HEAD

=======
>>>>>>> 79c21b3296715902c8a6394600c70e6815593217
	return (note->environ_changed);
}
