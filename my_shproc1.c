#include "my_shell.h"

/**
 * fk_n_exe_cmd - Forks to execute a command
 * @info: Struct parameter
 *
 * Return: void
 */
void fk_n_exe_cmd(info_t *info)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(info->path, info->argv, gEnv(info)) == -1)
		{
			_relinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_emessage(info, "Permission denied\n");
		}
	}
}

/**
 * fd_n_exe_cmd - Locates cmd in the file PATH and executes it
 * @info: Struct containing information
 *
 * Return: void, nothing
 */
void fd_n_exe_cmd(info_t *info)
{
	char *pth = NULL;
	int idx, ag_cnt;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (idx = 0, ag_cnt = 0; info->arg[idx]; idx++)
		if (!delimeter(info->arg[idx], " \t\n"))
			ag_cnt++;
	if (!ag_cnt)
		return;

	pth = _fdcmd_pth(info, Env_var(info, "PATH="), info->argv[0]);
	if (pth)
	{
		info->path = pth;
		fk_n_exe_cmd(info);
	}
	else
	{
		if ((interactive_mode(info) || Env_var(info, "PATH=")
					|| info->argv[0][0] == '/') && _execmd(info, info->argv[0]))
			fk_n_exe_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_emessage(info, "not found\n");
		}
	}
}

