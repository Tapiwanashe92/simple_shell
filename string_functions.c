/*
 * File: str_funcs1.c
 *
 *
 */

#include "shell.h"

int str_len(const char *str);
char *str_cpy(char *dest, const char *src);
char *str_cat(char *dest, const char *src);
char *strn_cat(char *dest, const char *src, size_t n);

/**
 * str_len - Returns the length of a string.
 * @str: A pointer to the characters string.
 *
 * Return: The length of the character string.
 */
int str_len(const char *str)
{
	int len = 0;

	if (!str)
		return (len);
	for (len = 0; str[len]; len++)
		;
	return (len);
}

/**
 * str_cpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
 */
char *str_cpy(char *dest, const char *src)
{
	size_t j;

	for (j = 0; src[j] != '\0'; j++)
		dest[j] = src[j];
	dest[j] = '\0';
	return (dest);
}

/**
 * str_cat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *str_cat(char *dest, const char *src)
{
	char *dest_Temp;
	const char *src_Temp;

	dest_Temp = dest;
	src_Temp =  src;

	while (*dest_Temp != '\0')
		dest_Temp++;

	while (*src_Temp != '\0')
		*dest_Temp++ = *src_Temp++;
	*dest_Temp = '\0';
	return (dest);
}

/**
 * strn_cat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *strn_cat(char *dest, const char *src, size_t n)
{
	size_t dest_len = str_len(dest);
	size_t j;

	for (j = 0; j < n && src[j] != '\0'; j++)
		dest[dest_len + j] = src[j];
	dest[dest_len + j] = '\0';

	return (dest);
}
