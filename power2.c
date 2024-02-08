#include <stdio.h>
#include <math.h>



long recfunc(int *sp, size_t n, int ind, long s) {
    if (ind == n) {
        if ((((s - 1) & s) == 0) && (s != 0)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return recfunc(sp, n, ind + 1, s) + recfunc(sp, n, ind + 1, s + sp[ind]);
    }
}


int main()
{
    unsigned int i = 0;
    int n = 0;
    scanf("%d", &n);
    int sp[n];
    for (i = 0; i < n; i++) {
        scanf("%d", &sp[i]);
    }
    long ans = recfunc(sp, n, 0, 0);
    printf("%ld", ans);
    return 0;
}