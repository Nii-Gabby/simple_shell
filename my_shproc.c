#include "my_shell.h"

/**
 * hsh - Primary shell loop.
 * @info: Pointer to a structure that holds information about input and output.
 * @cmd_args: arguments array from the primary() function
 * Return: 0 if successful
 * 1 - (error), or an error code
 */
int hsh(info_t *info, char **cmd_args)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		_initialinfo(info);
		if (interactive_mode(info))
			_puts("$ ");
		_stderr(BUF_FLUSH);
		r = _gtInp(info);
		if (r != -1)
		{
			_setInfo_(info, cmd_args);
			builtin_ret = _fdbutin(info);
			if (builtin_ret == -1)
				fd_n_exe_cmd(info);
		}
		else if (interactive_mode(info))
			_putchar('\n');
		_relinfo(info, 0);
	}
	sv_hist_file(info);
	_relinfo(info, 1);
	if (!interactive_mode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * _fdbutin - fetches any cmd in library
 * @info: struct pointer
 * Return: -1 not fnd, 0 on successful, 1 - cmd is found but not exe,
 *         -2 if built-in command signals exit()
 */
int _fdbutin(info_t *info)
{
	int idx, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _sExit},
		{"env", pEnv},
		{"help", _sHelp},
		{"history", _History},
		{"setenv", sEnv_var},
		{"unsetenv", unEnv_var},
		{"cd", _sDir},
		{"alias", _ALIAS},
		{NULL, NULL}};

	for (idx = 0; builtintbl[idx].type; idx++)
		if (comp_strs(info->argv[0], builtintbl[idx].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[idx].func(info);
			break;
		}
	return (built_in_ret);
}

