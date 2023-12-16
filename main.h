#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

/**
 * struct memoryStruct - a structure to keep track of
 * dynamically allocated memory
 * @memPtr: an array of pointer
 * @size: the size of the array
 * @sizeAllocated: current occupied space of the array
 */

typedef struct memoryStruct
{
	void **memPtr;
	int size;
	int allocatedSize;
} memStruct;



/**
 * struct Node - a node of a linked list
 * @num: the number field
 * @data: a string
 * @next: points to the next node
 */

typedef struct Node
{
	char *data;
	int *num;
	struct Node *next;
} Node;

/**
 * struct list_k - a linked list
 * @head: the first node on the list
 * @size: the size of the list
 */

typedef struct list_k
{
	Node *head;
	int size;
} list_l;

/**
 * struct built - a structure with a cmd name
 * and a function pointer
 * @cmd: the command name
 * @func: a pointer to the function of the name
 */

typedef struct built
{
	char *cmd;
	int (*func)(char **ptr, memStruct *allocMem);
} builtins;

int isempty(char *str);
int puterr(char c);
void printerr(char *str);
int _putchar(char c);
void printstr(char *str);
int getLine(char **lineptr, size_t *bufferSize, int fd);
int getPipe(char **lineptr, size_t *bufferSize, int fd);
char **strTok(char *str, char *delim);
char **tokenize(char *str, char *delim);
int shellHelper(char **argv, char **env);
char *_getenv(const char *varName, memStruct *allocMem);
void printPath(void);
int print_list(list_l *list);
int add_node(list_l *list, Node *newNode);
list_l *createList(void);
int _setenv(char *name, const char *value, int overwrite, memStruct *allocMem);
int freeMem(memStruct *list);
int addAddress(void *ptr, memStruct *list);
int _unsetenv(char *name, memStruct *allocMem);
char *_strdup(char *str);
char *strcon(const char *strOne, const char *strTwo);
char *_strtok(char *str, char *delim);
int _strcmp(const char *strone, const char *strtwo);
void *_realloc(void *ptr, int size, int newSize, int mode);
int _memcpy(char *ptr, char *newPtr);
int memcpystr(char **ptr, char **newptr);
char *searchFile(char *fileName, memStruct *allocMem);
int printEnv(char **argv, memStruct *allocMem);
int myexit(char **argv, memStruct *allocMem);
int _atoi(char *str);
int _pow(long int x, long int y);
void testBuiltin(char **argv, char *av, memStruct *allocMem);
int interactiveMode(char **av, char *currentPath, memStruct *allocMEm);
int shellloop(char **av, memStruct *allocMem);
int my_fgetc(int fd);
void _myexit(int exitcode, memStruct *allocMem);

#endif
