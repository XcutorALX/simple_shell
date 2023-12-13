#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * getLine - this function reads and saves the specified length
 * of characters in the provided pointer location
 *
 *@lineptr: an array of string
 *@bufferSize: the length of characters to read
 *@stream: the file to read from
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
			*bufferSize *= 1.5;
			*lineptr = realloc(*lineptr, *bufferSize * sizeof(char));

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
	*bufferSize = i;
	*lineptr = realloc(*lineptr, *bufferSize * sizeof(char));
	(*lineptr)[i] = '\0';

	return (i);
}
