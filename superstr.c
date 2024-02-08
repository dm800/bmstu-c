#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(int *sp, int n, int ind) {
    int nel = n - ind;
    if (nel > 1) {
        for (int i = 0; i < nel / 2; i++) {
            int temp = sp[i + ind];
            sp[i + ind] = sp[n - i - 1];
            sp[n - i - 1] = temp;
        }
    }
}


int max(int a, int b) {
    if (a >= b) {
        return a;
    }
    return b;
}

int count(char *in1, char *in2) {
    int c = 0;
    int nel1 = strlen(in1);
    int nel2 = strlen(in2);
    for (int i = 0; i < (nel1 + nel2 - max(nel1, nel2)); i++) {
        char is_prefix = 1;
        for (int k = i; k > 0; k--) {
            if (in1[nel1 - k] != in2[i - k]) {
                is_prefix = 0;
                break;
            }
        }
        if (is_prefix) {
            c = i;
        }
    }
    return c;
}

int mainsp[10][10];

int summary(int *perm, char *in, int n) {
    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        char *word1 = (char*)(in + perm[i] * 100001);
        char *word2 = (char*)(in + perm[i + 1] * 100001);
        ans += mainsp[perm[i]][perm[i + 1]];
    }
    return ans;
}


int main()
{
    int n;
    scanf("%d", &n);
    char arr[n][100001];
    int sp[n];
    int base = 0;
    for (int i = 0; i < n; i++) {
        sp[i] = i;
        scanf("%s", arr[i]);
        base += strlen(arr[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (i == k) {
                mainsp[i][k] = 0;
            }
            else {
                mainsp[i][k] = count(arr[i], arr[k]);
            }
        }
    }
    if (n == 1) {
        printf("%ld", strlen(arr[0]));
    }
    else {
        int k = 0;
        int l = 0;
        int ret = summary(sp, *arr, n);
        while (k != -1) {
            k = -1;
            for (int s = 0; s < n - 1; s++) {
                if (sp[s] < sp[s + 1]) {
                    k = s;
                }
            }
            if (k == -1) {
                break;
            }
            for (int s = k + 1; s < n; s++) {
                if (sp[k] < sp[s]) {
                    l = s;
                }
            }
            int temp = sp[k];
            sp[k] = sp[l];
            sp[l] = temp;
            reverse(sp, n, k + 1);
            ret = max(summary(sp, *arr, n), ret);
        }
        printf("%d", base - ret);
    }
    return 0;
}