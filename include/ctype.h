#ifndef __CTYPE_H__
#define __CTYPE_H__

#define _U  0x01 /* uppercase */
#define _L  0x02 /* lowercase */
#define _D  0x04 /* digit */
#define _C  0x08 /* control */
#define _P  0x10 /* punctuation */
#define _S  0x20 /* whitespace (space/lf/tab) */
#define _X  0x40 /* hex digit */
#define _SP 0x80 /* hard space (0x20) */

extern unsigned char    _ctype[];
extern char             _ctmp;

/* Test for an alphanumeric character */
#define isalnum(c) ((_ctype + 1)[c] & (_U | _L | _D))

/* Test for a 7-bit US-ASCII character */
#define isascii(c) (((unsigned)c) <= 0x7f)

#define isalpha(c) ((_ctype + 1)[c] & (_U | _L))

/* Test for a control character */
#define iscntrl(c) ((_ctype + 1)[c] & (_C))

/* Test for a decimal digit */
#define isdigit(c) ((_ctype + 1)[c] & (_D))

/* Test for a lowercase letter */
#define islower(c) ((_ctype + 1)[c] & (_L))

/* Test for a printable character */
#define isprint(c) ((_ctype + 1)[c] & (_P | _U | _L | _D | _SP))

/* Test for a punctuation character */
#define ispunct(c) ((_ctype + 1)[c] & (_P))

/* Test for a whitespace character */
#define isspace(c) ((_ctype + 1)[c] & (_S))

/* Test for a uppercase letter */
#define isupper(c) ((_ctype + 1)[c] & (_U))

/* Test for a hexadecimal digit*/
#define isxdigit(c) ((_ctype + 1)[c] & (_D | _X))

/* Convert an integer to a 7-bit ASCII character */
#define toascii(c) (((unsigned)c) & 0x7f)

/* Convert uppercase letter to lowercase letter */
#define tolower(c) (_ctmp = c, isupper(_ctmp) ? _ctmp - ('A' - 'a') : _ctmp)

/* Convert lowercase letter to uppercase letter */
#define toupper(c) (_ctmp = c, islower(_ctmp) ? _ctmp - ('a' - 'A') : _ctmp)

#endif