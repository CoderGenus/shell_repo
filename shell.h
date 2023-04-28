#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>

/* read/write buffers */
#define READ_BUFFER	1024
#define WRITE_BUFFER	1024
#define FLUSH_BUFFER	-1

/*commands chaining */
#define NORMAL_CMD	0
#define OR_CMD		1
#define AND_CMD		2
#define CHAIN_CMD	3

/*convert number */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED		2

/* system getline */
#define GETLINE		0
#define STRTOK		0
#define FILE_HISTORY	".simple_shell_history"
#define MAX_HISTORY	4095

extern char **environ;

/**
 * struct list_s - singly linked list
 * @index: the num field
 * @str: string
 * @next: points to the next node
 */
typedef struct list_s
{
	int index;
	char *str;
	struct list_s *next;
} list_t;

/**
 * struct passfunc - contains arguments to pass into a function,
 * allowing a uniform prototype for function pointer struct
 * @arg: string generated from getline containing argument
 * @argv: array of string generated from argument
 * @path: the path of the current command
 * @argc: the argument
 * @err_count: the error count
 * @err_index: the error code for exit's
 * @line_count_flag: counts line of input
 * @filename: the program's filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ
 * @history: the history mode
 * @alias: the alias mode
 * @environ_changed: On if environ was changed
 * @status: return status of the last executed command
 * @cmd_buffer: address of pointer to command buffer
 * @cmd_buffer_type: cmd_type ||, &&,;
 * @readfd: the file descriptor which reads the line input
 * @hist_count: the history line number count
 */
typedef struct passfunc
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int err_count;
	int err_index;
	int line_count_flag;
	char *filename;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int environ_changed;
	int status;
	char **cmd_buffer;
	int cmd_buffer_type;
	int readfd;
	int hist_count;
} note_t;

#define FUNC_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains a builtin string
 * @flag: builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *flag;
	int (*func)(note_t *);
} builtin_t;

/* shell_loop.c */
int hsh(note_t *, char **);
int search_builtin(note_t *);
void search_cmd(note_t *);
void fork_cmd(note_t *);
int loophsh(char **);

/* shell_parser.c */
int is_cmd(note_t *, char *);
char *chars_cp(char *, int, int);
char *search_path(note_t *, char *, char *);

/* shell_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* shell_errors1.c */
int _erratoi(char *);
void print_error(note_t *, char *);

/* shell_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *is_prefix(const char *, const char *);
char *_strcat(char *, char *);

/* shell_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
int print_dec(int, int);

/*shell_string2.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
int is_delim(char, char *);
int _isalpha(int);

/* shell_tokenizer */
char **split_string(char *, char *);
char **split_string2(char *, char);

/*shell_memory.c */
char *_memset(char *, char, unsigned int);
void free_str(char **);
void *_realloc(void *, unsigned int, unsigned int);
int free_ptr(void **);

/* shell_utils.c */
int is_interactive(note_t *);
char *conv_num(long int, int, int, int);
void del_comments(char *);
int _myatoi(char *);

/* shell_builtin.c */
int _myexit(note_t *);
int _mycd(note_t *);
int _myhelp(note_t *);
int _myhistory(note_t *);

/* shell_alias */
int remove_alias(note_t *, char *);
int set_alias(note_t *, char *);
int print_alias(note_t *);
int _myalias(note_t *);

/* shell_getline */
ssize_t read_input(note_t *);
int _getline(note_t *, char **, size_t *);
void sigint_handler(int);

/* shell_getnote */
void clear_note(note_t *);
void set_note(note_t *, int);
void free_note(note_t *, int);

/* shell_environ */
char *_getenv(note_t *, const char *);
int _myenv(note_t *);
int _mysetenv(note_t *);
int _myunsetenv(note_t *);
int build_env_list(note_t *);

/* shell environ1.c */
char **get_environ(note_t *);
int _unsetenv(note_t *, char *);
int _setenv(note_t *, char *, char *);

/*shell_history */
char *ret_hist_file(note_t *);
int rec_history(note_t *);
int rd_hist(note_t *);
int append_hist_list(note_t *, char *, int);
int reindex_history(note_t *);

/* shell_list */
list_t *add_node(list_t **, const char *, int);
list_t *append_node(list_t **, const char *, int);
size_t display_list_str(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/*shell_list1.c */
size_t count_list(const list_t *);
char **list_to_str(list_t *);
size_t print_list(const list_t *);
list_t *node_prefix(list_t *, char *, char);
ssize_t get_node_position(list_t *, list_t *);

/* shell_variables.c */
int is_chain(note_t *, char *, size_t *);
void check_chain(note_t *, char *, size_t *, size_t, size_t);
int resolve_alias(note_t *);
int resolve_vars(note_t *);
int resolve_string(char **, char *);

#endif
