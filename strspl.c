#include "my_shell.h"

/**
 * **_strSplit_ - divides a STRING into words using specific DELIMETER
 * @str: trped STRING
 * @del: DELIMETER
 *
 * Return: Pointer to an array of strings
 * NULL if failed
 */
char **_strSplit_(char *str, char *del)
{
	int i, j, wd_len, ch_cnt, num_wrds = 0;
	char **output;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!delimeter(str[i], del) &&
				(delimeter(str[i + 1], del) || !str[i + 1]))
			num_wrds++;

	if (num_wrds == 0)
		return (NULL);
	output = malloc((1 + num_wrds) * sizeof(char *));
	if (!output)
		return (NULL);
	for (i = 0, j = 0; j < num_wrds; j++)
	{
		while (delimeter(str[i], del))
			i++;
		wd_len = 0;
		while (!delimeter(str[i + wd_len], del) && str[i + wd_len])
			wd_len++;
		output[j] = malloc((wd_len + 1) * sizeof(char));
		if (!output[j])
		{
			for (wd_len = 0; wd_len < j; wd_len++)
				free(output[wd_len]);
			free(output);
			return (NULL);
		}
		for (ch_cnt = 0; ch_cnt < wd_len; ch_cnt++)
			output[j][ch_cnt] = str[i++];
		output[j][ch_cnt] = 0;
	}
	output[j] = NULL;
	return (output);
}

/**
 * _str_Split2 - divides a STRINGS into 2
 * @str: input strg
 * @del: approved DELIMETER
 *
 * Return: Pointer to array of strings,
 * NULL if failed
 */
char **_str_Split2(char *str, char del)
{
	int i, j, wd_len, ch_cnt, num_wrds = 0;
	char **output;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != del && str[i + 1] == del) ||
		    (str[i] != del && !str[i + 1]) || str[i + 1] == del)
			num_wrds++;
	if (num_wrds == 0)
		return (NULL);
	output = malloc((1 + num_wrds) * sizeof(char *));
	if (!output)
		return (NULL);
	for (i = 0, j = 0; j < num_wrds; j++)
	{
		while (str[i] == del && str[i] != del)
			i++;
		wd_len = 0;
		while (str[i + wd_len] != del && str[i + wd_len]
				&& str[i + wd_len] != del)
			wd_len++;
		output[j] = malloc((wd_len + 1) * sizeof(char));
		if (!output[j])
		{
			for (wd_len = 0; wd_len < j; wd_len++)
				free(output[wd_len]);
			free(output);
			return (NULL);
		}
		for (ch_cnt = 0; ch_cnt < wd_len; ch_cnt++)
			output[j][ch_cnt] = str[i++];
		output[j][ch_cnt] = 0;
	}
	output[j] = NULL;
	return (output);
}

