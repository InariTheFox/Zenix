#ifndef __LOCALE_H__
#define __LOCALE_H__

#define LC_ALL          0
#define LC_COLLATE      1
#define LC_CTYPE        2
#define LC_MONETARY     3
#define LC_NUMERIC      4
#define LC_TIME         5
#define LC_ADDRESS      6
#define LC_TELEPHONE    7
#define LC_NAME         8
#define LC_PAPER        9
#define LC_MIN          LC_ALL
#define LC_MAX          LC_PAPER

struct lconv
{
    char *decimal_point;
    char *thousands_sep;
    char *grouping;
    char *int_curr_symbol;
    char *currency_symbol;
    char *mon_decimal_point;
    char *mon_thousands_sep;
    char *mon_grouping;
    char *positive_sign;
    char *negative_sign;
    char int_frac_digits;
    char frac_digits;
};

/* Sets the locale */
char *setlocale(int, const char *);

/* Gets the locale settings */
struct lconv *localeconv(void);

#endif