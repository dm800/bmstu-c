#include <stdio.h>

void revarray(void *base, size_t nel, size_t width) {
    for (int i = 0; i < (nel / 2); i++) {
        for (int k = 0;k<width;k++) {
            char temp=*((char*)base+k+i*width);
            *((char*)base + i * width + k) = *((char*)base + width * (nel - i - 1) + k);
            *((char*)base + width * (nel - i - 1) + k) = temp;
        }
    }
}