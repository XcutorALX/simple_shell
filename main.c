#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "main.h"

/**
 * main: simple shell that runs commands without any argument and
 * with their full path
 * 
 * Return: always returns 0
 */

void **allocMem;
int allocated = 0 ;
int sizeAllocMem = 84;

int main(int *ac, char **av)
{
	size_t bufferSize = 1024;
	size_t dirLen = 1024;
	struct stat st;
	char *lineptr = NULL;
	char delim[] = " ";
	char **command, *dir, *temp;
	
	allocMem = malloc(sizeAllocMem * sizeof(void));
	allocMem[0] = NULL;

	dir = malloc(dirLen * sizeof(char));

	while (getcwd(dir, dirLen) == NULL)
	{
		dir = _realloc(dir, dirLen, dirLen * 1.5, sizeof(char *));
		dirLen *= 1.5;
	}

	printf("$ ");
	while(getLine(&lineptr, &bufferSize, stdin) != -1)
	{
		command = tokenize(lineptr, delim);
		if (stat(command[0], &st) == 0)
			shellHelper(command, environ);
		else if((temp = searchFile(command[0])) != NULL)
		{
			command[0] = temp;
			shellHelper(command, environ);
		}
		else
			printf("%s: 1: %s: not found\n", av[0], command[0]); 
		printf("$ ");
	}
	
	free(lineptr);
        freeMem();
	return (0);
}
