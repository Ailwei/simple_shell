#include "shell.h"

/**
 * custom_getline - Custom function to read a line from stdin
 *
 * Return: Pointer to the read line, or NULL on EOF or error
 */

char *custom_getline(void)
{

static char buffer[BUFFER_SIZE];
static size_t index = 0;
static size_t length = 0;
char *line = NULL;
size_t line_length = 0;
 char *new_line;

while (1)
{
	if (index >= length)
	{
		length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (length <= 0)
		{
			if (line_length > 0)
			{
				line[line_length] = '\0';
				return (line);
			}
			else
			{
				return (NULL);
			}
		}
		index = 0;
	}
	new_line = realloc(line, line_length + 1);
	if (new_line == NULL)
	{
		perror("Memory allocation error");
		free(line);
		return (NULL);
	}
	line  = new_line;

	while (index < length && buffer[index] != '\n')
	{
		line[line_length++] = buffer[index++];

	}
	if (index < length && buffer[index] == '\n')
	{
		line[line_length++] = '\0';
		index++;
		return (line);
	}
}
}

