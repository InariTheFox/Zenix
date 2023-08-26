#ifndef __STDLIB_H__
#define __STDLIB_H__

#include "stddef.h"
#include "stdint.h"

void *calloc(size_t num, size_t size);
void  free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

void  abort(void);
int   atexit(void (*func)(void));
void  exit(int status);
char *getenv(const char *name);
int   system(const char *command);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

#ifndef _MAX_PATH
#define _MAX_PATH (260)
#endif

#ifndef RAND_MAX
#define RAND_MAX 0x7FFF
#endif

float atof(const char *str);
int   atoi(const char *str);
long  atol(const char *str);
char *itoa(int value, char *str, unsigned char radix);
char *utoa(unsigned int value, char *str, unsigned char radix);
char *ltoa(long value, char *str, unsigned char radix);

int rand(void);

typedef struct
{
    int quot;
    int rem;
} div_t;

typedef struct
{
    long int quot;
    long int rem;
} ldiv_t;

div_t  div(int n, int d);
ldiv_t ldiv(long int n, long int d);

#endif