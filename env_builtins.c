#include "main.h"

int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_env(char **args, char __attribute__((__unused__)) **front);
/**
 * shellby_env - Displays the current environment
 * @args: An array passed to the shell
 * @front: Pointer to the beginning of args
 *
 * Return: returns 0 || -1
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int i;
	char n = '\n';

	if (!environ)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &n, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - Convert or increas variable to the PATH
 * @args: Arguments passed to the shell
 * @front: Pointer to the beginning of args
 * Description: a[1] is the name of the new or existing PATH variable
 *              a[2] is the value to set the new or changed variable to
 *
 * Return: 0 || -1
 */
int shellby_setenv(char **a, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int i;

	if (!a[0] || !a[1])
		return (create_error(a, -1));

	new_value = malloc(_strlen(a[0]) + 1 + _strlen(a[1]) + 1);
	if (!new_value)
		return (create_error(a, -1));
	_strcpy(new_value, a[0]);
	_strcat(new_value, "=");
	_strcat(new_value, a[1]);

	env_var = _getenv(a[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(a, -1));
	}

	for (i = 0; environ[i]; i++)
		new_environ[i] = environ[i];

	free(environ);
	environ = new_environ;
	environ[i] = new_value;
	environ[i + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - Remove environmental variable from the PATH
 * @a: Arguments passed to the shell
 * @f: Pointer to the beginning of args
 *
 * Return: returns 0 || -1
 */
int shellby_unsetenv(char **a, char __attribute__((__unused__)) **f)
{
	char **env_var, **new_environ;
	size_t size;
	int i, i2;

	if (!a[0])
		return (create_error(a, -1));
	env_var = _getenv(a[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(a, -1));

	for (i = 0, i2 = 0; environ[i]; i++)
	{
		if (*env_var == environ[i])
		{
			free(*env_var);
			continue;
		}
		new_environ[i2] = environ[i];
		i2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
