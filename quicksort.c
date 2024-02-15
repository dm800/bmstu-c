#include <stdio.h>
#include <stdlib.h>

void swap(int ind1, int ind2, long *in) {
    long temp = in[ind1];
    in[ind1] = in[ind2];
    in[ind2] = temp;
}

int partition(int low, int high, long *in) {
    int i = low;
    int j = low;
    while (j < high) {
        if (in[j] <= in[high]) {
            swap(i, j, in);
            i++;
        }
        j++;
    }
    swap(i, high, in);
    return i;
}

void choosesort(long *in, int low, int high) {
    int j = high;
    while (j > low) {
        int k = j;
        int i = j - 1;
        while (i >= low) {
            if (in[i] >= in[k]) {
                k = i;
            }
            i--;
        }
        swap(k, j, in);
        j--;
    }
}

void sorting(long *in, int low, int high, int m) {
    while (high - low + 1 >= m) {
        int q = partition(low, high, in);
        if (q- 1 - low < high - q - 1) {
            sorting(in, low, q - 1, m);
            low = q + 1;
        }
        else {
            sorting(in, q + 1, high, m);
            high = q - 1;
        }
    }
    choosesort(in, low, high);
}


int main()
{
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);
    long arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%ld", &arr[i]);
    }
    sorting(arr, 0, n - 1, m);
    for (int i = 0; i < n; i++) {
        printf("%ld ", arr[i]);
    }
}