#include "shell.h"

/**
 * set_memo - fill memory with a constant byte
 * @str: the pointer to the memory area
 * @b: the byte to fill *str with
 * @n: the amount of byte to fill
 * Return: (s) a pointer to the memory area s
 */
char *set_memo(char *str, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		str[i] = b;
	return (str);
}

/**
 * free_memo - free a string of strings
 * @pp: string of strings
 */
void free_string(char **pp)
{
	char **b = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(b);
}

/**
 * realloc_memo - reallocate  block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *realloc_memo(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *z;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	z = malloc(new_size);
	if (!z)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		z[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (z);
}

