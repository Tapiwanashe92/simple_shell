#include "shell.h"

int tok_length(char *str, char *delim);
int token_count(char *str, char *delim);
char **string_tok(char *line, char *delim);

/**
* tok_length - Locates the delimiter index marking the end
*             of the first token contained within a string.
* @str: The string to be searched.
* @delim: The delimiter character.
*
* Return: The delimiter index marking the end of
*         the intitial token pointed to be str.
*/
int tok_length(char *str, char *delim)
{
	int index = 0, length = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		length++;
		index++;
	}

	return (length);
}

/**
 * token_count - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int token_count(char *str, char *delim)
{
	int index;
	int tokens = 0;
	int length = 0;

	for (index = 0; *(str + index); index++)
		length++;

	for (index = 0; index < length; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += tok_length(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * string_tok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **string_tok(char *line, char *delim)
{
	char **pointer;
	int index = 0;
	int tokens;
	int z, letters, p;

	tokens = token_count(line, delim);
	if (tokens == 0)
		return (NULL);

	pointer = malloc(sizeof(char *) * (tokens + 2));
	if (!pointer)
		return (NULL);

	for (z = 0; z < tokens; z++)
	{
		while (line[index] == *delim)
			index++;

		letters = tok_length(line + index, delim);

		pointer[z] = malloc(sizeof(char) * (letters + 1));
		if (!pointer[z])
		{
			for (index -= 1; index >= 0; index--)
				free(pointer[index]);
			free(pointer);
			return (NULL);
		}

		for (p = 0; p < letters; p++)
		{
			pointer[z][p] = line[index];
			index++;
		}

		pointer[z][p] = '\0';
	}
	pointer[z] = NULL;
	pointer[z + 1] = NULL;

	return (pointer);
}
