#include "my_shell.h"

/**
 * main - start point of code execution
 * @aCnt: count parameter
 * @aVctr: vector parameter
 *
 * Return: 0 if successful otherwise 1
 */
int main(int aCnt, char **aVctr)
{
	info_t info[] = { INFO_INIT };
	int fl_d = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fl_d)
		: "r" (fl_d));

	if (aCnt == 2)
	{
		fl_d = open(aVctr[1], O_RDONLY);
		if (fl_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_dputss(aVctr[0]);
				_dputss(": 0: Can't open ");
				_dputss(aVctr[1]);
				_stderr('\n');
				_stderr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fl_d;
	}
	pEnv_ls(info);
	_rhistory(info);
	hsh(info, aVctr);
	return (EXIT_SUCCESS);
}

