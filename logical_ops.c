#include "shell.h"

/**
 * handle_logical_operators - Handle logical operators in shell commands
 * @input: The input command string
 *
 * Description:
 * This function splits a command line into multiple commands separated by
 * logical operators (&& or ||) and executes them based on the operators.
 *
 * Return:
 * The exit status of the last executed command.
 */
int handle_logical_operators(const char *input)
{
	int result = 0;
    int i;
    char *token = strtok((char *)input, "&&||");
    char *commands[100];
    int index = 0;

    while (token != NULL)
    {
        commands[index++] = token;
        token = strtok(NULL, "&&||");
    }

 
    for (i = 0; i < index; i++)
    {
        if (strstr(commands[i], "&&"))
        {
            char *cmd1 = strtok(commands[i], "&&");
            char *cmd2 = strtok(NULL, "&&");

            if (execute_command(cmd1) != 0)
            {
                /* Handle the case where cmd1 failed (non-zero return) */
                break;
            }

            result = execute_command(cmd2);
        }
        else if (strstr(commands[i], "||"))
        {
            char *cmd1 = strtok(commands[i], "||");
            char *cmd2 = strtok(NULL, "||");

            if (execute_command(cmd1) == 0)
            {
                /* Handle the case where cmd1 succeeded (zero return) */
                break;
            }

            result = execute_command(cmd2);
        }
        else
        {
            /* Handle the case without logical operators */
            result = execute_command(commands[i]);
        }
    }

    return result;
}

