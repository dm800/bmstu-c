#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int t = 0;
    scanf("%d", & t);
    int n = abs(t);
    if (t == -2147483648) {
        t = 2;
    }
    t = abs(t);
    if (t >= pow(2, 22)) {
        t = round(pow(2, 22));
    }
    bool sp[t - 1];
    for (int i = 0; i < t - 1; i++) {
        sp[i] = true;
    }
    for (int i = 0; i < t - 1; i++) {
        bool elem = sp[i];
        if (elem) {
            for (int k = i + i + 2; k < t - 1; k = k + i + 2) {
                sp[k] = false;
            }
        }
    }
    int ans = 0;
    int prevn = n;
    while (abs(n) >= pow(2, 22)) {
        for (int i = 2; i < round(sqrt(n)) + 1; i++) {
            if (n % i == 0) {
                n = n / i;
                break;
            }
        }
        if (prevn == n) {
            ans = n;
            break;
        }
        prevn = n;
    }
    if (ans == 0) {
        for (int i = 0; i < t - 1; i++) {
            if ((sp[i]) && (n % (i + 2) == 0)) {
                if (ans < i + 2) {
                    ans = i + 2;
                }
            }
        }
    }
    printf("%d", abs(ans));
    return 0;
}