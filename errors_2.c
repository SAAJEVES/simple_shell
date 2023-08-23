#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);
/**
 * error_126 - Make error message for denied permission failures
 * @a: Argument
 * Return: The error
 */
char *error_126(char **a)
{
	char *error, *hist_str;
	int l;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	l = _strlen(name) + _strlen(hist_str) + _strlen(a[0]) + 24;
	error = malloc(sizeof(char) * (l + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, a[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, ": ");
	_strcat(error, hist_str);

	free(hist_str);
	return (error);
}

/**
 * error_127 - Make error message
 * @a: Array of arguments
 *
 * Return: The error
 */
char *error_127(char **a)
{
	char *error, *hist_str;
	int l;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	l = _strlen(name) + _strlen(hist_str) + _strlen(a[0]) + 16;
	error = malloc(sizeof(char) * (l + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcpy(error, name);
	_strcat(error, a[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}
