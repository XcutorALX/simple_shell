#include "main.h"

/**
 * myexists - tests if a pointer exists in an array
 *
 * @allocMem: an array that keeps track of dynamically allocated memory
 * @ptr: the pointer to compare
 *
 * Returns: 0 if the ptr isnt in the list and 1 if it is
 */

int myexists(memStruct *allocMem, void *ptr)
{
	int i;

	for (i = 0; (allocMem->memPtr)[i] != NULL; i++)
	{
		if (ptr == allocMem->memPtr[i])
			return 0;
	}
	return 1;
}
