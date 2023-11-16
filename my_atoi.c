#include "my_shell.h"

/**
 * interactive_mode - Checks if shell is functioning in interactive mode
 * @info: struct pointer
 * Return: 1 if yes, otherwise 0
 */

int interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * delimeter - proves delimiter characters
 * @d: The character to be proven
 * @d_str: string of delimeter
 *
 * Return: Prints 1 if yes, 0 otherwise
 */

int delimeter(char d, char *d_str)
{
	while (*d_str)
		if (*d_str++ == d)
			return (1);
	return (0);
}

/**
 * _alpha - Looks out for an alphabetic character
 * @a: The character to check
 *
 * Return: 1 for alphabetic character, otherwise 0
 */
int _alpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _stin - Changes a given string into an integer
 * @ins: The input string
 * Return: result, otherwise 0
 */
int _stin(char *ins)
{
	int i, sign = 1, flag = 0, result;
	unsigned int Value = 0;

	for (i = 0;  ins[i] != '\0' && flag != 2; i++)
	{
		if (ins[i] == '-')
			sign *= -1;

		if (ins[i] >= '0' && ins[i] <= '9')
		{
			flag = 1;
			Value *= 10;
			Value += (ins[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -Value;
	else
		result = Value;

	return (result);
}

