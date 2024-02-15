#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void sorting(char *in, char *dest) {
    int arr[26] = { 0 };
    int nel = strlen(in);
    int s = 0;
    for (int i = 0; i < nel - 1; i++) {
        arr[(int)in[i] - (int)'a'] += 1;
        s += 1;
    }
    int arr2[26] = { 0 };
    int last = 0;
    for (int i = 0; i < 26; i++) {
        arr2[i] = last + arr[i];
        last = arr2[i];
    }
    
    int j = s - 1;
    while (j >= 0) {
        int k = (int)(in[j]);
        int i = arr2[k - (int)'a'] - 1;
        arr2[k - (int)'a'] = i;
        dest[i] = in[j];
        j = j - 1;
    }
    dest[nel - 1] = '\0';
}


int main()
{
   char str[1000002];
   char dest[1000002];
   fgets(str, 1000002, stdin);
   sorting(str, dest);
   printf("%s", dest);
}