#include "shell.h"

/*Function to skip lines starting '#' */

void skip_comments(char **line)
{
	if ((*line)[0] == '#')
	{
		free(*line);
		*line = NULL;
	}
}
