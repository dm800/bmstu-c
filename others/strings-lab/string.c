#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct String {
    char* str;
    int len;
};

struct String* stringinit() {
    struct String* str = malloc(sizeof(struct String));
    str->len = 0;
    str->str = "";
    return str;
}

void writeinto(struct String* dest, char* text) {
    int len = strlen(text);
    if (len > dest->len) {
        dest->str = malloc(len + 1);
    }
    dest->len = len;
    if (len == 0) {
        dest->str = "";
    }
    else {
        strcpy(dest->str, text);
    }
}

struct String* concat(struct String* str1, struct String* str2) {
    struct String* temp = stringinit();
    int len1 = str1->len;
    int len2 = str2->len;
    temp->len = len1 + len2;
    temp->str = malloc(len1 + len2 + 1);
    strcpy(temp->str, str1->str);
    strcat(temp->str, str2->str);
    return temp;
}

struct String* getsub(struct String* str, int i, int j) {
    char* temp = malloc(j - i + 1);
    if ((i > str->len) || (i < 0) || (j > str->len) || (j < 0)) {
        return str;
    }
    else if (i > j) {
        return str;
    }
    for (int k = i; k < j; k++) {
        temp[k - i] = str->str[k];
    }
    temp[j - i] = '\0';
    struct String* ans = stringinit();
    writeinto(ans, temp);
    free(temp);
    return ans;
}

void recode(struct String* str, char (*codefunc)(char a)) {
    for (int k = 0; k < str->len; k++) {
        str->str[k] = codefunc(str->str[k]);
    }
}


void stringfree(struct String* str1) {
    if (str1->len != 0) {
        free(str1->str);
    }
    free(str1);
}