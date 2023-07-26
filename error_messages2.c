#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - creates and error message for permission denied failures
 * @args: an array of arguments passed to command
 *
 * Return: the error string
 */
char *error_126(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = int_to_str(hist);
	if (!hist_str)
		return (NULL);

	len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, hist_str);
	str_cat(error, ": ");
	str_cat(error, args[0]);
	str_cat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_127 - creates an error message for command not found failure
 * @args: an array of arguments passed to command
 *
 * Return: the error string
 */
char *error_127(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = int_to_str(hist);
	if (!hist_str)
		return (NULL);

	len = str_len(name) + str_len(hist_str) + str_len(args[0] + 16);
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, hist_str);
	str_cat(error, ": ");
	str_cat(error, args[0]);
	str_cat(error, ": not found\n");

	free(hist_str);
	return (error);
}
