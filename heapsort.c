#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    int c1 = 0;
    int c2 = 0;
    int i = 0;
    while (*((char*)a + i * sizeof(char)) != '\0') {
        if (*((char*)a + i * sizeof(char)) == 'a') {
            c1 += 1;
        }
        i++;
    }
    i = 0;
    while (*((char*)b + i * sizeof(char)) != '\0') {
        if (*((char*)b + i * sizeof(char)) == 'a') {
            c2 += 1;
        }
        i++;
    }
    return c1 - c2;
}

void swap(void *in, int a, int b, size_t n) {
    for (int i = 0; i < n; i++) {
        char temp = *((char*)in + a * n + i);
        *((char*)in + a * n + i) = *((char*)in + b * n + i);
        *((char*)in + b * n + i) = temp;
    }
}

void heapify(int (*compare)(const void *a, const void *b), int i, int n, void *base, size_t width) {
    while (1) {
        int l = 2 * i + 1;
        int r = l + 1;
        int j = i;
        if ((l < n) && (compare((void*)((char*)base + i * width), (void*)((char*)base + l * width)) < 0)) {
            i = l;
        }
        if ((r < n) && (compare((void*)((char*)base + i * width), (void*)((char*)base + r * width)) < 0)) {
            i = r;
        }
        if (i == j) {
            break;
        }
        swap(base, i, j, width);
    }
}


void buildheap(int (*compare)(const void *a, const void *b), int n, void *base, size_t width) {
    int i = n / 2 - 1;
    while (i >= 0) {
        heapify(compare, i, n, base, width);
        i--;
    }
}


void hsort(void *base, size_t nel, size_t width,
        int (*compare)(const void *a, const void *b))
{
    buildheap(compare, nel, base, width);
    int i = nel - 1;
    while (i > 0) {
        swap(base, 0, i, width);
        heapify(compare, 0, i, base, width);
        i--;
    }
}


int main()
{
    int n;
    scanf("%d", &n);
    char arr[n][1001];
    for (int i = 0; i < n; i++) {
        scanf("%s", arr[i]);
    }
    hsort(arr, n, 1001, compare);
    for (int i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }
    return 0;
}