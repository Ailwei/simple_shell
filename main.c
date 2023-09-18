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

        /* Split the input into commands using ';' */
         commands = handle_separators(line);

        /* Iterate through the commands and execute them */
        for ( i = 0; commands[i] != NULL; i++)
        {
            /* Copy the command to the command buffer */
            strncpy(command, commands[i], sizeof(command));

            /* Remove the trailing newline character */
            command_length = strlen(command);
            if (command_length > 0 && command[command_length - 1] == '\n')
            {
                command[command_length - 1] = '\0';
            }

            /* Handle built-in commands and external commands */
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
                else
                {
                    /* Execute the command */
                    if (strstr(command, " ") != NULL)
                    {
                        /* Command has arguments, use execute_command_with_args */
                        char *space_position = strchr(command, ' ');
                        const char *arguments = space_position + 1;
                        execute_cmd_args(command, arguments);
                    }
                    else
                    {
                        /* Command has no arguments, use execute_command */
                        execute_command(command);
                    }
                }
            }
        }

        /* Free the memory allocated for commands */
        for ( i = 0; commands[i] != NULL; i++)
        {
            free(commands[i]);
        }
        free(commands);

        /* Free the memory allocated by custom_getline */
        free(line);
    }

    return 0;
}

