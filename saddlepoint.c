#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    short x = 0, y = 0;
    scanf("%hd %hd", &y, &x);
    long sp[y][x];
    long sp2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < y; i++) {
        double max = -pow(2, 70);
        for (int k = 0; k < x; k++) {
            long t = 0;
            scanf("%ld", &t);
            sp[i][k] = t;
            if (max < t) max = t;
        }
        sp2[i] = max;
    }
    short ansx = -1, ansy = -1;
    for (int k = 0; k < x; k++) {
        double min = pow(2, 70);
        short index = 0;
        for (int i = 0; i < y; i++) {
            long elem = sp[i][k];
            if (min > elem) {
                min = elem;
                index = i;
            }
        }
        if (sp2[index] == min) {
            ansx = k;
            ansy = index;
        }
    }
    if (ansx == -1) printf("none");
    else printf("%hd %hd", ansy, ansx);
    return 0;
}