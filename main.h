#include <stdlib.h>
#include <stdio.h>
#ifndef MAIN_H
#define MAIN_H

extern char **environ;

typedef struct Node {
	char *data;
	int *num;
	void *ptr;
	struct Node *next;
} Node;

typedef struct {
	Node *head;
	int size;
} list_l;

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

#endif
