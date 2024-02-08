#include <stdio.h>

int main()
{
    long n = 0;
    scanf("%ld", &n);
    long sp[n];
    for (int i = 0; i < n; i++) {
        scanf("%ld", &sp[i]);
    }
    long k = 0;
    scanf("%ld", &k);
    long s = 0;
    for (int i = 0; i < k; i++) {
        s = s + sp[i];
    }
    long maxs = s;
    for (int i = k; i < n; i++) {
        s = s + sp[i];
        s = s - sp[i - k];
        if (maxs < s) maxs = s;
    }
    printf("%ld", maxs);
    return 0;
}