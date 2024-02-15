#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void prefix(char *source, int *dest) {
    int t = 0;
    dest[0] = 0;
    int nel = strlen(source);
    int i = 1;
    while (i < nel) {
        while ((t > 0) && (source[t] != source[i])) {
            t = dest[t - 1];
        }
        if (source[t] == source[i]) {
            t = t + 1;
        }
        dest[i] = t;
        i = i + 1;
    }
}

void kmp(char *in, char *where) {
    int pi[strlen(in)];
    int nel = strlen(where);
    int nel2 = strlen(in);
    prefix(in, pi);
    int q = 0;
    int k = 0;
    while (k < nel) {
        while ((q > 0) && (in[q] != where[k])) {
            q = pi[q - 1];
        }
        if (in[q] == where[k]) {
            q += 1;
            if (q == nel2) {
                q = pi[q - 1];
                printf("%d ", k - nel2 + 1);
            }
        }
        k += 1;
    }
}

int main(int n, char *find[])
{
    kmp(find[1], find[2]);
    return 0;
}