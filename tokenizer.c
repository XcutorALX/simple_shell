#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <string.h>

/**
 * _strtok - looks for a delim in a string
 *
 * @str: the string to parse, if str is NULL it continues from the
 * point of stoppage in the previous string
 * @delim: the delimiter to look out for
 *
 * Return: returns a pointer to the string found
 */

char *_strtok(char *str, char *delim)
{
	static int position, count;
	static char *strPtr;
	size_t start, i;

	if (str)
	{
		strPtr = str;
		for (count = 0, position = 0; strPtr[count] != '\0'; count++)
		{
			for (i = 0; delim[i] != '\0'; i++)
			{
				if (strPtr[count] == delim[i])
				{
					strPtr[count] = '\0';
					break;
				}
			}
		}
		count++;
	}
	start = position;
	for (; position <= count; position++)
	{
		if (position == count)
		{
			position++;
			return (&strPtr[start]);
		}
		if (position != 0)
		{
			if (strPtr[position - 1] != '\0' && strPtr[position] == '\0')
			{
				position++;
				return (&strPtr[start]);
			}
			else if (strPtr[position - 1] == '\0' && strPtr[position] != '\0')
				start = position;
		}
	}
	return (NULL);
}


/**
 * tokenize - a function that splits a string
 * into an array of string according to a delim provided
 *
 *@str: the string to be parsed
 *@delim: the delimeter to look out for
 *
 *Return: returns an array of strings
 */

char **tokenize(char *str, char *delim)
{
	size_t count, size;
	char **split, *buffer;

	size = 1024;
	split = malloc(size * sizeof(char *));
	if (!split)
		exit(EXIT_FAILURE);
	split[0] = _strtok(str, delim);
	if (!_strtok(str, delim))
		return (NULL);
	for (count = 1; (buffer = _strtok(NULL, delim)) != NULL
			&& *buffer != '\0'; count++)
	{
		if (count == size - 1)
		{
			size *= 1.5;
			split = realloc(split, size * sizeof(char *));
			if (!split)
				exit(EXIT_FAILURE);
		}
		split[count] = buffer;
	}
	split[count++] = NULL;
	split = _realloc(split, size * sizeof(char *),
		(count + 1) * sizeof(char *), sizeof(char *));
	size = count + 1;
	if (!split)
		exit(EXIT_FAILURE);
	return (split);
}
