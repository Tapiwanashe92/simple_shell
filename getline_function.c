/**
 * Main - entry point
 * Description - a program for a getline function
 *
 * @ptr: a pointer to the memory previously allocated
 * @old_size: the size in bytes of the allocated space ptr
 * @new_size: the size in bytes for the new memory block
 *
 * Return: if new_size == old_size - ptr
 * if new_size == 0 and ptr is not NULL - NULL
 * Otherwise - a pointer to the reallocated memory block
 */

#include "shell.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: a pointer to the memory previously allocated
 * @old_size: the size in bytes of the allocated space for ptr
 * @new_size: the size in bytes for the new memory block
 *
 * Return: if new_size == old_size - ptr
 * if new_size == 0 and ptr is not NULL - NULL
 * Otherwise - a pointer to the reallocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *mem;
	char *ptr_copy, *filler;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	mem = malloc(sizeof(*ptr_copy) * new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = mem;

	for (index = 0; index < old_size && index < new_size; index++)
		filler[index] = *ptr_copy++;

	free(ptr);
	return (mem);
}

/**
 * assign_lineptr - reassigns the lineptr variable for _getline
 * @lineptr: a buffer to store an input string
 * @n: the size of lineptr
 * @buffer: the string to assign to lineptr
 * @b: the size of buffer
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		str_cpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - reads input from a stream
 * @lineptr: a buffer to store the input
 * @n: the size of lineptr
 * @stream: the stream to read from
 *
 * Return: the number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_lineptr(lineptr, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
