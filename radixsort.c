#include <stdio.h>
#include <math.h>

union Int32 {
    int x;
    unsigned char bytes[4];
};

int mainkey(union Int32 elem, int i) {
    if (i == 3) {
        if (elem.x >= 0) {
            return elem.bytes[i] + 128;
        }
        else {
            return elem.bytes[i] - 128;
        }
    }
    else {
        return elem.bytes[i];
    }
}

void distribsort(union Int32 *in, size_t nel, size_t n, int (*key)(union Int32 elem, int i), int num, union Int32 *dest) {
    int count[n];
    for (int i = 0; i < n; i++) {
        count[i] = 0;
    }
    int j = 0;
    while (j < nel) {
        int k = key(in[j], num);
        count[k] += 1;
        j++;
    }
    int i = 1;
    while (i < n) {
        count[i] += count[i - 1];
        i++;
    }
    int s = 0;
    j = nel - 1;
    while (j >= 0) {
        int k = key(in[j], num);
        s = count[k] - 1;
        count[k] = s;
        dest[s] = in[j];
        j--;
    }
    
}

void radixsort(union Int32 *in, size_t nel, union Int32 *dest) {
    for (int i = 0; i < nel; i++) {
        dest[i] = in[i];
    }
    union Int32 temp[nel];
    for (int i = 0; i < 4; i++) {
        distribsort(dest, nel, 256, mainkey, i, temp);
        for (int c = 0; c < nel; c++) {
            dest[c] = temp[c];
        }
        /* for (int k = 0; k < nel; k++) {
            printf("%d ", dest[k].x);
        }
        printf("\n"); */
    }
}



int main()
{
    int n = 0;
    scanf("%d", &n);
    union Int32 sp[n];
    union Int32 ans[n];
    union Int32 k = { -1 };
    for (int i = 0; i < n; i++) {
        union Int32 temp;
        scanf("%d", &temp.x);
        sp[i] = temp;
        // printf("%d %d %d %d \n", sp[i].bytes[0], sp[i].bytes[1], sp[i].bytes[2], sp[i].bytes[3]);
    }
    // printf("\n");
    radixsort(sp, n, ans);
    for (int i = 0; i < n; i++) {
        printf("%d ", ans[i].x);
    }
    return 0;
}