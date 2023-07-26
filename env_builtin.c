#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - creates a copy of the environment
 *
 * Return: if an error occurs - NULL
 * O/w - a double pointer to the new copy
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(str_len(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		str_cpy(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * free_env - frees the environment copy
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _getenv - gets an environmental variable from the PATH
 * @var: the name of the environmental variable to get
 *
 * Return: if the environmental variable does not exist - NULL.
 * Otherwise - a pointer to the environmental variable
 */
char **_getenv(const char *var)
{
	int index, len;

	len = str_len(var);
	for (index = 0; environ[index]; index++)
	{
		if (strn_cmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}
	return (NULL);
}
