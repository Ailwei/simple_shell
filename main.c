#include "shell.h"

int main(void)
{
    size_t i;
    char *line;
    size_t command_length;
    char *shell_name = "hsh";
    char command[MAX_COMMAND_LENGTH];
    char **commands;

    /* Get the PATH environment variable */
    char *path_env = getenv("PATH");
    if (path_env == NULL)
    {
        perror("Unable to get PATH");
        return 1;
    }

    while (1)
    {
        /* Display the shell prompt */
        printf("%s> ", shell_name);
        fflush(stdout);

        /* Read a command line using custom_getline */
        line = custom_getline();

        /* Check for Ctrl + D (EOF) */
        if (line == NULL)
        {
            printf("\nExiting %s.\n", shell_name);
            break;
        }
	/* check if entered command is alias */
	if (strncmp(line, "alias ", 6) == 0)
	{
		alias_builtin(handle_separators(line));
		continue;
	}
	else
	{

        /* Split the input into commands using ';' */
        commands = handle_separators(line);

        /* Iterate through the commands and execute them */
        for (i = 0; commands[i] != NULL; i++)
        {
            /* Copy the command to the command buffer */
            strncpy(command, commands[i], sizeof(command));

            /* Remove the trailing newline character */
            command_length = strlen(command);
            if (command_length > 0 && command[command_length - 1] == '\n')
            {
                command[command_length - 1] = '\0';
            }

            /* Handle built-in commands, logical operators, and external commands */
            if (command_length > 0)
            {
                if (strcmp(command, "exit") == 0)
                {
                    /* Handle the "exit" builtin command */
                    exit_shell(shell_name);
                }
                else if (strncmp(command, "exit ", 5) == 0)
                {
                    /* Handle "exit" with status */
                    const char *status = command + 5;
                    handle_exit(status);
                }
                else if (strcmp(command, "env") == 0)
                {
                    /* Handle the "env" builtin command */
                    env_builtin(environ);
                }
                else if (strncmp(command, "setenv ", 7) == 0)
                {
                    /* Handle "setenv" command */
                    char *arguments = command + 7;
                    const char *variable = strtok(arguments, " ");
                    const char *value = strtok(NULL, " ");

                    if (variable != NULL && value != NULL)
                    {
                        if (set_env(variable, value) != 0)
                        {
                            perror("Failed to set environment variable");
                        }
                    }
                    else
                    {
                        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                    }
                }
                else if (strncmp(command, "unsetenv ", 9) == 0)
                {
                    /* Handle "unsetenv" command */
                    char *variable = command + 9;

                    if (unset_env(variable) != 0)
                    {
                        perror("Failed to unset environment variable");
                    }
                }
                else if (strncmp(command, "cd", 2) == 0)
                {
                    /* Handle "cd" command */
                    const char *directory = command + 2;
                    handle_cd(directory);
                }
                else
                {
                    /* Execute the command with logical operators */
                    int result = handle_logical_operators(command);
                    if (result == -1)
                    {
                        fprintf(stderr, "Failed to handle logical operators\n");
                    }
                }
            }
        }

        /* Free the memory allocated for commands */
        for (i = 0; commands[i] != NULL; i++)
        {
            free(commands[i]);
        }
        free(commands);
	

        /* Free the memory allocated by custom_getline */
        free(line);
    }

    return 0;
}
return 0;
}
