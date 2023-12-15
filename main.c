#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

/**
 * main - simple shell that runs commands without any argument and
 * with their full path
 *
 *@ac: the number of arguments passed
 *@av: an array of arguments as strings
 *
 * Return: always returns 0
 */

int main(int ac, char **av)
{
	size_t dirLen = 1024;
	char *dir;
	memStruct *allocMem;

	allocMem = malloc(sizeof(memStruct));

	if (!allocMem)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	allocMem->size = 0;
	allocMem->allocatedSize = 0;
	allocMem->memPtr = NULL;

	dir = malloc(dirLen * sizeof(char));

	if (ac < 2)
	{
		while (getcwd(dir, dirLen) == NULL)
		{
			dir = _realloc(dir, dirLen, dirLen * 1.5, sizeof(char *));
			dirLen *= 1.5;
		}
		shellloop(av, allocMem);
	}
	else
	{
		interactiveMode(av, dir, allocMem);
	}

	if (allocMem->memPtr)
		freeMem(allocMem);

	free(dir);
	free(allocMem);
	return (0);
}
