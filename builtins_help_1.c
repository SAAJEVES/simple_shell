#include "main.h"

void help_cd(void);
void help_exit(void);
void help_help(void);
void help_all(void);
void help_alias(void);
/**
 * help_all - Prints builtin shellby commands
 */

void help_all(void)
{
	char *m = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, m, _strlen(m));
	m = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, m, _strlen(m));
}
/**
 * help_alias - Prints info. shellby builtin command 'alias'
 */

void help_alias(void)
{
	char *m = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, m, _strlen(m));
	m = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, m, _strlen(m));
	m = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, m, _strlen(m));
	m = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, m, _strlen(m));
}
/**
 * help_cd - Prints info. on the shellby builtin command 'cd'
 */

void help_cd(void)
{
	char *m = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, m, _strlen(m));
	m = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, m, _strlen(m));
	m = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "after a change of directory.\n";
	write(STDOUT_FILENO, m, _strlen(m));
}
/**
 * help_exit - Prints info. on the shellby builtin command 'exit'
 */

void help_exit(void)
{
	char *m = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, m, _strlen(m));
	m = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, m, _strlen(m));
	m = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, m, _strlen(m));
	m = " exit 0.\n";
	write(STDOUT_FILENO, m, _strlen(m));
}
/**
 * help_help - Prints info. on the shellby builtin command 'help'
 */

void help_help(void)
{
	char *m = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, m, _strlen(m));
	m = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, m, _strlen(m));
	m = "builtin command.\n";
	write(STDOUT_FILENO, m, _strlen(m));
}
