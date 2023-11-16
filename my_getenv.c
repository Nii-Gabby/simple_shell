#include "my_shell.h"

/**
 * gEnv - function to get array of strings in the envi
 * @info: all potential argument struct to maintain the func prototype cons
 *
 * Return: 0 when successful
 */


char **gEnv(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = _string_listarray(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unEnv - eliminates environment variable with the help of unEnv func.
 * @info: A structure that holds possible arguments (const prototype)
 * @var: The eliminating string property
 *
 * Return: 1 if successfully eliminating, 0 otherwise.
 */

int _unEnv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = f_sbstr(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = eliminate_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * sEnv - deploys or modify a new or an existing environment variable
 * @info: potential arguments struct ensuring constant function prototype
 * @var: environment variable string property.
 * @value: The string value environ
 *
 * Return: 0 (Success)
 */
int sEnv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(my_lenstr(var) + my_lenstr(value) + 2);
	if (!buf)
		return (1);
	_cpy_str(buf, var);
	combined_strings(buf, "=");
	combined_strings(buf, value);
	node = info->env;
	while (node)
	{
		p = f_sbstr(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_appendnode(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

