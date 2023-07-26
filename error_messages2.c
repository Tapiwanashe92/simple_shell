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

	hist_str = itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

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

	hist_str = itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0] + 16);
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}