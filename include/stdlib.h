#ifndef __STDLIB_H__
#define __STDLIB_H__

#include <stddef.h>

void *calloc(size_t num, size_t size);
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

void abort(void);
int atexit(void (*func)(void));
void exit(int status);
char *getenv(const char *name);
int system(const char *command);

#define EXIT_SUCCESS    0
#define EXIT_FAILURE    -1

#ifndef _MAX_PATH
#define _MAX_PATH   (260)
#endif

#ifndef RAND_MAX
#define RAND_MAX    0x7FFF
#endif

float atof(const char *str);
int atoi(const char *str);
long atol(const char *str);

int rand(void);

#endif