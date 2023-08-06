#ifndef __SYS_UTSNAME_H__
#define __SYS_UTSNAME_H__

struct utsname
{
    char sysname[14];
    char nodename[14];
    char release[8];
    char version[8];
    char machine[8];
    char domainname[14];
};

#endif