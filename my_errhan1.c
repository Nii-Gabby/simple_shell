#include "my_shell.h"

/**
 * stderrtoi -  Changes a string into an unsigned integer.
 * @str: converting string
 *
 * Return: on success (converted string), -1 on error
 */
int stderrtoi(char *str)
{
	int id = 0;
	unsigned long int ans = 0;

	if (*str == '+')
		str++;
	for (id = 0;  str[id] != '\0'; id++)
	{
		if (str[id] >= '0' && str[id] <= '9')
		{
			ans *= 10;
			ans += (str[id] - '0');
			if (ans > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (ans);
}

/**
 * _emessage - prints out any error message
 * @info: The format that contains the inputs and outputs of a function
 * @estr: error type string
 * Return: 0 for no numbers,
 *            otherwise the converted number.
 *        -1 in case of an error.
 *
 */
void _emessage(info_t *info, char *estr)
{
	_dputss(info->fname);
	_dputss(": ");
	_odec(info->line_count, STDERR_FILENO);
	_dputss(": ");
	_dputss(info->argv[0]);
	_dputss(": ");
	_dputss(estr);
}

/**
 * _odec - func to display an int in base 10.
 * @dn: displayed number
 * @fd: The target file
 *
 * Return: The character_count of characters printed
 */
int _odec(int dn, int fd)
{
	int (*__putchar)(char) = _putchar;
	int id, mul = 0;
	unsigned int _ab_, sup;

	if (fd == STDERR_FILENO)
		__putchar = _stderr;
	if (dn < 0)
	{
		_ab_ = -dn;
		__putchar('-');
		mul++;
	}
	else
		_ab_ = dn;
	sup = _ab_;
	for (id = 1000000000; id > 1; id /= 10)
	{
		if (_ab_ / id)
		{
			__putchar('0' + sup / id);
			mul++;
		}
		sup %= id;
	}
	__putchar('0' + sup);
	mul++;

	return (sup);
}

/**
 * _cnum - the func convert
 * @inu: converting num.
 * @bs: specific base to convert to
 * @fgs: Flags ab argument.
 *
 * Return: just a string
 */

char *_cnum(long int inu, int bs, int fgs)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = inu;

	if (!(fgs & CONVERT_UNSIGNED) && inu < 0)
	{
		n = -inu;
		sign = '-';

	}
	array = fgs & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % bs];
		n /= bs;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * _crem - eliminates all comments (#  \0)
 * @bfr: string modifying struct
 *
 * Return: 0 (On success)
 */
void _crem(char *bfr)
{
	int id;

	for (id = 0; bfr[id] != '\0'; id++)
		if (bfr[id] == '#' && (!id || bfr[id - 1] == ' '))
		{
			bfr[id] = '\0';
			break;
		}
}

