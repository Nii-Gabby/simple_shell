#include "my_shell.h"

/**
 * fr_n_null - Frees the memory associated with a pointer
 * assigns the address to NULL.
 * @ptr: pointer address to free.
 *
 * Return: 1 if successful, if not 0.
 */
int fr_n_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
