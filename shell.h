#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

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

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* protypes func for shell.c */
int hsh(info_t *, char **);
int check_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* protype func for parser.c */
int check_cmd(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* prototype funct for errors.c */
void _eputs(char *);
int _eputchar(char);
int _put_file_des(char c, int fd);
int _puts_file_des(char *str, int fd);

/* prototype funct for string.c */
int string_length(char *);
int string_compare(char *, char *);
char *begin_with(const char *, const char *);
char *string_concatenate(char *, char *);

/* protype funct string1.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void print_string(char *);
int _putchar(char);

/* prototype function  for exits.c */
char *string_cpy(char *, char *, int);
char *string_cat(char *, char *, int);
char *string_char(char *, char);

/* prototype func for _tokenizer.c */
char **str_split(char *, char *);
char **str_split2(char *, char);

/* protype funct for realloc.c */
char *set_memo(char *, char, unsigned int);
void free_string(char **);
void *realloc_memo(void *, unsigned int, unsigned int);

/* prototype funct for _memory.c */
int bfree(void **);

/* prototypes for atoi.c */
int is_interactive(info_t *);
int check_delimiters(char, char *);
int check_alpha(int);
int convert_str_int(char *);

/* prototype fun for errors1.c */
int err_atoi(char *);
void display_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void delete_comments(char *);

/* protypes function for _builtin.c */
int my_exit(info_t *);
int change_directory(info_t *);
int my_help(info_t *);

/* protypes for builtins.c */
int my_history(info_t *);
int my_alias(info_t *);

/*protype func for getline.c */
ssize_t get_input(info_t *);
int custom_getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* protype func for getinfo.c */
void remove_info(info_t *);
void create_info(info_t *, char **);
void free_info(info_t *, int);

/* prototypes function for _environ.c */
char *fetch_env(info_t *, const char *);
int print_env(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);
int fill_env_list(info_t *);

/* prottotype funct for getenv.c */
char **fetch_environ(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* prototype funct for _history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* prototypes funct for lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t display_list_str(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* prototype funct for _lists1.c */
size_t list_length(const list_t *);
char **list_to_str(list_t *);
size_t display_list(const list_t *);
list_t *node_begin_with(list_t *, char *, char);
ssize_t fetch_node_index(list_t *, list_t *);

/* prototype functions for vars.c */
int is_chain_delim(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_variables(info_t *);
int replace_str(char **, char *);

#endif

