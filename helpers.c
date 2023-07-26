#include "shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_length(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - Partitions a line read from standard input as needed.
 *@line: A double pointer to a line read from standard input.
 *@read: The line length.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */

void handle_line(char **line, ssize_t read)
{
	char *prev_line, *new_line;
	char prev, new, next;
	size_t j, k;
	ssize_t new_length;

	new_length = get_length(*line);
	if (new_length == read - 1)
		return;
	new_line = malloc(new_length + 1);
	if (!new_line)
		return;
	k = 0;
	prev_line = *line;
	for (j = 0; prev_line[j]; j++)
	{
		new = prev_line[j];
		next = prev_line[j + 1];
		if (j != 0)
		{
			prev = prev_line[j - 1];
			if (new == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					new_line[k++] = ' ';
					new_line[k++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					new_line[k++] = ';';
					new_line[k++] = ' ';
					continue;
				}
				if (prev != ' ')
					new_line[k++] = ' ';
				new_line[k++] = ';';
				if (next != ' ')
					new_line[k++] = ' ';
				continue;
			}
			else if (new == '&')
			{
				if (next == '&' && prev != ' ')
					new_line[k++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					new_line[k++] = '&';
					new_line[k++] = ' ';
					continue;
				}
			}
			else if (new == '|')
			{
				if (next == '|' && prev != ' ')
					new_line[k++]  = ' ';
				else if (prev == '|' && next != ' ')
				{
					new_line[k++] = '|';
					new_line[k++] = ' ';
					continue;
				}
			}
		}
		else if (new == ';')
		{
			if (j != 0 && prev_line[j - 1] != ' ')
				new_line[k++] = ' ';
			new_line[k++] = ';';
			if (next != ' ' && next != ';')
				new_line[k++] = ' ';
			continue;
		}
		new_line[k++] = prev_line[j];
	}
	new_line[k] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * get_length - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_length(char *line)
{
	size_t j;
	ssize_t new_length = 0;
	char now, new;

	for (j = 0; line[j]; j++)
	{
		now = line[j];
		new = line[j + 1];
		if (now == '#')
		{
			if (j == 0 || line[j - 1] == ' ')
			{
				line[j] = '\0';
				break;
			}
		}
		else if (j != 0)
		{
			if (now == ';')
			{
				if (new == ';' && line[j - 1] != ' ' && line[j - 1] != ';')
				{
					new_length += 2;
					continue;
				}
				else if (line[j - 1] == ';' && new != ' ')
				{
					new_length += 2;
					continue;
				}
				if (line[j - 1] != ' ')
					new_length++;
				if (new != ' ')
					new_length++;
			}
			else
				logical_ops(&line[j], &new_length);
		}
		else if (now == ';')
		{
			if (j != 0 && line[j - 1] != ' ')
				new_length++;
			if (new != ' ' && new != ';')
				new_length++;
		}
		new_length++;
	}
	return (new_length);
}
/**
 *logical_ops - Checks a line for logical operators "||" or "&&".
 *@line: A pointer to the character to check in the line.
 *@new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char prev, now, new;

	prev = *(line - 1);
	now = *line;
	new = *(line + 1);

	if (now == '&')
	{
		if (new == '&' && prev != ' ')
			(*new_len)++;
		else if (prev == '&' && new != ' ')
			(*new_len)++;
	}
	else if (now == '|')
	{
		if (new == '|' && prev != ' ')
			(*new_len)++;
		else if (prev == '|' && new != ' ')
			(*new_len)++;
	}
}
