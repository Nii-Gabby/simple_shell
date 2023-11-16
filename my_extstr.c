#include "my_shell.h"

/**
 * _cpstr - func to clone string
 * @loc: cloned string arriving location
 * @osce: cloned string true form
 * @_num: total number of cloned strings
 *
 * Return: combined string
 */
char *_cpstr(char *loc, char *osce, int _num)
{
	int sid, did;
	char *s = loc;

	sid = 0;
	while (osce[sid] != '\0' && sid < _num - 1)
	{
		loc[sid] = osce[sid];
		sid++;
	}
	if (sid < _num)
	{
		did = sid;
		while (did < _num)
		{
			loc[did] = '\0';
			did++;
		}
	}
	return (s);
}

/**
 * _catstr - combines two strings
 * @loc: starting string
 * @osce: 1st runner up string
 * @nmax: max used bytes amt
 *
 * Return: The joint string
 */
char *_catstr(char *loc, char *osce, int nmax)
{
	int did, sid;
	char *s = loc;

	did = 0;
	sid = 0;

	while (loc[did] != '\0')
		did++;
	while (osce[sid] != '\0' && sid < nmax)
	{
		loc[did] = osce[sid];
		did++;
		sid++;
	}
	if (sid < nmax)
		loc[did] = '\0';
	return (s);
}

/**
 * *_chstr - looks out for a character in any string
 * @stng: The search parameter
 * @c: The char to look out for
 *
 * Return: char,
 * or NULL if not found
 */
char *_chstr(char *stng, char c)
{
	do {
		if (*stng == c)
			return (stng);
	} while (*stng++ != '\0');

	return (NULL);
}

