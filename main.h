#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

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
	int (*func)(char **ptr);
} builtins;

extern void **allocMem;
extern int allocated;
extern int sizeAllocMem;

int getLine(char **lineptr, size_t *bufferSize, FILE *stream);
char **strTok(char *str, char *delim);
char **tokenize(char *str, char *delim);
int shellHelper(char **argv, char **env);
char *_getenv(const char *varName);
void printPath(void);
int print_list(list_l *list);
int add_node(list_l *list, Node *newNode);
list_l *createList(void);
int _setenv(char *name, const char *value, int overwrite);
int freeMem(void);
int addAddress(void *ptr);
int _unsetenv(char *name);
char *_strdup(char *str);
char *strcon(const char *strOne, const char *strTwo);
char *_strtok(char *str, char *delim);
int _strcmp(const char *strone, const char *strtwo);
void *_realloc(void *ptr, int size, int newSize, int mode);
int _memcpy(char *ptr, char *newPtr);
int memcpystr(char **ptr, char **newptr);
char *searchFile(char *fileName);
int printEnv(char **argv);
int myexit(char **argv);
int _atoi(char str[]);
int _pow(long int x, long int y);
int testBuiltin(char **argv, char *av);

#endif
