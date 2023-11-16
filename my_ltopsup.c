#include "my_shell.h"

/**
 * lt_lth - Calculates the length of nodes
 * @_hnode: Pointer of the head node
 *
 * Return: Length of the LIST
 */
size_t lt_lth(const list_t *_hnode)
{
	size_t cnt = 0;

	while (_hnode)
	{
		_hnode = _hnode->next;
		cnt++;
	}
	return (cnt);
}

/**
 * _string_listarray - Converts a list of strings into an array of strings.
 * @head: Pointer node of the list struct(first)
 *
 * Return: Array of concatated strings
 */
char **_string_listarray(list_t *head)
{
	list_t *node = head;
	size_t cnt = lt_lth(head), id;
	char **str_arr;
	char *str;

	if (!head || !cnt)
		return (NULL);
	str_arr = malloc(sizeof(char *) * (cnt + 1));
	if (!str_arr)
		return (NULL);
	for (cnt = 0; node; node = node->next, cnt++)
	{
		str = malloc(my_lenstr(node->str) + 1);
		if (!str)
		{
			for (id = 0; id < cnt; id++)
				free(str_arr[id]);
			free(str_arr);
			return (NULL);
		}

		str = _cpy_str(str, node->str);
		str_arr[cnt] = str;
	}
	str_arr[cnt] = NULL;
	return (str_arr);
}

/**
 * _disp_list - shows the "elements" of a linked list
 * @_hnode: Pointer to the first node's address
 *
 * Return: The num nodes in the list
 */
size_t _disp_list(const list_t *_hnode)
{
	size_t cnt = 0;

	while (_hnode)
	{
		_puts(_cnum(_hnode->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(_hnode->str ? _hnode->str : "(nil)");
		_puts("\n");
		_hnode = _hnode->next;
		cnt++;
	}
	return (cnt);
}

/**
 * _nde_srt_fder - seeks node with a predetermined pre_fix
 * @node: Pointer of the headnode address
 * @pfix: The prefix to pair against
 * @ch_match: The particular character to match to
 *
 * Return: The most likely node or NULL if no match found
 */
list_t *_nde_srt_fder(list_t *node, char *pfix, char ch_match)
{
	char *sfix = NULL;

	while (node)
	{
		sfix = f_sbstr(node->str, pfix);
		if (sfix && ((ch_match == -1) || (*sfix == ch_match)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * gt_nde_pst - fetches the index node
 * @hed: Pointer of the head node
 * @trgt_node: Pointer to the node looked for
 *
 * Return:(index) of the node or
 * -1 if the node is not found
 */
ssize_t gt_nde_pst(list_t *hed, list_t *trgt_node)
{
	size_t cnt = 0;

	while (hed)
	{
		if (hed == trgt_node)
			return (cnt);
		hed = hed->next;
		cnt++;
	}
	return (-1);
}

