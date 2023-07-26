/*
 * File: helper.c
 */

#include "shell.h"

void free_arg(char **args, char **front);
char *get_pid(void);
char *env_value(char *beginning, int len);
void var_replacement(char **args, int *exe_ret);

/**
 * free_arg - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void free_arg(char **args, char **front)
{
	size_t j;

	for (j = 0; args[j] || args[j + 1]; j++)
		free(args[j]);

	free(front);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID
 *	OR NULL on failure.
 */
char *get_pid(void)
{
	size_t j = 0;
	char *buff;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(file);
		return (NULL);
	}
	read(file, buff, 120);
	while (buff[j] != ' ')
		j++;
	buff[j] = '\0';

	close(file);
	return (buff);
}

/**
 * env_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *env_value(char *beginning, int len)
{
	char **address;
	char *replace = NULL, *t, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	strn_cat(var, beginning, len);

	address = _getenv(var);
	free(var);
	if (address)
	{
		t = *address;
		while (*t != '=')
			t++;
		t++;
		replace = malloc(str_len(t) + 1);
		if (replace)
			str_cpy(replace, t);
	}

	return (replace);
}

/**
 * var_replacement -Deals with variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void var_replacement(char **line, int *exe_ret)
{
	int i, j = 0, len;
	char *replace = NULL, *prev_line = NULL, *new_line;

	prev_line = *line;
	for (i = 0; prev_line[i]; i++)
	{
		if (prev_line[i] == '$' && prev_line[i + 1] &&
				prev_line[i + 1] != ' ')
		{
			if (prev_line[j + 1] == '$')
			{
				replace = get_pid();
				j = i + 2;
			}
			else if (prev_line[i + 1] == '?')
			{
				replace = int_to_str(*exe_ret);
				j = i + 2;
			}
			else if (prev_line[i + 1])
			{
				/* extract the variable name to search for */
				for (j = i + 1; prev_line[j] &&
						prev_line[j] != '$' &&
						prev_line[j] != ' '; j++)
					;
				len = j - (i + 1);
				replace = env_value(&prev_line[i + 1], len);
			}
			new_line = malloc(j + str_len(replace)
					  + str_len(&prev_line[j]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			strn_cat(new_line, prev_line, i);
			if (replace)
			{
				str_cat(new_line, replace);
				free(replace);
				replace = NULL;
			}
			str_cat(new_line, &prev_line[j]);
			free(prev_line);
			*line = new_line;
			prev_line = new_line;
			i = -1;
		}
	}
}
