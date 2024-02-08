#include <stdio.h>

int main()
{
    long sp1[8], sp2[8];
    for (int i = 0; i < 8; i++) {
        scanf("%ld", &sp1[i]);
    }
    for (int i = 0; i < 8; i++) {
        scanf("%ld", &sp2[i]);
    }
    int s = 0;
    for (int i = 0; i < 8; i++) {
        int c = 0;
        for (int k = 0; k < 8; k++) {
            if (sp1[i] == sp2[k]) c = c + 1;
        }
        int c2 = 0;
        for (int k = 0; k < 8; k++) {
            if (sp1[i] == sp1[k]) c2 = c2 + 1;
        }
        if (c == c2) s = s + 1;
    }
    if (s == 8) {
        printf("yes");
    }
    else {
        printf("no");
    }
    return 0;
}