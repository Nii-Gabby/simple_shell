#include "my_shell.h"

/**
 * ctm_mset - Writes a specific byte value to fill a memory area.
 * @m_area: mem area struct pointer
 * @b_value: value of filled byte
 * @lth: length
 *
 * Return: Address of the memory area which is modified
**/
char *ctm_mset(char *m_area, char b_value, unsigned int lth)
{
	unsigned int idx;

	for (idx = 0; idx < lth; idx++)
		m_area[idx] = b_value;
	return (m_area);
}

/**
 * _frstrarray - Deallocates memory used by an array of strings.
 * @str_array: Array of strings to be freed
 *
 * Return: void
 */
void _frstrarray(char **str_array)
{
	char **tpm = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(tpm);
}

/**
 *  _ctm_rlloc - Adjusts the size of a previously allocated memory block.
 * @ptr: Reference to the initially allocated memory block.
 * @src_size: bytes of source block.
 * @nw_size: size of new block
 *
 * Return: A pointer to nw_size
 */
void *_ctm_rlloc(void *ptr, unsigned int src_size, unsigned int nw_size)
{
	char *nw_ptr;

	if (!ptr)
		return (malloc(nw_size));
	if (!nw_size)
		return (free(ptr), NULL);
	if (nw_size == src_size)
		return (ptr);

	nw_ptr = malloc(nw_size);
	if (!nw_ptr)
		return (NULL);

	src_size = src_size < nw_size ? src_size : nw_size;
	while (src_size--)
		nw_ptr[src_size] = ((char *)ptr)[src_size];
	free(ptr);
	return (nw_ptr);
}

