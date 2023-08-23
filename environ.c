#include "main.h"

void free_env(void);
char **_getenv(const char *var);
char **_copyenv(void);
/**
 * _copyenv - Makethe environment for copy.
 *
 * Return: NULL || a double pointer
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t s;
	int i;

	for (s = 0; environ[s]; s++)
		;

	new_environ = malloc(sizeof(char *) * (s + 1));
	if (!new_environ)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = malloc(_strlen(environ[i]) + 1);

		if (!new_environ[i])
		{
			for (i--; i >= 0; i--)
				free(new_environ[i]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[i], environ[i]);
	}
	new_environ[i] = NULL;

	return (new_environ);
}

/**
 * free_env - Make the the environment free copy
 */
void free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * _getenv - Finde environmental variable from the PATH
 * @v: The mass environmental variable nedede
 *
 * Return: If no environmental variable - NULL or - a pointer
 */
char **_getenv(const char *v)
{
	int i, l;

	l = _strlen(v);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(v, environ[i], l) == 0)
			return (&environ[i]);
	}

	return (NULL);
}
