#include "main.h"

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
/**
 * _realloc - Reallocates a memory
 * @p: A pointer previously allocated
 * @old_size: The mass of allocated space for p
 * @new_size: The mass for the new memory block
 *
 * Return: If new_size == old_size - p
 *         If new_size == 0 and p is not NULL - NULL
 *         Otherwise - a pointer to the reallocated memory block
 */
void *_realloc(void *p, unsigned int old_size, unsigned int new_size)
{
	void *m;
	char *ptr_copy, *filler;
	unsigned int i;

	if (new_size == old_size)
		return (p);

	if (p == NULL)
	{
		m = malloc(new_size);
		if (m == NULL)
			return (NULL);

		return (m);
	}

	if (new_size == 0 && p != NULL)
	{
		free(p);
		return (NULL);
	}

	ptr_copy = p;
	m = malloc(sizeof(*ptr_copy) * new_size);
	if (m == NULL)
	{
		free(p);
		return (NULL);
	}

	filler = m;

	for (i = 0; i < old_size && i < new_size; i++)
		filler[i] = *ptr_copy++;

	free(p);
	return (m);
}
/**
 * assign_lineptr - Re name the lineptr for _getline variable
 * @lin: Store an input string
 * @a: The size of lineptr
 * @buffer: The string to assign to lineptr
 * @b: Size of buffer
 */
void assign_lineptr(char **lin, size_t *a, char *buffer, size_t b)
{
	if (*lin == NULL)
	{
		if (b > 120)
			*a = b;
		else
			*a = 120;
		*lin = buffer;
	}
	else if (*a < b)
	{
		if (b > 120)
			*a = b;
		else
			*a = 120;
		*lin = buffer;
	}
	else
	{
		_strcpy(*lin, buffer);
		free(buffer);
	}
}
/**
 * _getline - Input from a stream
 * @lin: Store the input
 * @a: Size of lineptr
 * @stream: read from
 *
 * Return: The mass of bytes read
 */
ssize_t _getline(char **lin, size_t *a, FILE *stream)
{
	static ssize_t i;
	ssize_t r;
	char c = 'x', *buffer;
	int b;

	if (i == 0)
		fflush(stream);
	else
		return (-1);
	i = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		b = read(STDIN_FILENO, &c, 1);
		if (b == -1 || (b == 0 && i == 0))
		{
			free(buffer);
			return (-1);
		}
		if (b == 0 && i != 0)
		{
			i++;
			break;
		}

		if (i >= 120)
			buffer = _realloc(buffer, i, i + 1);

		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';

	assign_lineptr(lin, a, buffer, i);

	r = i;
	if (b != 0)
		i = 0;
	return (r);
}
