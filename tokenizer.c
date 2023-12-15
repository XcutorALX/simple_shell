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
	static int position;
	static char *strPtr;
	static int count;
	size_t start, i;

	if (str)
	{
		strPtr = str;
		position = 0;
		count = 0;
		for (; strPtr[count] != '\0'; count++)
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
	if (position == count)
		return (NULL);
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
	char **split;
	char *buffer;

	size = 1024;
	split = malloc(size * sizeof(char *));
	if (!split)
	{
		perror("Memory reallocation error third");
		exit(EXIT_FAILURE);
	}
	buffer = _strtok(str, delim);
	split[0] = buffer;
	if (!buffer)
	{
		return (NULL);
	}
	for (count = 1; (buffer = _strtok(NULL, delim)) != NULL && *buffer != '\0'; count++)
	{
		if (count == size - 1)
		{
			size *= 1.5;
			split = realloc(split, size * sizeof(char *));
			if (!split)
			{
				perror("Memory reallocation error second");
				exit(EXIT_FAILURE);
			}
		}
		split[count] = buffer;
	}

	split[count++] = NULL;
	split = _realloc(split, size * sizeof(char *), (count + 1) * sizeof(char *), sizeof(char *));
	size = count + 1;
	if (!split)
	{
		perror("Memory reallocation error third");
		exit(EXIT_FAILURE);
	}
	return (split);
}
