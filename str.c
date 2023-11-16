#include "my_shell.h"

/**
 * my_lenstr - RETURNS string's LENGTH
 * @str: The STRING whose length to CHK
 *
 * Return: INTEGER STRING LENGTH
 */
int my_lenstr(char *str)
{
	int lth = 0;

	if (!str)
		return (0);

	while (*str++)
		lth++;
	return (lth);
}

/**
 * comp_strs - just compares two STRINGS
 * @strg1: First STRING
 * @strg2: Next STRING
 *
 * Return: Returns a negative value if string1 precedes string2,
 *  a positive value if string1 follows string2,
 * and zero if string1 is equivalent to strg2.
 */
int comp_strs(char *strg1, char *strg2)
{
	while (*strg1 && *strg2)
	{
		if (*strg1 != *strg2)
			return (*strg1 - *strg2);
		strg1++;
		strg2++;
	}
	if (*strg1 == *strg2)
		return (0);
	else
		return (*strg1 < *strg2 ? -1 : 1);
}

/**
 * *f_sbstr - searches main string
 * @hsk: searching STRING
 * @sub: The substring to SEARCH
 *
 * Return: POINTER to next char
 * or NULL
 */
char *f_sbstr(const char *hsk, const char *sub)
{
	while (*sub)
		if (*sub++ != *hsk++)
			return (NULL);
	return ((char *)hsk);
}

/**
 * *combined_strings - Combines two strings
 * @loc: Buffer location
 * @srce: buffer source
 *
 * Return: Address of the location buffer
 */
char *combined_strings(char *loc, char *srce)
{
	char *output = loc;

	while (*loc)
		loc++;
	while (*srce)
		*loc++ = *srce++;
	*loc = *srce;
	return (output);
}

