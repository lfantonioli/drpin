#include <stdio.h>
#include "complex.h"
 
int complex_operation(int a, int b)
{
    int ca = 2*b;
    int cb = ca + 2 - a;
    return ca*cb + a*b;
}
