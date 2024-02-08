#include <stdio.h>

int maxarray(void *base, size_t nel, size_t width,
        int (*compare)(void *a, void *b))
{
    long ans = 0;
    for (int i = 0; i < nel; i++) {
        if (compare((char*)base + i * width, (char*)base + ans * width) > 0) {
            ans = i;
        }
    }
    return ans;
}

int check(void *a, void *b) {
    return ((int*)a - (int*)b);
}