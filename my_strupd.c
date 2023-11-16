#include "my_shell.h"

/**
 * *_cpy_str - replicates a STRING.
 * @loc: The BUFFE LOCATION
 * @srce: The SOURCE STRING to be REPLICATED
 *
 * Return: location buffer
 */
char *_cpy_str(char *loc, char *srce)
{
	int id = 0;

	if (loc == srce || srce == 0)
		return (loc);
	while (srce[id])
	{
		loc[id] = srce[id];
		id++;
	}
	loc[id] = 0;
	return (loc);
}

/**
 * _strdup - Creates a duplicate of a string.
 * @str: The string to be duplicated.
 *
 * Return: A pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--str;
	return (result);
}

/**
 * _puts - SHOWS a given INPUT STRING
 * @str: The string to be SHOWED.
 *
 * Return: NOTHING
 */
void _puts(char *str)
{
	int id = 0;

	if (!str)
		return;
	while (str[id] != '\0')
	{
		_putchar(str[id]);
		id++;
	}
}

/**
 * _putchar - Displays the character 'c' on
 * the standard output (stdout).
 * @c: The specified character intended for writing
 * Return: Returns 1 (successful)
 * On ERROR, returns -1 and sets the appropriate ERRNO.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

