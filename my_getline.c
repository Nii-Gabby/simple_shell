#include "my_shell.h"

/**
 * bufferChained_commands - maintains a sequence of interconnected commands
 * @info: Struct that holds aparameters
 * @c_buf: chained command buffer addresss
 * @b_len: length variable address
 *
 * Return: Number of bytes read
 */

ssize_t bufferChained_commands(info_t *info, char **c_buf, size_t *b_len)
{
	ssize_t b_read = 0;
	size_t _blen = 0;

	if (!*b_len)
	{

		free(*c_buf);
		*c_buf = NULL;
		signal(SIGINT, sig_intHandler);
#if USE_GETLINE
		bytes_read = getline(chain_buf, &buffer_len, stdin);
#else
		b_read = ctm_gtline(info, c_buf, &_blen);
#endif
		if (b_read > 0)
		{
			if ((*c_buf)[b_read - 1] == '\n')
			{
				(*c_buf)[b_read - 1] = '\0';
				b_read--;
			}
			info->linecount_flag = 1;
			_crem(*c_buf);
			_add_hist_list(info, *c_buf, info->histcount++);

			{
				*b_len = b_read;
				info->cmd_buf = c_buf;
			}
		}
	}
	return (b_read);
}

/**
 * _gtInp - fetches a line omitting newline character
 * @info: Struct to hold parameter arguments
 *
 * Return: Num bytes read
 */
ssize_t _gtInp(info_t *info)
{
	static char *c_buf;
	static size_t i, j, b_len;
	ssize_t b_read = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	b_read = bufferChained_commands(info, &c_buf, &b_len);
	if (b_read == -1)
		return (-1);
	if (b_len)
	{
		j = i;
		p = c_buf + i;

		chk_chn_cnd(info, c_buf, &j, i, b_len);
		while (j < b_len)
		{
			if (chk_chn_del(info, c_buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= b_len)
		{
			i = b_len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (my_lenstr(p));
	}

	*buf_p = c_buf;
	return (b_read);
}

/**
 * readBuffer - Processes data from a temporary storage area.
 * @info: Container holding the parameters of an argument.
 * @buff: _bufer
 * @_pz: _size
 *
 * Return: bytes_read
 */
ssize_t readBuffer(info_t *info, char *buff, size_t *_pz)
{
	ssize_t b_read = 0;

	if (*_pz)
		return (0);
	b_read = read(info->readfd, buff, READ_BUF_SIZE);
	if (b_read >= 0)
		*_pz = b_read;
	return (b_read);
}

/**
 * ctm_gtline - Fetches the subsequent line of
 * input from the standard input (stdin).
 * @info: Structure holding parameter argument
 * @pt: pointer  address to buffer, preallocated or NULL
 * @lth: Size of preallocated pt buffer if not NULL
 *
 * Return: total_bytes_read
 */
int ctm_gtline(info_t *info, char **pt, size_t *lth)
{
	static char c_buf[READ_BUF_SIZE];
	static size_t i, b_len;
	size_t k;
	ssize_t b_read = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pt;
	if (p && lth)
		s = *lth;
	if (i == b_len)
		i = b_len = 0;

	b_read = readBuffer(info, c_buf, &b_len);
	if (b_read == -1 || (b_read == 0 && b_len == 0))
		return (-1);

	c = _chstr(c_buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - c_buf) : b_len;
	new_p = _ctm_rlloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_catstr(new_p, c_buf + i, k - i);
	else
		_cpstr(new_p, c_buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (lth)
		*lth = s;
	*pt = p;
	return (s);
}

/**
 * sig_intHandler - Manages the Ctrl-C interrupt signal.
 * @s_num: The signal num parameter
 */
void sig_intHandler(__attribute__((unused)) int s_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

