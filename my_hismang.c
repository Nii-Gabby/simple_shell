#include "my_shell.h"

/**
 * _gthist_fpath - Fetches the contents of the history file.
 * @info: A parameter structure holder
 *
 * Return: A dynamically assigned string that holds
 * the content of the history file..
 */
char *_gthist_fpath(info_t *info)
{
	char *buff, *hm_d;

	hm_d = Env_var(info, "HOME=");
	if (!hm_d)
		return (NULL);
	buff = malloc(sizeof(char) * (my_lenstr(hm_d)
				+ my_lenstr(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_cpy_str(buff, hm_d);
	combined_strings(buff, "/");
	combined_strings(buff, HIST_FILE);
	return (buff);
}
/**
 * sv_hist_file - Creates a new history
 * file or concatenate to an existing file.
 * @info: A struct parameter holder
 *
 * Return: 1 when successful, or -1 when it fails
 */
int sv_hist_file(info_t *info)
{
	ssize_t _fdsc;
	char *filename = _gthist_fpath(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	_fdsc = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (_fdsc == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_outputStr(node->str, _fdsc);
		_printFd('\n', _fdsc);
	}
	_printFd(BUF_FLUSH, _fdsc);
	close(_fdsc);
	return (1);
}

/**
 * _rhistory - fetches the hist file's data or infp
 * @info: Parameter information holder
 *
 * Return: if successful, 0 otherwise
 */
int _rhistory(info_t *info)
{
	int i, lst = 0, linecount = 0;
	ssize_t _fdsc, _rdlen, _fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = _gthist_fpath(info);

	if (!filename)
		return (0);

	_fdsc = open(filename, O_RDONLY);
	free(filename);
	if (_fdsc == -1)
		return (0);
	if (!fstat(_fdsc, &st))
		_fsize = st.st_size;
	if (_fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (_fsize + 1));
	if (!buff)
		return (0);
	_rdlen = read(_fdsc, buff, _fsize);
	buff[_fsize] = 0;
	if (_rdlen <= 0)
		return (free(buff), 0);
	close(_fdsc);
	for (i = 0; i < _fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			_add_hist_list(info, buff + lst, linecount++);
			lst = i + 1;
		}
	if (lst != i)
		_add_hist_list(info, buff + lst, linecount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		eliminate_node_at_index(&(info->history), 0);
	rfrsh_hist_numbs(info);
	return (info->histcount);
}

/**
 * _add_hist_list - concatates the start of linked list
 * @info: potential arguments struct
 * @p_buf: The added buf to path
 * @line_count: as the name
 *
 * Return: 0 if yes
 */
int _add_hist_list(info_t *info, char *p_buf, int line_count)
{
	list_t *nw_nd = NULL;

	if (info->history)
		nw_nd = info->history;
	_appendnode(&nw_nd, p_buf, line_count);

	if (!info->history)
		info->history = nw_nd;
	return (0);
}

/**
 * rfrsh_hist_numbs - Updates or refreshes a
 * linked list after making modifications.
 * @info: potential arguments struct
 *
 * Return: The refreshed history item count.
 */
int rfrsh_hist_numbs(info_t *info)
{
	list_t *node = info->history;
	int cnt = 0;

	while (node)
	{
		node->num = cnt++;
		node = node->next;
	}
	return (info->histcount = cnt);
}

