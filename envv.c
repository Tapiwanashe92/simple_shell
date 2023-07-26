#include "shell.h"

int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_set_env(char **args, char __attribute__((__unused__)) **front);
int shell_unset_env(char **args, char __attribute__((__unused__)) **front);

/**
 * shell_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int shell_env(char **args, char __attribute__((__unused__)) **front)
{
	int index;
	char c = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], str_len(environ[index]));
		write(STDOUT_FILENO, &c, 1);
	}

	(void)args;
	return (0);
}

/**
 * shell_set_env - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_set_env(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_env, *new_val;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (write_error(args, -1));

	new_val = malloc(str_len(args[0]) + 1 + str_len(args[1]) + 1);
	if (!new_val)
		return (write_error(args, -1));
	str_cpy(new_val, args[0]);
	str_cat(new_val, "=");
	str_cat(new_val, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_val;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_val);
		return(write_error(args, -1));
	}

	for (index = 0; environ[index]; index++)
		new_env[index] = environ[index];

	free(environ);
	environ = new_env;
	environ[index] = new_val;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * shell_unset_env - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_unset_env(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_env;
	size_t size;
	int index, index2;

	if (!args[0])
		return (write_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (write_error(args, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_env[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_env;
	environ[size - 1] = NULL;

	return (0);
}
