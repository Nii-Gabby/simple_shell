#include "my_shell.h"

/**
 * *_adnode - commence point of linked list
 * @_hnode: Pointer  address to the headnode
 * @s_data: string field node
 * @num_id: Index for cur_node history
 *
 * Return: Size of the LIST
 */
list_t *_adnode(list_t **_hnode, const char *s_data, int num_id)
{
	list_t *new_head;

	if (!_hnode)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	ctm_mset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num_id;
	if (s_data)
	{
		new_head->str = _strdup(s_data);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *_hnode;
	*_hnode = new_head;
	return (new_head);
}

/**
 * *_appendnode - Adds cur_node at the end of list
 * @_hnode: Pointer address(head node)
 * @_data: field of the node string
 * @num_id: used history Node index
 *
 * Return: Size of updated linked list
 */
list_t *_appendnode(list_t **_hnode, const char *_data, int num_id)
{
	list_t *n_node, *old_node;

	if (!_hnode)
		return (NULL);

	old_node = *_hnode;
	n_node = malloc(sizeof(list_t));
	if (!n_node)
		return (NULL);
	ctm_mset((void *)n_node, 0, sizeof(list_t));
	n_node->num = num_id;
	if (_data)
	{
		n_node->str = _strdup(_data);
		if (!n_node->str)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (old_node)
	{
		while (old_node->next)
			old_node = old_node->next;
		old_node->next = n_node;
	}
	else
		*_hnode = n_node;
	return (n_node);
}

/**
 * p_strlist - shows _str_ element of a linked list
 * @_hnode: Pointer address of the head_node
 *
 * Return: Linked lists size bytes
 */
size_t p_strlist(const list_t *_hnode)
{
	size_t cnt = 0;

	while (_hnode)
	{
		_puts(_hnode->str ? _hnode->str : "(nil)");
		_puts("\n");
		_hnode = _hnode->next;
		cnt++;
	}
	return (cnt);
}

/**
 * eliminate_node_at_index - Eliminates a designated at a
 * specified index in the linked list.
 * @_hnode: Pointer address of _hnode
 * @id: Id of the to be eliminate
 *
 * Return: 1 (successful), 0 for failure
 */
int eliminate_node_at_index(list_t **_hnode, unsigned int id)
{
	list_t *first_node, *late_node;
	unsigned int cnt = 0;

	if (!_hnode || !*_hnode)
		return (0);

	if (!id)
	{
		first_node = *_hnode;
		*_hnode = (*_hnode)->next;
		free(first_node->str);
		free(first_node);
		return (1);
	}
	first_node = *_hnode;
	while (first_node)
	{
		if (cnt == id)
		{
			late_node->next = first_node->next;
			free(first_node->str);
			free(first_node);
			return (1);
		}
		cnt++;
		late_node = first_node;
		first_node = first_node->next;
	}
	return (0);
}

/**
 * _emplist - Frees up memory allocated by nodes in the list.
 * @head_ptr: Pointer structto the _hnode cur_node
 *
 * Return: Void
 */
void _emplist(list_t **head_ptr)
{
	list_t *c_node, *nt_node, *hd_node;

	if (!head_ptr || !*head_ptr)
		return;
	hd_node = *head_ptr;
	c_node = hd_node;
	while (c_node)
	{
		nt_node = c_node->next;
		free(c_node->str);
		free(c_node);
		c_node = nt_node;
	}
	*head_ptr = NULL;
}

