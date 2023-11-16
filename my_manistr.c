#include "my_shell.h"

/**
 * chk_chn_del - Verifies whether the present character
 * in the buffer serves as a chain delimiter.
 * @info: struct par
 * @bfrr: buf char
 * @pst: position address
 *
 * Return: 1 if successfull, 0 if not
 */
int chk_chn_del(info_t *info, char *bfrr, size_t *pst)
{
	size_t id = *pst;

	if (bfrr[id] == '|' && bfrr[id + 1] == '|')
	{
		bfrr[id] = 0;
		id++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (bfrr[id] == '&' && bfrr[id + 1] == '&')
	{
		bfrr[id] = 0;
		id++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (bfrr[id] == ';')
	{
		bfrr[id] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pst = id;
	return (1);
}

/**
 * chk_chn_cnd - Assesses wther the chain process should persist
 * @info: structt para
 * @bfrr: buff para
 * @pst: current position address
 * @i: buff start point
 * @lth: buff length
 *
 * Return: Void.
 */
void chk_chn_cnd(info_t *info, char *bfrr,
		size_t *pst, size_t i, size_t lth)
{
	size_t id = *pst;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			bfrr[i] = 0;
			id = lth;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			bfrr[i] = 0;
			id = lth;
		}
	}

	*pst = id;
}

/**
 * _repalias -  changes the aliases in the tknized str
 * @info: The struct para
 *
 * Return: 1 if replacement occurs, 0 otherwise.
 */
int _repalias(info_t *info)
{
	int i;
	list_t *node;
	char *pst;

	for (i = 0; i < 10; i++)
	{
		node = _nde_srt_fder(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		pst = _chstr(node->str, '=');
		if (!pst)
			return (0);
		pst = _strdup(pst + 1);
		if (!pst)
			return (0);
		info->argv[0] = pst;
	}
	return (1);
}

/**
 * _repvar - changes variables in the tknized str
 * @info: struct par
 *
 * Return: 1 if suffecfull occurs, 0 otherwise.
 */
int _repvar(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!comp_strs(info->argv[i], "$?"))
		{
			repStrs(&(info->argv[i]),
				_strdup(_cnum(info->status, 10, 0)));
			continue;
		}
		if (!comp_strs(info->argv[i], "$$"))
		{
			repStrs(&(info->argv[i]),
				_strdup(_cnum(getpid(), 10, 0)));
			continue;
		}
		node = _nde_srt_fder(info->env, &info->argv[i][1], '=');
		if (node)
		{
			repStrs(&(info->argv[i]),
				_strdup(_chstr(node->str, '=') + 1));
			continue;
		}
		repStrs(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * repStrs - changes the source string
 * @src_str: string to be replaced
 * @nw_str: replaced string
 *
 * Return: 1(success), 0 otherwise.
 */
int repStrs(char **src_str, char *nw_str)
{
	free(*src_str);
	*src_str = nw_str;
	return (1);
}

