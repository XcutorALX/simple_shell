#include <stdio.h>
#include "main.h"

/**
 * addAddress - adds an address to the global array keeping track
 * of dynamically allocated memory
 *
 * @ptr: the address to add to the array
 *
 * Return: returns 0
 */

int addAddress(void *ptr)
{
	void **allocMem;
	int allocated;
	int sizeAllocMem;

	if (allocated == sizeAllocMem - 1)
	{
		sizeAllocMem *= 1.5;
		allocMem = realloc(allocMem, sizeAllocMem * sizeof(void *));

		if (!allocMem)
		{
			perror("Memory reallocation failed");
			exit(EXIT_FAILURE);
		}
	}
	allocMem[allocated] = ptr;

	allocated += 1;
	allocMem[allocated] = NULL;

	return (0);
}

/**
 * freeMem - frees all dynamically allocated memory not freed
 *
 * Return: always 0
 */

int freeMem(void)
{
	void **allocMem;
	size_t i;

	for (i = 0; allocMem[i]; i++)
	{
		free(allocMem[i]);
	}
	free(allocMem);
	return (0);
}

/**
 * _realloc - this function reallocates a block of memory
 *
 * @ptr: a pointer to the start of a block
 * @size: the size of the block
 * @newSize: the new size of the block
 * @mode: the size of one unit in the array, i.e sizeof(char)
 *
 * Return: returns a pointer to the new block on success and NULL on failure
 */

void *_realloc(void *ptr, int size, int newSize, int mode)
{
	void *newPtr;

	if (!ptr)
		return (malloc(newSize));
	if (!newSize)
	{
		free(ptr);
		return (NULL);
	}
	if (newSize == size)
		return (ptr);

	newPtr = malloc(newSize * mode);
	if (!newPtr)
		return (NULL);

	if (mode == sizeof(char *))
		memcpystr((char **)ptr, (char **)newPtr);

	else if (mode == sizeof(char))
		_memcpy(ptr, newPtr);

	free(ptr);
	return (newPtr);
}

/**
 * _memcpy - copies data from one block into another
 *
 * @ptr: the block to copy from
 * @newPtr: the block to copy to
 *
 * Return: returns 0 on success and 1 on failure
 */

int _memcpy(char *ptr, char *newPtr)
{
	size_t i;

	for (i = 0; ptr[i] != '\0'; i++)
		((char *)newPtr)[i] = ((char *)ptr)[i];

	newPtr[i] = '\0';
	return (0);
}


/**
 * memcpystr - copies strings from one array of strings to another
 *
 * @ptr: the block to copy from
 * @newptr: the block to copy to
 *
 * Return: returns 0 on success and 1 on failure
 */

int memcpystr(char **ptr, char **newptr)
{
	size_t i;

	for (i = 0; ptr[i] != NULL; i++)
		((char **)newptr)[i] = ((char **)ptr)[i];

	newptr[i] = NULL;

	return (0);
}
