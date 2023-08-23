#include "shell.h"

void set_alias(char *var_name, char *value);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void print_alias(alias_t *alias);

/**
 * shellby_alias - Make command that prints aliases, specific aliases, or alias
 * @a: An array of arguments
 * @f: A double pointer to the beginning of args
 *
 * Return: If their is error - -1 or - 0
 */
int shellby_alias(char **a, char __attribute__((__unused__)) **f)
{
	alias_t *temp = aliases;
	int b, r = 0;
	char *value;

	if (!a[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (r);
	}
	for (b = 0; a[b]; b++)
	{
		temp = aliases;
		value = _strchr(a[b], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(a[b], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				r = create_error(a + b, 1);
		}
		else
			set_alias(a[b], value);
	}
	return (r);
}

/**
 * set_alias - Either set an existing alias or make new
 * @var_name: Mass of the alias
 * @value: The alias.The first is a '='
 */
void set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int l, b, c;
	char *new_value;

	*value = '\0';
	value++;
	l = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (l + 1));
	if (!new_value)
		return;
	for (b = 0, c = 0; value[b]; b++)
	{
		if (value[b] != '\'' && value[b] != '"')
			new_value[c++] = value[b];
	}
	new_value[c] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - Prints the alias
 * @alias: Pointer to an alias
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int l = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (l + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, l);
	free(alias_string);
}

/**
 * replace_aliases - Replace any matching alias with their value
 * @a: 2D pointer
 *
 * Return: 2D pointer
 */
char **replace_aliases(char **a)
{
	alias_t *temp;
	int b;
	char *new_value;

	if (_strcmp(a[0], "alias") == 0)
		return (a);
	for (b = 0; a[b]; b++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(a[b], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_value)
				{
					free_args(a, a);
					return (NULL);
				}
				_strcpy(new_value, temp->value);
				free(a[b]);
				a[b] = new_value;
				b--;
				break;
			}
			temp = temp->next;
		}
	}

	return (a);
}
