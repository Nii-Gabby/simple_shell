#include "my_shell.h"

/**
 * _initialinfo - Makes info_t struct field initialized
 * @info: Pointer to the info_t struct
 */
void _initialinfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * _setInfo_ - commences info_t struct
 * @info: structure pointer
 * @_argvec: The argument vector
 */
void _setInfo_(info_t *info, char **_argvec)
{
	int id = 0;

	info->fname = _argvec[0];
	if (info->arg)
	{
		info->argv = _strSplit_(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (id = 0; info->argv && info->argv[id]; id++)
			;
		info->argc = id;

		_repalias(info);
		_repvar(info);
	}
}

/**
 * _relinfo - creates more space in  info_t struct
 * @info: struct url
 * @_frall: free fields
 */
void _relinfo(info_t *info, int _frall)
{
	_frstrarray(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (_frall)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			_emplist(&(info->env));
		if (info->history)
			_emplist(&(info->history));
		if (info->alias)
			_emplist(&(info->alias));
		_frstrarray(info->environ);
			info->environ = NULL;
		fr_n_null((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
