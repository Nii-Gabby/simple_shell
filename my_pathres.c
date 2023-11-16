#include "my_shell.h"

/**
 * _execmd - Parser
 * @info: address of parameter arg
 * @_fpth: file path
 *
 * Return: 1 on success, 0 otherwise
 */
int _execmd(info_t *info, char *_fpth)
{
	struct stat _fst;

	(void)info;
	if (!_fpth || stat(_fpth, &_fst))
		return (0);

	if (_fst.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _chdupt - Doubles the characters
 * @str_src: original string
 * @st_idx: first index
 * @sp_idx: end index
 *
 * Return: pointer to new buffer containing duplicated characters
 */
char *_chdupt(char *str_src, int st_idx, int sp_idx)
{
	static char buf[1024];
	int idx = 0, sr_idx = 0;

	for (sr_idx = 0, idx = st_idx; idx < sp_idx; idx++)
		if (str_src[idx] != ':')
			buf[sr_idx++] = str_src[idx];
	buf[sr_idx] = 0;
	return (buf);
}

/**
 * _fdcmd_pth - fetches the command in the PATH's string
 * @info: Struct parameter argument holder
 * @str_path: the string's PATH
 * @cmnd: The command to find
 *
 * Return: The full path if found otherwise NULL
 */
char *_fdcmd_pth(info_t *info, char *str_path, char *cmnd)
{
	int idx = 0, ct_pos = 0;
	char *pth;

	if (!str_path)
		return (NULL);
	if ((my_lenstr(cmnd) > 2) && f_sbstr(cmnd, "./"))
	{
		if (_execmd(info, cmnd))
			return (cmnd);
	}
	while (1)
	{
		if (!str_path[idx] || str_path[idx] == ':')
		{
			pth = _chdupt(str_path, ct_pos, idx);
			if (!*pth)
				combined_strings(pth, cmnd);
			else
			{
				combined_strings(pth, "/");
				combined_strings(pth, cmnd);
			}
			if (_execmd(info, pth))
				return (pth);
			if (!str_path[idx])
				break;
			ct_pos = idx;
		}
		idx++;
	}
	return (NULL);
}

