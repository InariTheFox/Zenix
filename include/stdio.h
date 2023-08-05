#ifndef __STDIO_H__
#define __STDIO_H__

#include <stddef.h>

#define STDIN_FILENO    0
#define STDOUT_FILENO   1
#define STDERR_FILENO   2

#define EOF (-1)

#define FILENAME_MAX    (260)

#define FOPEN_MAX   (20)

#define BUFSIZ  512

#ifndef _VA_LIST
#define _VA_LIST
typedef char *va_list;
#endif

typedef struct _iobuf
{
    char *_ptr;
    int _count;
    char *_base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char *_tmpfname;
} FILE;

FILE *fopen(const char *filename, const char *mode);
int *fclose(FILE *stream);
int fflush(FILE *stream);
int remove(const char *filename);
int rename(const char *oldname, const char* newname);
FILE *tmpfile(void);
char *tmpnam(char *str);
void setbuf(FILE *stream, char *buffer);

int fprintf(FILE *stream, const char* format, ...);
int printf(const char* format, ...);
int sprintf(char *str, const char *format, ...);
int vfprintf(FILE *stream, const char* format, va_list arg);
int vprintf(const char *format, va_list arg);
int vsprintf(char *str, const char *format, va_list arg);

int fscanf(FILE *stream, const char *format, ...);
int scanf(const char *format, ...);
int sscanf(char *str, const char *format, ...);

int fgetc(FILE *stream);
char *fgets(char *str, int num, FILE *stream);
int fputc(int character, FILE *stream);
int fputs(const char *str, FILE *stream);
int getc(FILE *stream);
int getchar(void);
char *gets(char *str);
int putc(int character, FILE *stream);
int putchar(int character);
int puts(const char *str);
int ungetc(int character, FILE *stream);

size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);

#ifndef _FPOS_T
#define _FPOS_T
typedef int fpos_t;
#endif

int fgetpos(FILE *stream, fpos_t *pos);
int fsetpos(FILE *stream, const fpos_t *pos);

void clearerr(FILE *stream);
int feof(FILE *stream);
int ferror(FILE *stream);
void perror(const char *str);

#endif