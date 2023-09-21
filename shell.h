#ifndef  SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
#define CUSTOM_WRITE_BUF_SIZE 1024
#define CUSTOM_BUF_FLUSH '\n'

extern char **environ;

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} Custom_Lists;

typedef struct Shellpsser


{

	int read_file_descriptor;
	char *arguments;
	char **argumentVector;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	Custom_Lists *env;
	Custom_Lists *history;
	Custom_Lists *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
}ShellInfo;







/* functions prototypes atoic.c*/

int custom_atoi(char *s);
int custom_is_alpha(int c);
int is_delimiter(char c, char *delimiter_str);
int is_interactive(ShellInfo *info);

/* functions prototypes errors */

void custom_puts_error(char *error_string);
int custom_putchar_error(char c);
int custom_putchar_fd(char c, int fd);
int custom_puts_fd(char *str, int fd);
int custom_atoi(char *str);
void print_custom_error(ShellInfo *info, char *error_type);
int print_custom_d(int input, int fd);
char *custom_convert_number(long int num, int base, int flags);
void remove_custom_comments(char *buf);

/* functions getlineinfo.c */

void freeShellInfo(ShellInfo *info, int all);
void setShellInfo(ShellInfo *info, char **av);
void initializeShellInfo(ShellInfo *info);
void blockCtrlC(__attribute__((unused)) int sigNum);
int customGetline(ShellInfo *info, char **pointer, size_t *length);
ssize_t readBuffer(ShellInfo *info, char *buffer, size_t *currentIndex);
ssize_t getInput(ShellInfo *info);
ssize_t bufferInput(ShellInfo *info, char **buffer, size_t *bufferSize);

/* functions protypes memory.c  */

int bfree(void **ptr);

/*protypes of history.c */

int renumber_history_entries(ShellInfo *info);
int add_history_entry(ShellInfo *info, char *entry, int linecount);
int read_history_from_file(ShellInfo *info);
int write_history_to_file(ShellInfo *info);
char *get_history_filename(ShellInfo *info);

/*prototypes of parser.c */

char *find_command_path(ShellInfo *info, char *pathstr, char *cmd);
char *duplicate_chars(char *pathstr, int start, int stop);
int is_executable(ShellInfo *info, char *path);

/*prototypes of strings */

int print_character(char c);
void print_string(char *str);
char *string_duplicate(const char *str);
char *string_copy(char *destination, char *source);
char *str_concatenate(char *dest, char *src);
char *starts_with(const char *haystack, const char *needle);
int str_compare(char *s1, char *s2);
int str_length(char *s);

/*prototypes of lists */

ssize_t custom_get_node_index(Custom_Lists *head, Custom_Lists *node);
Custom_Lists *custom_list_starts_with(Custom_Lists *node, char *prefix, char c);
size_t custom_list_print(const Custom_Lists *head);
char **custom_list_to_strings(Custom_Lists *head);
size_t custom_list_length(const Custom_Lists *head);
void custom_free_list(Custom_Lists **head_ptr);
int custom_delete_node_at_index(Custom_Lists **head, unsigned int index);
size_t custom_print_list_data(const Custom_Lists *h);
Custom_Lists *add_custom_node_end(Custom_Lists **head, const char *data, int number);
Custom_Lists *add_custom_node(Custom_Lists **head, const char *data, int number);

/*prototypes for builtin */

int custom_help(ShellInfo *info);
int custom_change_directory(ShellInfo *info);
int custom_exit(ShellInfo *info);
int custom_display_history(ShellInfo *info);
int custom_unset_alias(ShellInfo *info, char *str);
int custom_set_alias(ShellInfo *info, char *str);
int custom_print_alias(Custom_Lists *node);
int custom_alias(ShellInfo *info);

/*prototypes for tokenizer.c */

char **splitStringByDelimiter(char *str, char delimiter);
char **splitStringByDelimiters(char *str, char *delimiters);

/*prototypes for variables.c */

int isChainDelimiter(ShellInfo *info, char *buf, size_t *p);
void checkChain(ShellInfo *info, char *buf, size_t *p, size_t i, size_t len);
int replaceAliases(ShellInfo *info);
int replaceVariables(ShellInfo *info);
int replaceString(char **old, char *new);

/*prototypes for gtenv. v */

char **getEnvironment(ShellInfo *info);
int unsetEnvironmentVariable(ShellInfo *info, char *variable);
int setEnvironmentVariable(ShellInfo *info, char *variable, char *value);

/*prototypes for enviro.c */

int custom_print_environment(ShellInfo *info);
char *custom_get_environment_variable(ShellInfo *info, const char *name);
int custom_set_environment_variable(ShellInfo *info);
int custom_unset_environment_variable(ShellInfo *info);
int custom_populate_environment_list(ShellInfo *info);

/*protypes for shell.c */

int shell_loop(ShellInfo *info, char **av);
int find_builtin(ShellInfo *info);
void find_command(ShellInfo *info);
void fork_command(ShellInfo *info);
 /* main */

int main(int argc, char **argv);







#endif
