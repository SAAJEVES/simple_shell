#include "main.h"

void help_unsetenv(void);
void help_env(void);
void help_setenv(void);
void help_history(void);
/**
 * help_env - Outputs shellby builtin command 'env' information
 */

void help_env(void)
{
	char *m = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, m, _strlen(m));
}
/**
 * help_setenv - Outputs the shellby builtin command 'setenv' information
 */

void help_setenv(void)
{
	char *m = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, m, _strlen(m));
	m = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, m, _strlen(m));
}
/**
 * help_unsetenv - Outputs the shellby builtin command 'unsetenv' info.
 */

void help_unsetenv(void)
{
	char *m = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, m, _strlen(m));
	m = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "message to stderr.\n";
	write(STDOUT_FILENO, m, _strlen(m));
}
