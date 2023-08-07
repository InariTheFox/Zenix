#ifndef __SYS_UNISTD_H__
#define __SYS_UNISTD_H__

#include "stdio.h"
#include "types.h"
#include "utsname.h"

int          access(const char *, int);
int          chdir(const char *);
int          chown(const char *, uid_t, gid_t);
int          chroot(const char *);
int          chsize(int, long);
int          close(int);
int          creat(const char *, int);
int         *crypt(const char *, const char *);
int          dup(int);
void         encrypt(char *, int);
int          eof(int);
int          execv(const char *, const char **);
int          execve(const char *, const char **);
int          execvp(const char *, const char **);
void         exit(int);
long         filelength(int);
int          fileno(FILE *);
pid_t        fork(void);
int          fsync(int);
gid_t        getegid(void);
uid_t        geteuid(void);
gid_t        getgid(void);
char        *getlogin(void);
pid_t        getpid(void);
uid_t        getuid(void);
char        *getcwd(char *, size_t);
int          isatty(int);
int          link(const char *, const char *);
off_t        lseek(int, long, int);
int          open(const char *, int, ...);
int          pause(void);
int          pipe(int *);
size_t       read(int, void *, size_t);
size_t       readlink(const char *, char *, size_t);
int          rmdir(const char *);
int          setegid(gid_t);
int          seteuid(uid_t);
int          setgid(gid_t);
int          setuid(uid_t);
unsigned int sleep(unsigned int);
int          symlink(const char *, const char *);
void         sync(void);
int          truncate(const char *, off_t);
char        *ttyname(int);
int          uname(struct utsname *);
int          umask(int);
int          unlink(const char *);
size_t       write(int, const void *, size_t);

#endif