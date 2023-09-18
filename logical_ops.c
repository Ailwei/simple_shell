#include "shell.h"

int handle_logical_operators(const char *input)
{
	char *token = strtok((char *)input, "&&||");
	char *commands[100];
	int index;

	while (token != NULL)
	{
		commands[index++] = token;
		token strtok(NULL, "&&||");
	}
	int result = 0;
	int i;

	for (i = 0; i < index; i++)
	{
		if (strstr(commands[i], "&&"))
		{
			char *cmd1 = strtok(commands[i], "&&");
			char *cmd2 = strtok(NULL, "&&");

			if (execute_command(cmd1) != 0)
			{
				break;
			}
			result = execute_command(cmd2);

		}
		else if (strstr(commands[i], "||"))
		{
			char *cmd1 = strtok(commands[i], "||");
			char *cmd2 = strotok(NULL, "||");

			if (execute_command(cmd1) == 0)
			{
				break;
			}
			result = execute_commands(cmd2);

		}else 
		{
			result = execute_command(commands[i]);
		}
	}
	return (result);
}
