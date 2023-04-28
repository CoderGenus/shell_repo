#include "shell.h"

/**
 *_myatoi - converts a string to an integer
 *@a: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _myatoi(char *a)
{
	int i;
	int sign = 1;
	int note = 0;
	int give;
	unsigned int result = 0;

	if (a[i] == ' ')
	{
		i++;
	}

	for (i = 0;  a[i] != '\0' && note != 2; i++)
	{
		if (a[i] == '-')
		{
			sign *= -1;
		}
		else if (a[i] == '+')
		{
			i++;
		}

		if (a[i] >= '0' && a[i] <= '9')
		{
			note = 1;
			result = result * 10 + (a[i] - '0');
			i++;
		}
		else if (note == 1)
		{
			note = 2;
		}
	}
	if (sign == -1)
		give = -result;
	else
		give = result;

	return (give);
}

/**
 * is_interactive - returns 1 if shell is in interactive mode
 * @notice: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive(note_t *notice)
{
	return (isatty(fileno(stdin)) && notice->readfd <= 2);
}

/**
 * conv_num - has the function of a converter
 * @digit: the numner to be coverted
 * @origin: origin
 * @flags: argument flags
 *
 * Return: string
 */
char *conv_num(long int digit, int origin, int flags)
{
	static char *nums;
	static char buff[50];
	char sign = 0;
	char *ptr = &buff[49];
	unsigned long b = digit;

	if (!(flags & CONVERT_UNSIGNED) && digit < 0)
	{
		b = -digit;
		sign = '-';
	}

	nums = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	*ptr = '\0';

	do {
		*--ptr = nums[b % origin];
		b /= origin;
	} while (b != 0);

	if (sign != 0)
	{
		*--ptr = sign;
	}

	return (ptr);
}

/**
 * del_comments - function that replaces first instance of '#' with '\0'
 * @str: pointer to thestring to be modified
 *
 * Return: Nothing.
 */

void del_comments(char *str)
{
	int i;
	int com_start = -1;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == '#' && (i == 0 || str[i - 1] == ' '))
		{
			com_start = i;
			break;
		}
	if (com_start != -1)
	{
		str[com_start] = '\0';
	}
}
