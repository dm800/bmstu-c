#include <stdio.h>

int main()
{
    long x = 0, n1 = 1, n2 = 1, n3 = 1;
    scanf("%ld", &x);
    if (x == 0) printf("0");
    while (n2 <= x) {
        n3 = n1 + n2;
        n1 = n2;
        n2 = n3;
    }
    while ((n1 >= 1) && (n2 > 1)) {
        if (x >= n1) {
            printf("1");
            x = x - n1;
        }
        else {
            printf("0");
        }
        n3 = n2 - n1;
        n2 = n1;
        n1 = n3;
    }
    printf("\n");
    return 0;
}