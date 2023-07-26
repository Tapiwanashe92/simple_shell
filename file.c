#include "shell.h"
#include <stdlib.h>
#include <stddef.h>

int cant_open(char *file_path);
int file_commands(char *file_path, int *exe_ret);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error, *past_str;
	int length;

	past_str = int_to_str(hist);
	if (!past_str)
		return (127);

	length = str_len(name) + str_len(past_str) + str_len(file_path) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(past_str);
		return (127);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, past_str);
	str_cat(error, ": Can't open ");
	str_cat(error, file_path);
	str_cat(error, "\n");

	free(past_str);
	write(STDERR_FILENO, error, length);
	free(error);
	return (127);
}

/**
 * file_commands - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int file_commands(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, j;
	unsigned int line_size = 0;
	unsigned int prev_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * prev_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, prev_size, line_size);
		str_cat(line, buffer);
		prev_size = line_size;
	} while (b_read);
	for (j = 0; line[j] == '\n'; j++)
		line[j] = ' ';
	for (; j < line_size; j++)
	{
		if (line[j] == '\n')
		{
			line[j] = ';';
			for (j += 1; j < line_size && line[j] == '\n'; j++)
				line[j] = ' ';
		}
	}
	var_replacement(&line, exe_ret);
	handle_line(&line, line_size);
	args = str_tok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_arg(args, args);
		return (*exe_ret);
	}
	front = args;

	for (j = 0; args[j]; j++)
	{
		if (strn_cmp(args[j], ";", 1) == 0)
		{
			free(args[j]);
			args[j] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++j];
			j = 0;
		}
	}

	ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}
