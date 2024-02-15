#include <stdio.h>
#include <stdlib.h>

void merge(long * sp1, size_t n1, long * sp2, size_t n2, long * dest) {
    int n3 = 0;
    int k = 0;
    int j = 0;
    while (n3 < n1 + n2) {
        if ((j >= n2) || ((k < n1) && (abs(sp1[k]) <= abs(sp2[j])))) {
            dest[n3] = sp1[k];
            k += 1;
        } else {
            dest[n3] = sp2[j];
            j += 1;
        }
        n3 += 1;
    }
}

void insertsort(long * in, size_t nel) {
    int i = 1;
    while (i < nel) {
        long elem = in [i];
        int loc = i - 1;
        while ((loc >= 0) && (abs(in [loc]) > abs(elem))) {
            in [loc + 1] = in [loc];
            loc = loc - 1;
        }
        in [loc + 1] = elem;
        i = i + 1;
    }
}

void sorting(long * in, size_t nel) {
    if (nel > 4) {
        int l2 = nel / 2 + nel % 2;
        int l1 = nel / 2;
        long sp1[l1];
        long sp2[l2];
        for (int i = 0; i < l1; i++) {
            sp1[i] = 0;
            sp2[i] = 0;
        }
        if (nel % 2 == 1) {
            sp2[nel / 2] = 0;
        }
        int i = 0;
        while (i < nel) {
            if (i < l1) {
                sp1[i] = in [i];
            } else {
                sp2[i - nel / 2] = in [i];
            }
            i += 1;
        }
        sorting(sp1, l1);
        sorting(sp2, l2);
        long temp[nel];
        merge(sp1, l1, sp2, l2, temp);
        for (int i = 0; i < nel; i++) {
            in [i] = temp[i];
        }
    } else {
        insertsort(in, nel);
    }
}

int main() {
    int n = 0;
    scanf("%d", & n);
    long arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%ld", & arr[i]);
    }
    sorting(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%ld ", arr[i]);
    }
}