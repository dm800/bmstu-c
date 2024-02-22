#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

struct Elem {
    struct Elem *next;
    char *word;
};

void insertafter(struct Elem* a, struct Elem* b) {
    struct Elem* temp = a->next;
    a->next = b;
    b->next = temp;
}

void listfree(struct Elem* list) {
    struct Elem* cur = list;
    while (cur->next != NULL) {
        struct Elem* temp = cur;
        cur = cur->next;
        free(temp->word);
        free(temp);
    }
    free(cur->word);
    free(cur);
}


struct Elem *bsort(struct Elem* list) {
    if (list != NULL) {
        struct Elem* helper = malloc(sizeof(struct Elem));
        helper->next = list;
        struct Elem* lastsorted = NULL;
        /*struct Elem* printer = helper;
        while (printer->next != NULL) {
            printf("%s ", printer->word);
            printer = printer->next;
        }
        printf("%s\n", printer->word);*/
        while (lastsorted != helper->next) {
            struct Elem* cur = helper;
            struct Elem* elem1 = cur->next;
            struct Elem* elem2 = elem1->next;
            while (elem2 != lastsorted) {
                if (((int)strlen(elem1->word) - (int)strlen(elem2->word)) > 0) {
                    cur->next = elem2;
                    elem1->next = elem2->next;
                    elem2->next = elem1;
                }
                cur = cur->next;
                elem1 = cur->next;
                elem2 = elem1->next;
            }
            lastsorted = elem1;
        }
        struct Elem* answer = helper->next;
        free(helper);
        return answer;
    }
    return list;
}

int main() {
    struct Elem* list = malloc(sizeof(struct Elem));
    list->word = (char*)'\0';
    list->next = NULL;
    char sent[1001];
    fgets(sent, 1001, stdin);
    int lastspace = 1;
    char temp[1001];
    int t = 0;
    int c = 0;
    char wordlist[1001][1001];
    for (int i = 0; i < strlen(sent); i++) {
        char cur = sent[i];
        if ((cur == ' ') && (lastspace == 0)) {
            temp[t] = '\0';
            temp[t + 1] = '\0';
            strcpy(wordlist[c], temp);
            t = 0;
            lastspace = 1;
            c += 1;
            
        }
        else if (cur == ' ') {
            lastspace = 1;
        }
        else if (cur == '\n') {
            break;
        }
        else {
            lastspace = 0;
            temp[t] = cur;
            t += 1;
        }
    }
    if (t != 0) {
        temp[t] = '\0';
        strcpy(wordlist[c], temp);
        c += 1;
    }
    for (int i = c; i > 0; i--) {
        struct Elem* new = malloc(sizeof(struct Elem));
        new->word = calloc(strlen(wordlist[i - 1]) + 2, sizeof(char));
        strcpy(new->word, wordlist[i - 1]);
        insertafter(list, new);
    }
    struct Elem* work = list->next;
    free(list);
    if (c > 1) {work = bsort(work);}
    struct Elem* cur = work;
    while (cur->next != NULL) {
        printf("%s ", cur->word);
        cur = cur->next;
    }
    printf("%s \n", cur->word);
    listfree(work);
}