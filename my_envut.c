#include "my_shell.h"

/**
 * pEnv - outputs the operating environment
 * @info: Structure that contains all  potential arguments.
 * in maintaining constant function prototype.
 *
 * Return: Always 0 on success
 */
int pEnv(info_t *info)
{
	p_strlist(info->env);
	return (0);
}

/**
 * Env_var - Obtains the value of an _environ variable.
 * @info: This structure holds potential arguments.
 * in maintaining constant function prototype
 * @v_name: Environment variable name
 *
 * Return: NULL or var_value
 */
char *Env_var(info_t *info, const char *v_name)
{
	list_t *node = info->env;
	char *v_value;

	while (node)
	{
		v_value = f_sbstr(node->str, v_name);
		if (v_value && *v_value)
			return (v_value);
		node = node->next;
	}
	return (NULL);
}

/**
 * sEnv_var - Initializes a new environment variable
 * or modify an already existing environment variable
 * @info: Structure containing potential arguments.
 * Employed to maintain constant function prototype.
 *
 * Return: Always 0 on success
 */
int sEnv_var(info_t *info)
{
	if (info->argc != 3)
	{
		_dputss("Incorrect number of arguements\n");
		return (1);
	}
	if (sEnv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unEnv_var - eliminates environment variable
 * @info: Structure that contains all  potential arguments.
 * maintain constant function prototype.
 *
 * Return: Always 0 (Success)
 */

int unEnv_var(info_t *info)
{
	int i;
	if (info->argc < 2)
	{
		_dputss("Too few arguments.\n");
			
			return 1;
	}
	
	for (i = 1; i < info->argc; i++)
	{
		_unEnv(info, info->argv[i]);
	}
	
	return 0;
}

/**
 * pEnv_ls - Expands the environ linked list
 * @info: Structure containing potential arguments
 * (constant function prototype).
 *
 * Return: Always 0 on success
 */
int pEnv_ls(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_appendnode(&node, environ[i], 0);
	info->env = node;
	return (0);
}
