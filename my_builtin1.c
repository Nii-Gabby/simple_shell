#include "my_shell.h"

/**
 * _History - shows history of recent commands
 * @info: potential arguments structs to maintain constant prototype
 *
 * Return: 0 Always
 */
int _History(info_t *info)
{
	_disp_list(info->history);
	return (0);
}

/**
 * _UNSETAlias - Takes out an alias string from the alias list
 * @info: struct parameter.
 * @str: The string to removed as an alias
 *
 * Return: 0 if successful, 1 on error.
 */
int _UNSETAlias(info_t *info, char *str)
{
	char *point, tp_char;
	int rett;

	point = _chstr(str, '=');
	if (!point)
		return (1);
	tp_char = *point;
	*point = 0;
	rett = eliminate_node_at_index(&(info->alias),
		gt_nde_pst(info->alias, _nde_srt_fder(info->alias, str, -1)));
	*point = tp_char;
	return (rett);
}

/**
 * _SETAlias - to add an alias string to the alias list
 * @info: Struct potential arguments
 * @str: The string of an alias.
 *
 * Return: 0 successful, 1 on error.
 */
int _SETAlias(info_t *info, char *str)
{
	char *pnt;

	pnt = _chstr(str, '=');
	if (!pnt)
		return (1);
	if (!*++pnt)
		return (_UNSETAlias(info, str));

	_UNSETAlias(info, str);
	return (_appendnode(&(info->alias), str, 0) == NULL);
}

/**
 * _singleAlias - Shows an alias string.
 * @node: The alias node to be displayed.
 * Return: 0 if successful, 1 otherwise.
 */
int _singleAlias(list_t *node)
{
	char *pnt = NULL, *a_value = NULL;

	if (node)
	{
		pnt = _chstr(node->str, '=');
		for (a_value = node->str; a_value <= pnt; a_value++)
			_putchar(*a_value);
		_putchar('\'');
		_puts(pnt + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _ALIAS - imitates the 'alias' builtin
 * @info: Structure containing possible
 * arguments to maintain constant prototype
 * Return: Always 0.
 */

int _ALIAS(info_t *info)
{
	char *pnt = NULL;
	int i = 0;
	list_t *node = NULL;


	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_singleAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		pnt = _chstr(info->argv[i], '=');
		if (pnt)
			_SETAlias(info, info->argv[i]);
		else
			_singleAlias(_nde_srt_fder(info->alias, info->argv[i], '='));
	}

	return (0);
}

