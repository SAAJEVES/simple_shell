#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define END_OF_FLIE -2
#define EXIT -3

/* The Global Environment */
extern char **environ;

/* The Global program Name */
char *name;

/* The Global History Counter */
int hist;

/**
 * struct list_s -The struct defining a linked list.
 * @dir: The path of directory.
 * @next: The pointer point to struct list_s.
 */

typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - The struct defining builtin commands.
 * @name: The name for builtin command.
 * @f: THE function pointer point to builtin command's function.
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/*The main helpers*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int execute(char **args, char **front);
char *_itoa(int num);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
void free_list(list_t *head);
list_t *get_path_dir(char *path);

/*The input helpers*/
int check_args(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);
void handle_line(char **line, ssize_t read);
void variable_replacement(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);

/*The builtin functions*/
int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/* The builtin helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/*Error Handling*/
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
int create_error(char **args, int err);
char *error_env(char **args);

/* Th void helpers */
void help_exit(void);
void help_help(void);
void help_env(void);
void help_all(void);
void help_alias(void);
void help_cd(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/*The Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);
void free_alias_list(alias_t *head);

/*Function of  String */
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);

int proc_file_commands(char *file_path, int *exe_ret);
#endif /* SHELL_H */
