#include"shell.h"

/**
 * custom_strncpy - Copies a string up to 'n' characters.
 * @destination: The destination string to be copied to.
 * @source: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *custom_strncpy(char *destination, char *source, int n)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return result;
}

/**
 * custom_strncat - Concatenates two strings up to 'n' characters.
 * @destination: The first string.
 * @source: The second string.
 * @n: The maximum number of characters to concatenate.
 *
 * Return: A pointer to the concatenated string.
 */
char *custom_strncat(char *destination, char *source, int n)
{
	int i, j;
	char *result = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return result;
}

/**
 * custom_strchr - Locates a character in a string.
 * @string: The string to be parsed.
 * @character: The character to look for.
 *
 * Return: A pointer to the memory area containing the character,
 * or NULL if the character is not found.
 */
char *custom_strchr(char *string, char character)
{
	do {
		if (*string == character)
			return string;
	} while (*string++ != '\0');

	return NULL;
}


