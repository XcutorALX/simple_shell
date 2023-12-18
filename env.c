#include <stdio.h>
#include <string.h>
#include "main.h"

#define DELIM "="

/**
 * _getenv - gets the variable value from the current enviroment
 *
 *@name: The enviroment variable to search for
 *@allocMem: a struct keeping track of dynamically allocated memory
 *
 * Return: returns a pointer to a string containing the value of the
 * enviroment variable returns NULL if the variable wasn't found
 */

char *_getenv(const char *name, memStruct *allocMem)
{
	size_t index;
	char **varToken;
	char *varDup;

	for (index = 0; environ[index] != NULL; index++)
	{
		varDup = _strdup(environ[index]);
		varToken = tokenize(varDup, DELIM);

		if (_strcmp(varToken[0], name) == 0)
		{
			addAddress(varDup, allocMem);
			addAddress(varToken, allocMem);
			return (varToken[1]);
		}

		free(varDup);
		free(varToken);
	}
	return (NULL);
}


/**
 * _setenv - this function adds a variable
 * name and its value to the current envioment
 *
 * @argv: commandline arguments
 * @allocMem: a struct keeping track of dynamically allocated memory
 *
 * Return: returns zero on success or -1 on error,
 * with errno set to indicate the error
 */

int _setenv(char **argv, memStruct *allocMem)
{
	size_t envLen;
	char *varPair, *full, *buffer, *varDup, **temp;
	char *name, *value;
	char join[] = "=";
	int seen = 0;
	int overwrite;

	name = argv[1];
	if (name)
		value = argv[2];
	if (value && argv[3])
		overwrite = _atoi(argv[3]);
	temp = malloc(1024 * sizeof(char *));
	full = strcon(name, join);
	varPair = strcon(full, value);
	free(full);
	for (envLen = 0; environ[envLen] != NULL; envLen++)
	{
		varDup = _strdup(environ[envLen]);
		buffer = _strtok(varDup, DELIM);
		if ((_strcmp(buffer, name) == 0))
		{
			if (overwrite == 1)
				temp[envLen] = varPair;
			seen = 1;
			temp[envLen] = environ[envLen];
		}
		else
			temp[envLen] = environ[envLen];
		free(varDup);
	}
	if (seen != 1)
		temp[envLen++] = varPair;
	temp = (char **)_realloc(temp, 1024,
		(envLen + 1) * sizeof(char *), sizeof(char *));
	temp[envLen] = NULL;
	environ = temp;
	addAddress((void *)temp, allocMem);
	addAddress((void *)varPair, allocMem);
	return (0);
}

/**
 * _unsetenv - this function removes a variable and its value
 * from the enviroment
 *
 *@argv: command line arguments
 *@allocMem: a struct keeping track of dynamically allocated memory
 *
 * Return: returns 0 on failure
 */

int _unsetenv(char **argv, memStruct *allocMem)
{
	char *name;
	size_t envLen, newEnvLen, size;
	char **newEnv, *buffer, *env_dup;

	name = argv[0];
	size = 80;
	newEnv = malloc(size * sizeof(char *));
	for (envLen = 0, newEnvLen = 0; environ[envLen] != NULL; envLen++)
	{
		if (newEnvLen == size - 1)
		{
			newEnv = _realloc(newEnv, size * sizeof(char *)
			, size * 1.5 * sizeof(char *), sizeof(char *));
			size *= 1.5;
			if (!size)
				exit(EXIT_FAILURE);
		}
		env_dup = _strdup(environ[envLen]);
		buffer = _strtok(env_dup, DELIM);
		if (_strcmp(buffer, name) != 0)
		{
			newEnv[newEnvLen] = environ[envLen];
			newEnvLen++;
		}
		free(env_dup);
	}
	newEnv[newEnvLen++] = NULL;
	newEnv = _realloc(newEnv, size * sizeof(char *),
		newEnvLen * sizeof(char *), sizeof(char *));
	size = newEnvLen;
	if (!size)
	{
		printstr("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	environ = newEnv;
	addAddress(newEnv, allocMem);
	return (0);
}
