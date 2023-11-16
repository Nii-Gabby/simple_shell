#include "my_shell.h"

/**
 * _dputss - Prints the string input inside
 * @str: The string to be displayed
 *
 * Return: No return value (void)
 */
void _dputss(char *str)
{
	int ix = 0;

	if (!str)
		return;
	while (str[ix] != '\0')
	{
		_stderr(str[ix]);
		ix++;
	}
}

/**
 * _stderr - sends char 'c' to the standard error
 * @c: The char which will be printed
 *
 * Return: 1 if successful
 *         -1 otherwise , and errno appropriately set
 */
int _stderr(char c)
{
	static int ix;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ix >= WRITE_BUF_SIZE)
	{
		write(2, buf, ix);
		ix = 0;
	}
	if (c != BUF_FLUSH)
		buf[ix++] = c;
	return (1);
}

/**
 * _printFd - displays the char 'c'
 * @c: The character to be written
 * @f_d: The target file descriptor for writing
 *
 * Return: 1 for success
 *         -1 for error , and errno appropriately set
 */
int _printFd(char c, int f_d)
{
	static int ix;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ix >= WRITE_BUF_SIZE)
	{
		write(f_d, buf, ix);
		ix = 0;
	}
	if (c != BUF_FLUSH)
		buf[ix++] = c;
	return (1);
}

/**
 * _outputStr - displays the string typed
 * @str: struct containing the string that will be displayed
 * @f_d: identifier for writing
 *
 * Return: The count of characters printed
 */
int _outputStr(char *str, int f_d)
{
	int ix = 0;

	if (!str)
		return (0);
	while (*str)
	{
		ix += _printFd(*str++, f_d);
	}
	return (ix);
}

