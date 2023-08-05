#ifndef __TIME_H__
#define __TIME_H__

#include <stddef.h>

#include "sys/types.h"

#define CLOCKS_PER_SEC  ((clock_t)1000)
#define CLK_TCK         CLOCKS_PER_SEC

/* Time structure */
struct tm
{
    char        sec;     /* Seconds [0-61] (Because fucking leap-seconds) */
    char        min;     /* Minutes [0-59] */
    char        hour;    /* Hours [0-23] */
    char        mday;    /* Day of the Month [0-31] */
    char        mon;     /* Month [0-11] */
    char        _unused; /* padding to keep aligned */
    int         year;    /* Years since 1900 */
    int         wday;    /* Day of the Week [0-6] (Sunday = 0) */
    int         yday;    /* Day of the Year [0-365] */
    int         isdst;   /* Is DST? (1 = DST, 0 = ST, -1 = Unknown) */
    long        gmtoff;  /* Timezone offset from GMT in seconds */
    const char  *zone;   /* Timezone name */
} tm;

/* Convert the number of seconds since epoch (time_t) to a date and time string */
char *ctime(const time_t);

/* Returns the difference in seconds between two times */
float difftime(time_t, time_t);

/* Converts the number of seconds since epoch (time_t) to time structure (tm) */
struct tm *localtime(const time_t *);

/* Convert time structure (tm) to number of seconds since epoch (time_t) */
time_t mktime(struct tm *);

/* Notifies the system that the timezone has changed */
void tzset(void);

#endif