#include "shell.h"

int shellby_exit(char **args, char **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int (*get_builtin(char *command))(char **args, char **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - Relates command with shellby builtin function
 * @c: The command
 *
 * Return: A function pointer that realates builtin
 */
int (*get_builtin(char *c))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "unsetenv", shellby_unsetenv },
		{ "cd", shellby_cd },
		{ "alias", shellby_alias },
		{ "help", shellby_help },
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "setenv", shellby_setenv },
		{ NULL, NULL }
	};
	int a;

	for (a = 0; funcs[a].name; a++)
	{
		if (_strcmp(funcs[a].name, c) == 0)
			break;
	}
	return (funcs[a].f);
}

/**
 * shellby_exit - Makes process terminatio for shellby shell
 * @a: An array of arguments
 * @f: A double pointer
 *
 * Return: If no arguments - -3
 *         If the no valid exit value - 2 Or - exits the given value
 */
int shellby_exit(char **a, char **f)
{
	int b, len_of_int = 10;
	unsigned int n = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (a[0])
	{
		if (a[0][0] == '+')
		{
			b = 1;
			len_of_int++;
		}
		for (; a[0][b]; b++)
		{
			if (b <= len_of_int && a[0][b] >= '0' && a[0][b] <= '9')
				n = (n * 10) + (a[0][b] - '0');
			else
				return (create_error(--a, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (n > max - 1)
		return (create_error(--a, 2));
	a -= 1;
	free_args(a, f);
	free_env();
	free_alias_list(aliases);
	exit(n);
}

/**
 * shellby_cd - Changes the current directory of the shellby process
 * @args: An array of arguments
 * @front: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2
 *         If an error occurs - -1
 *         Otherwise - 0
 */
int shellby_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * shellby_help - Out put information about shellby builtin.
 * @a: An array.
 * @f: A pointer.
 *
 * Return: If their is error - -1. or - 0.
 */
int shellby_help(char **a, char __attribute__((__unused__)) **f)
{
	if (!a[0])
		help_all();
	else if (_strcmp(a[0], "alias") == 0)
		help_alias();
	else if (_strcmp(a[0], "cd") == 0)
		help_cd();
	else if (_strcmp(a[0], "exit") == 0)
		help_exit();
	else if (_strcmp(a[0], "env") == 0)
		help_env();
	else if (_strcmp(a[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(a[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(a[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
