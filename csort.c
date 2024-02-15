#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct DictElem {
    char * key;
    int val;
};

static void countsort(char st[1001][1001], int nel) {
    struct DictElem * dict[nel];
    for (int i = 0; i < nel; i++) {
        struct DictElem * new = malloc(sizeof(struct DictElem));
        new->key = malloc(strlen(st[i]) + 1);
        strcpy(new -> key, st[i]);
        new -> val = 0;
        dict[i] = new;
    }
    for (int i = 0; i < nel; i++) {
        int curlen = strlen(st[i]);
        for (int k = 0; k < nel; k++) {
            if (curlen > strlen(st[k])) {
                dict[i] -> val += 1;
            } else if ((curlen == strlen(st[k])) && (i > k)) {
                dict[i] -> val += 1;
            }
        }
    }
    for (int i = 0; i < nel; i++) {
        strcpy(st[dict[i] -> val], dict[i] -> key);
        free(dict[i] -> key);
        free(dict[i]);
    }
}

void csort(char * src, char * dest) {
    char st[1001][1001];
    char temp[1001] = {
        0
    };
    int c = 0;
    int k = 0;
    char cur;
    short lastspace = 0;
    for (int i = 0; i < strlen(src); i++) {
        cur = src[i];
        if ((cur == ' ') && (lastspace == 0)) {
            temp[c] = '\0';
            strcpy(st[k], temp);
            k += 1;
            c = 0;
            lastspace = 1;
            continue;
        }
        if ((cur == ' ') && (lastspace == 1)) {
            continue;
        }
        temp[c] = cur;
        if (cur == '\n') {
            temp[c] = '\0';
            break;
        }
        lastspace = 0;
        c += 1;
    }
    temp[c] = 0;
    if (lastspace == 0) {
        strcpy(st[k], temp);
        k += 1;
    }
    countsort(st, k);
    int i = 0;
    int tmp = 0;
    int s = 0;
    while (i < k) {
        tmp = strlen(st[i]);
        for (int p = 0; p < tmp; p++) {
            dest[s] = st[i][p];
            s += 1;
        }
        dest[s] = ' ';
        s += 1;
        i += 1;
    }
    dest[s - 1] = '\0';
}

int main() {
    char s[1001];
    char buff[1001];
    fgets(s, 1001, stdin);
    csort(s, buff);
    printf("%s", buff);
}