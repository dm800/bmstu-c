#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void kadane(double *in, int n) {
    int l = 0;
    int r = 0;
    double maxsum = in[0];
    int start = 0;
    double sum = 1;
    int i = 0;
    while (i < n) {
        sum *= in[i];
        if (sum > maxsum) {
            maxsum = sum;
            l = start;
            r = i;
        }
        i += 1;
        if (sum < 1) {
            sum = 1;
            start = i;
        }
    }
    printf("%d %d", l, r);
}


int main()
{
    int n;
    scanf("%d", &n);
    double arr[n];
    for (int i = 0; i < n; i++) {
        char temp[20];
        scanf("%s", temp);
        char word1[10];
        char word2[10];
        short delta = 0;
        for (int k = 0; k < strlen(temp); k++) {
            if (temp[k] == '/') {
                word1[k] = '\0';
                delta = k + 1;
            }
            else {
                if (delta == 0) {
                    word1[k] = temp[k];
                }
                else {
                    word2[k - delta] = temp[k];
                }
            }
        }
        word2[strlen(temp) - delta] = '\0';
        double n1 = atof(word1);
        double n2 = atof(word2);
        arr[i] = n1 / n2;
    }
    kadane(arr, n);
}