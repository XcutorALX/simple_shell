#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#define DELIM ":"
/**
 * searchFile - this function searches for a file in the system PATH
 *
 *@fileName: the name of the file to search for
 *@allocMem: a struct keeping track of dynamically allocated memory
 *
 * Return: 1 if found and 0 if not found
 */

char *searchFile(char *fileName, memStruct *allocMem)
{
	char *path = _getenv("PATH", allocMem);
	char *path_copy;
	char **pathTokens;
	char *fullPath;
	size_t index, fileLength, i, j;
	struct stat st;

	if (!path)
		return (NULL);
	path_copy = _strdup(path);
	pathTokens = tokenize(path_copy, DELIM);

	if (!pathTokens)
	{
		perror("Unable to get paths");
		return (NULL);
	}

	for (fileLength = 0; fileName[fileLength] != '\0'; fileLength++)
		;
	fullPath = (char *)malloc(1024);

	for (index = 0; pathTokens[index]; index++)
	{
		for (i = 0; pathTokens[index][i] != '\0'; i++)
		{
			fullPath[i] = pathTokens[index][i];
		}
		fullPath[i++] = '/';
		for (j = 0; fileName[j] != '\0'; j++, i++)
		{
			fullPath[i] = fileName[j];
		}
		fullPath[i] = '\0';

		if (stat(fullPath, &st) == 0)
		{
			free(path_copy);
			free(pathTokens);
			return (fullPath);
		}
	}
	
	free(path_copy);
	free(pathTokens);
	free(fullPath);
	return (NULL);
}
