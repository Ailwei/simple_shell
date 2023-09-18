#include "shell.h"

/**
 * handle_separators - Split the input into commands using ';' as the separator
 * @input: The input string containing commands separated by ';'
 *
 * Return: An array of strings representing individual commands.
 */

char **handle_separators(char *input)
{
	char *token;
	size_t num_commands = 0;
	char **commands = malloc(MAX_COMMANDS * sizeof(char *));

	if (commands == NULL)
	{
		perror("Failed to allocated memory for commands");
		return NULL;
	}
	num_commands = 0;
	token = strtok(input, ";");
 while (token != NULL)
 {
	 commands[num_commands++] = strdup(token);

	 if (num_commands >= MAX_COMMANDS)
	 {
		 fprintf(stderr, "Too many commands, ignoring the rest\n");
		 break;
	 }
	 token = strtok(NULL, ";");
 }
 commands[num_commands] = NULL;

 return commands;
}
