#include "my_shell.h"

/**
 * _sExit - ends the shell fully.
 * @info: struct's potential arguments
 * This function facilitates a controlled termination of the shell.
 * If info.argv[0] does not equal "exit", it terminates with a status of 0.
 *  Otherwise,
 * it concludes the shell execution after performing the required cleanup.
 * Return: Exits with specified status; returns 0 if info.argv[0]
 *         isn't "exit".
 */
int _sExit(info_t *info)
{
	int Exit;

	if (info->argv[1])
	{
		Exit = stderrtoi(info->argv[1]);
		if (Exit == -1)
		{
			info->status = 2;
			_emessage(info, "Illegal number: ");
			_dputss(info->argv[1]);
			_stderr('\n');
			return (1);
		}
		info->err_num = stderrtoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _sDir - new directory
 * @info: potential arguments variable.
 *
 * Return: 0 (Success)
 */
int _sDir(info_t *info)
{
	char *cPath, *nPath, buffer[1024];
	int chdir_output;

	cPath = getcwd(buffer, 1024);
	if (!cPath)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		nPath = Env_var(info, "HOME=");
		if (!nPath)
			chdir_output =
				chdir((nPath = Env_var(info, "PWD=")) ? nPath : "/");
		else
			chdir_output = chdir(nPath);
	}
	else if (comp_strs(info->argv[1], "-") == 0)
	{
		if (!Env_var(info, "OLDPWD="))
		{
			_puts(cPath);
			_putchar('\n');
			return (1);
		}
		_puts(Env_var(info, "OLDPWD=")), _putchar('\n');
		chdir_output =
			chdir((nPath = Env_var(info, "OLDPWD=")) ? nPath : "/");
	}
	else
		chdir_output = chdir(info->argv[1]);
	if (chdir_output == -1)
	{
		_emessage(info, "can't cd to ");
		_dputss(info->argv[1]), _stderr('\n');
	}
	else
	{
		sEnv(info, "OLDPWD", Env_var(info, "PWD="));
		sEnv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _sHelp - shows help information
 * @info: Structure containing potential arguments.
 * to maintain a uniform fucntion prototype
 *
 * Return: Always 0 (Success)
 */
int _sHelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

