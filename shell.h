#ifndef SHELL_H
#define SHELL_H

/*Header files*/

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* functions prototypes */

void execute_command(const char *command);
void execute_command_with_args(char *command);
void execute_command_with_path(char *command, char *path, char *shell_name);
void exit_shell(char *shell_name);
void env_builtin(char **envp);
char *custom_getline(void);
void execute_cmd_args(const char *command, const char *arguments);
void handle_exit(const char *status);
int unset_env(const char *variable);
int set_env(const char *variable, const char *value);
int handle_cd(const char *directory);
char **handle_separators(char *input);
int handle_logical_operators(const char *input);

/*declared vars */

#define MAX_PATH_LENGTH 1024
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10
#define BUFFER_SIZE 1024
#define MAX_COMMANDS 100

/*declare environ */
extern char **environ;


#endif /* SHELL_H */

