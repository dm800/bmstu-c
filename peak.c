#include <stdio.h>

unsigned long peak(unsigned long nel,
        int (*less)(unsigned long i, unsigned long j))
{
    
    unsigned long i = 0;
    if (nel == 1) {
        return 0;
    }
    if (less(i + 1, i) == 1) {
        return i;
    }
    if (less(nel - 2, nel - 1) == 1) {
        return nel - 1;
    }
    for (i = 1; i < nel - 1; i++) {
        if (less(i, i - 1) + less(i, i + 1) == 0) {
            return i;
        }
    }
}