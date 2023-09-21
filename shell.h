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

/* definitions */

#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH '\0'
#define DELIM " \t\r\n\a"
#define HIST_MAX 4096
#define HIST_FILE ".simple_shell_history"
#define BUFSIZE 1024
#define BUF_FLUSH 0

/*structure to shell info */

typedef struct ShellInfo
{
	char *str;
	int num;
	ShellHistoryEntry *history;
    int histcount;
	int readfd;
	int status;
    char **argv;
    char *arg;
    char **env;
    char **alias;
    char *path;
    int line_count;
    int err_num;
    int linecount_flag;
    int cmd_buf_type;
}ShellInfo;

typedef struct builtins
{
	char *type;
	int (*func)(ShellInfo *);
} builtin_table;
typedef struct List
{
    char *data;
    size_t number;
    struct List *next;
} list_t;
/*history functions */

char *_strdup(const char *str);
char *_strcpy(char *dest, const char *src);
void _puts(const char *str);
void _putchar(char c);
void _putsfd(const char *str, int fd);
void _putcharfd(char c, int fd);
int _strlen(const char *str);
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_memset(char *s, char b, unsigned int n);
int _strncmp(const char *s1, const char *s2, size_t n);
char *get_env_var(char **env, const char *name);
ShellHistoryEntry *add_history_entry(ShellInfo *info, char *entry, int linecount);
int renumber_history_entries(ShellInfo *info);

/* main shell loop */

int hsh(ShellInfo *info, char **av);
/* Custom string functions */
char *_custom_strcpy(char *dest, const char *src);
char *_custom_strcat(char *dest, const char *src);
size_t _custom_strlen(const char *str);
char *_custom_strdup(const char *str);
char *_custom_strchr(const char *str, int c);
char *_custom_strtok(char *str, const char *delim);

/* Custom standard I/O functions */

ssize_t _custom_putchar(char c);
ssize_t _custom_puts(const char *s);
ssize_t _custom_eputs(const char *s);

/* Custom number conversion functions */
char *_custom_itoa(int n, int base);
char *_custom_utoa(unsigned int n, int base);
char *_custom_itoa_long(long n, int base);
char *_custom_utoa_long(unsigned long n, int base);

/* builtins util */

/* Custom list functions */
size_t custom_list_length(const CustomList *head);
char **custom_list_to_strings(CustomList *head);
size_t custom_list_print(const CustomList *head);
CustomList *custom_list_starts_with(CustomList *node, char *prefix, char c);
ssize_t custom_get_node_index(CustomList *head, CustomList *node);

char *_set_memory(char *s, char b, unsigned int n);
void free_strings(char **str_arr);
void *_reallocate(void *ptr, unsigned int old_size, unsigned int new_size);

/*parser.c */

int hsh(ShellInfo *info, char **av);
int is_executable(ShellInfo *info, char *path);
char *duplicate_chars(char *pathstr, int start, int stop);
char *find_command_path(ShellInfo *info, char *pathstr, char *cmd);

/* variables.c prototype */

int isChainDelimiter(ShellInfo *shellInfo, char *buf, size_t *p);
void checkChain(ShellInfo *shellInfo, char *buf, size_t *p, size_t i, size_t len);
int replaceAliases(ShellInfo *shellInfo);
int replaceVariables(ShellInfo *shellInfo);
int replaceString(char **old, char *new);

/*atoc.c functions prototypes */

int checkInteractiveMode(ShellInfo *shellInfo);
int isDelimiter(char character, char *delimiters);
int isAlphabetic(int character);
int stringToInteger(char *str);

/* builtins.c prototypes */

int exitShell(ShellInfo *shellInfo);
int changeDirectory(ShellInfo *shellInfo);
int showHelp(ShellInfo *shellInfo);

 /*okrnizer.c ptotoypes */

char **splitStringByDelimiters(char *str, char *delimiters);
char **splitStringByDelimiter(char *str, char delimiter);

/* strings1.c protoypes */

char *string_copy(char *destination, char *source);
char *string_duplicate(const char *str);
void print_string(char *str);
int print_character(char c);

/*strings.c prototypes */

int str_length(char *s);
int str_compare(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *str_concatenate(char *dest, char *src);

/*shell.c prototypes*/

int shell_loop(ShellInfo *info, char **av);
int find_builtin(ShellInfo *info);
void find_command(ShellInfo *info);
void fork_command(ShellInfo *info);
void clear_info(ShellInfo *info);
int interactive(ShellInfo *info);
ssize_t get_input(ShellInfo *info);
void set_info(ShellInfo *info, char **av);
void write_history(ShellInfo *info);
void free_info(ShellInfo *info, int mode);
int my_exit(ShellInfo *info);
int my_env(ShellInfo *info);
int my_help(ShellInfo *info);
int my_history(ShellInfo *info);
int my_setenv(ShellInfo *info);
int my_unsetenv(ShellInfo *info);
int my_cd(ShellInfo *info);
int my_alias(ShellInfo *info);
int is_delimiter(char c, char *delimiters);
int is_command(ShellInfo *info, const char *cmd);
char *find_path(ShellInfo *info, char *paths, char *cmd);
char **strtow(char *str, char *delimiters);
int _strcmp(const char *s1, const char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, const char *src);
int _putchar(char c);
void _puts(const char *str);
int _strlen(const char *s);
void _eputchar(char c);
char **get_environment(ShellInfo *info);
char *_getenv(ShellInfo *info, const char *name);

/*bferr*/
int bfree(void **ptr);
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
int hsh(ShellInfo *info, char **av);
int find_builtin(ShellInfo *info);
void find_cmd(ShellInfo *info);
void fork_cmd(ShellInfo *info);
int _memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int is_cmd(ShellInfo *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(ShellInfo *info, char *pathstr, char *cmd);
int bfree(void **ptr);
int main(int ac, char **av);
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);
#endif
