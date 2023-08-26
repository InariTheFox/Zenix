#include "stdlib.h"

int _divsint(int n, int d) { return div(n, d).quot; }

int _modsint(int n, int d) { return div(n, d).rem; }

long int _divslong(long int n, long int d) { return ldiv(n, d).quot; }

long int _modslong(long int n, long int d) { return ldiv(n, d).rem; }

unsigned int _divuint(unsigned int n, unsigned int d)
{
    return (unsigned int)ldiv(n, d).quot;
}

unsigned int _moduint(unsigned int n, unsigned int d)
{
    return (unsigned int)ldiv(n, d).rem;
}

div_t div(int n, int d)
{
    div_t result = {0, n};

    while (result.rem >= d)
    {
        result.rem = result.rem - d;
        result.quot = result.quot + 1;
    }

    return result;
}

ldiv_t ldiv(long int n, long int d)
{
    ldiv_t result = {0, n};

    while (result.rem >= d)
    {
        result.rem = result.rem - d;
        result.quot = result.quot + 1;
    }

    return result;
}