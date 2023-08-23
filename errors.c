#include "main.h"

char *_itoa(int n);
int create_error(char **args, int err);
int num_len(int n);
/**
 * num_len - Printts the length of a number
 * @n: Number to be measured
 *
 * Return: The length of number
 */
int num_len(int n)
{
	unsigned int n1;
	int l = 1;

	if (n < 0)
	{
		l++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		l++;
		n1 /= 10;
	}

	return (l);
}

/**
 * _itoa - Change an integer to a string
 * @n: An integer
 *
 * Return: Converted string
 */
char *_itoa(int n)
{
	char *buffer;
	int l = num_len(n);
	unsigned int n1;

	buffer = malloc(sizeof(char) * (l + 1));
	if (!buffer)
		return (NULL);

	buffer[l] = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	l--;
	do {
		buffer[l] = (n1 % 10) + '0';
		n1 /= 10;
		l--;
	} while (n1 > 0);

	return (buffer);
}


/**
 * create_error -Text an error message to stderr
 * @args: An array
 * @e: Value of error
 *
 * Return: Value of error
 */
int create_error(char **args, int e)
{
	char *error;

	switch (e)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (e);

}
