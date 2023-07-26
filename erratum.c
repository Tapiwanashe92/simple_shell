#include "shell.h"

int num_length(int num);
char *int_to_str(int num);
int write_error(char **args, int err);

/**
 * num_length - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_length(int num)
{
	unsigned int num_one;
	int length = 1;

	if (num < 0)
	{
		length++;
		num_one = num * -1;
	}
	else
	{
		num_one = num;
	}
	while (num_one > 9)
	{
		length++;
		num_one /= 10;
	}

	return (length);
}

/**
 * int_to_str - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *int_to_str(int num)
{
	char *buff;
	int length = num_length(num);
	unsigned int num_one;

	buff = malloc(sizeof(char) * (length + 1));
	if (!buff)
		return (NULL);

	buff[length] = '\0';

	if (num < 0)
	{
		num_one = num * -1;
		buff[0] = '-';
	}
	else
	{
		num_one = num;
	}

	length--;
	do {
		buff[length] = (num_one % 10) + '0';
		num_one /= 10;
		length--;
	} while (num_one > 0);

	return (buff);
}


/**
 * write_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int write_error(char **args, int err)
{
	char *error;

	switch (err)
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
	write(STDERR_FILENO, error, str_len(error));

	if (error)
		free(error);
	return (err);

}
