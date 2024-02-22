#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct Elem {
    struct Elem *prev, *next;
    int v;
};

void insertafter(struct Elem* a, struct Elem* b) {
    struct Elem* temp = a->next;
    a->next = b;
    b->prev = a;
    b->next = temp;
    temp->prev = b;
}

void listfree(struct Elem* list) {
    struct Elem* cur = list->next;
    while (cur->v != INT_MAX) {
        struct Elem* temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(list);
}

void sorting(struct Elem* list) {
    struct Elem* lastsorted = list->next;
    struct Elem* checking = lastsorted->next;
    while (lastsorted->next->v != list->v) {
        struct Elem* cur = lastsorted;
        while ((cur->v != list->v) && (checking->v < cur->v)) {
            cur = cur->prev;
        }
        lastsorted->next = checking->next;
        checking->prev = lastsorted;
        insertafter(cur, checking);
        if (cur == lastsorted) {
            lastsorted = lastsorted->next;
        }
        checking = lastsorted->next;
        struct Elem* temp = list->next;
        /*while (temp->v != list->v) {
            printf("%d ", cur->v);
            temp = temp->next;
        }
        printf("\n"); */
    }
}

int main() {
    struct Elem* list = malloc(sizeof(struct Elem));
    list->v = INT_MAX;
    list->prev = list;
    list->next = list;
    int n;
    scanf("%d", &n);
    int t;
    for (int i = 0; i < n; i++) {
        scanf("%d", &t);
        struct Elem* new = malloc(sizeof(struct Elem));
        new->v = t;
        insertafter(list, new);
    }
    sorting(list);
    struct Elem* cur = list->next;
    while (cur->v != list->v) {
        printf("%d ", cur->v);
        cur = cur->next;
    }
    listfree(list);
}