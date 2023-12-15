#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * getLine - this function reads and saves the specified length
 * of characters in the provided pointer location
 *
 *@lineptr: an array of string
 *@bufferSize: the length of characters to read
 *@fd: the file to descriptor of the file to read from
 *
 * Return: returns -1 on failure to read a line or EOF else it returns
 * the number of characters read
 */

int getLine(char **lineptr, size_t *bufferSize, int fd)
{
	size_t i = 0;
	int c;

	if (!(*lineptr))
	{
		*bufferSize = 1024;
		*lineptr = malloc(*bufferSize * sizeof(char));

		if (!(*lineptr))
		{
			perror("Memory reallocation error");
			exit(EXIT_FAILURE);
		}
	}
	while ((c = my_fgetc(fd)) != EOF && c != '\n')
	{
		if (i == *bufferSize - 1)
		{
			*lineptr = _realloc(*lineptr, *bufferSize * sizeof(char),
					*bufferSize * sizeof(char) * 1.5, sizeof(char));
			*bufferSize *= 1.5;
			if (!(*lineptr))
			{
				perror("Memory reallocation error");
				exit(EXIT_FAILURE);
			}
		}
		(*lineptr)[i] = c;
		i++;
	}

	if (i == 0 && c == EOF)
	{
		return (-1);
	}
	*bufferSize = i + 3;
	*lineptr = realloc(*lineptr, *bufferSize * sizeof(char));
	(*lineptr)[i] = '\0';
	return (i);
}

int getPipe(char **lineptr, size_t *bufferSize, int fd)
{
	size_t i = 0;
	int c;

	if (!(*lineptr))
	{
		*bufferSize = 1024;
		*lineptr = malloc(*bufferSize * sizeof(char));

		if (!(*lineptr))
		{
			perror("Memory reallocation error");
			exit(EXIT_FAILURE);
		}
	}
	while ((c = my_fgetc(fd)) != EOF)
	{
		if (i == *bufferSize - 1)
		{
			*lineptr = _realloc(*lineptr, *bufferSize * sizeof(char),
					*bufferSize * 1.5 * sizeof(char), sizeof(char));
			*bufferSize *= 1.5;
			if (!(*lineptr))
			{
				perror("Memory reallocation error");
				exit(EXIT_FAILURE);
			}
		}
		(*lineptr)[i] = c;
		(*lineptr)[i + 1] = '\0';
		i++;
	}

	if (i == 0 && c == EOF)
	{
		return (-1);
	}
	*lineptr = _realloc(*lineptr, *bufferSize * sizeof(char),
			(i + 2) * sizeof(char), sizeof(char));
	*bufferSize = i + 2;
	return (i);
}
