#include "shell.h"

char *get_pid(void);
char *get_env_value(char *beg, int l);
void free_args(char **a, char **f);
void variable_replacement(char **args, int *exe_ret);
/**
 * free_args - cleare up and taken by a
 * @a: Null-terminated double pointer containing arguments
 * @front: A pointer to start a
 */
void free_args(char **a, char **f)
{
	size_t i;

	for (i = 0; a[i] || a[i + 1]; i++)
		free(a[i]);

	free(front);
}

/**
 * get_pid - Find PPID
 * Description: Information about the current process
 *
 * Return: The PPID or NULL
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t f;

	f = open("/proc/self/stat", O_RDONLY);
	if (f == -1)
	{
		perror("Cant read f");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(f);
		return (NULL);
	}
	read(f, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(f);
	return (buffer);
}

/**
 * get_env_value - Find value to an environmental variable
 * @beg: To search for environmental variable
 * @l: Length of the environmental variable
 *
 * Return: If not found - empty string Or - the environmental variable
 */
char *get_env_value(char *beg, int l)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(l + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beg, l);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - Reples variable
 * @l: A pointer include command and arguments
 * @exe_ret: A pointer to last executed command
 */
void variable_replacement(char **l, int *exe_ret)
{
	int b, c = 0, a;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *l;
	for (b = 0; old_line[b]; b++)
	{
		if (old_line[b] == '$' && old_line[b + 1] &&
				old_line[b + 1] != ' ')
		{
			if (old_line[b + 1] == '$')
			{
				replacement = get_pid();
				c = b + 2;
			}
			else if (old_line[b + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				c = b + 2;
			}
			else if (old_line[b + 1])
			{
				/* extract the variable name to search for */
				for (c = b + 1; old_line[c] &&
						old_line[c] != '$' &&
						old_line[c] != ' '; c++)
					;
				a = c - (b + 1);
				replacement = get_env_value(&old_line[b + 1], a);
			}
			new_line = malloc(b + _strlen(replacement)
					  + _strlen(&old_line[c]) + 1);
			if (!l)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, b);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[c]);
			free(old_line);
			*l = new_line;
			old_line = new_line;
			b = -1;
		}
	}
}
