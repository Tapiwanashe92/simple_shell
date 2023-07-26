#include "shell.h"

char *fill_path_dir(char *path);
list_t *path_dir(char *path);

/**
 *path_location - locates a command in the path
 * @command: The command to locate
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *	Otherwise - the full pathname of the command
 */

char *path_location(char *command)
{
	char **path, *t;
	list_t *dirs, *head;
	struct stat file;

	path = _getenv("PATH");

	if (!path || !(*path))
		return (NULL);

	dirs = path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		t = malloc(str_len(dirs->dir) + str_len(command) + 2);
		if (!t)
			return (NULL);

		str_cpy(t, dirs->dir);
		str_cat(t, "/");
		str_cat(t, command);

		if (stat(t, &file) == 0)
		{
			free_list(head);
			return (t);
		}
		dirs = dirs->next;
		free(t);
	}
	free_list(head);
	return (NULL);
}

/**
 * fill_path_dir - copies path but also replaces leading/sandwiched/trailing
 *		 colons (:) with current working directory.
 * @path: The colon-seperated list of directories
 *
 * Return: A copy of path any leading/sandwiched/trailing
 *         colons replaced with the current working directory.
 *
*/

char *fill_path_dir(char *path)
{
	int j, len = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (j = 0; path[j]; j++)
	{
		if (path[j] == ':')
		{
			if (path[j + 1] == ':' || j == 0 || path[j + 1] == '\0')
				len += str_len(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	path_copy = malloc(sizeof(char) * (len + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (j = 0; path[j]; j++)
	{
		if (path[j] == ':')
		{
			if (j == 0)
			{
				str_cat(path_copy, pwd);
				str_cat(path_copy, ":");
			}
			else if (path[j + 1] == ':' || path[j + 1] == '\0')
			{
				str_cat(path_copy, ":");
				str_cat(path_copy, pwd);
			}
			else
				str_cat(path_copy, ":");
		}
		else
		{
			strn_cat(path_copy, &path[j], 1);
		}
	}
	return (path_copy);
}

/**
*path_dir - tokenizes a colon seperated list of
*	directoris into a list_s linked list
*@path: The colon seperated list of directories.
*
*Return: A pointer to the initialized linkd list.
*/

list_t *path_dir(char *path)
{
	int index;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = str_tok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}
	free(dirs);
	return (head);
}
