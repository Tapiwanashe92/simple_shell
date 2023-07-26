/*
 * File: string_functions_two.c
 *
 */

#include "shell.h"

char *str_chr(char *str, char c);
int str_spn(char *str, char *accept);
int str_cmp(char *str1, char *str2);
int strn_cmp(const char *str1, const char *str2, size_t n);

/**
 * str_chr - Locates a character in a string.
 * @str: The string to be searched.
 * @c: The character to be located.
 *
 * Return: If c is found - a pointer to the first occurence.
 *         If c is not found - NULL.
 */
char *str_chr(char *str, char c)
{
	int arg;

	for (arg = 0; str[arg]; arg++)
	{
		if (str[arg] == c)
			return (str + arg);
	}

	return (NULL);
}

/**
 * str_spn - Gets the length of a prefix substring.
 * @str: The string to be searched.
 * @accept: The prefix to be measured.
 *
 * Return: The number of bytes in s which
 *         consist only of bytes from accept.
 */
int str_spn(char *str, char *accept)
{
	int i = 0;
	int j;

	while (*str)
	{
		for (j = 0; accept[j]; j++)
		{
			if (*str == accept[j])
			{
				i++;
				break;
			}
		}
		str++;
	}
	return (i);
}

/**
 * str_cmp - Compares two strings.
 * @str1: The first string to be compared.
 * @str2: The second string to be compared.
 *
 * Return: Positive byte difference if str1 > str2
 *         0 if str1 = str2
 *         Negative byte difference if str1 < str2
 */
int str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/**
 * strn_cmp - Compare two strings.
 * @str1: Pointer to a string.
 * @str2: Pointer to a string.
 * @n: The first n bytes of the strings to compare.
 *
 * Return: Less than 0 if str1 is shorter than str2.
 *         0 if str1 and str2 match.
 *         Greater than 0 if str1 is longer than str2.
 */
int strn_cmp(const char *str1, const char *str2, size_t n)
{
	size_t j;

	for (j = 0; str1[j] && str2[j] && j < n; j++)
	{
		if (str1[j] > str2[j])
			return (str1[j] - str2[j]);
		else if (str1[j] < str2[j])
			return (str1[j] - str2[j]);
	}
	if (j == n)
		return (0);
	else
		return (-15);
}
