#include "stdlib.h"

int _divsint(int n, int d) { return div(n, d).quot; }

int _modsint(int n, int d) { return div(n, d).rem; }

div_t div(int n, int d)
{
    div_t result = {0, n};
    // result.rem = n;
    // result.quot = 0;

    while (result.rem >= d)
    {
        result.rem = result.rem - d;
        result.quot = result.quot + 1;
    }

    return result;
}