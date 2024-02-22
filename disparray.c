#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Elem {
    struct Elem *next;
    int key;
    int value;
};

struct Table {
    struct Elem** data;
    int size;
};


void tablefree(struct Table* table) {
    for (int i = 0; i < table->size; i++) {
        struct Elem* cur = table->data[i];
        while (cur != NULL) {
            // printf("%d %d is CLEARED\n", cur->key, cur->value);
            struct Elem* temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
    free(table->data);
    free(table);
}

struct Table* inittable(int size) {
    struct Table* result = malloc(sizeof(struct Table));
    struct Elem** data = calloc(size, sizeof(struct Elem));
    result->size = size;
    result->data = data;
    return result;
}

/*void printall(struct Table* table) {
    struct Elem* cur = table->next;
    while (cur != NULL) {
        printf("%d: %d\n", cur->key, cur->value);
        cur = cur->next;
    }
} */

int hasher(struct Table* table, int key) {
    return key % table->size;
}

int COMAT(struct Table* table, int key, int hashfunc(struct Table* table, int key)) {
    int h = hasher(table, key);
    struct Elem* cur = table->data[h];
    while (cur != NULL) {
        if (cur->key == key) {
            return cur->value;
        }
        cur = cur->next;
    }
    return 0;
}

struct Elem* generateelem(struct Table* table, int key, int value) {
    struct Elem* new = malloc(sizeof(struct Elem));
    new->key = key;
    new->value = value;
    new->next = NULL;
    return new;
}

void COMASSIGN(struct Table* table, int key, int value, int hashfunc(struct Table* table, int key)) {
    int h = hashfunc(table, key);
    struct Elem* cur = table->data[h];
    if (cur == NULL) {
        if (value != 0) {
            table->data[h] = generateelem(table, key, value);
        }
        return;
    }
    if (cur->key == key) {
        if (value == 0) {
            table->data[h] = cur->next;
            free(cur);
        }
        else {
            cur->value = value;
        }
        return;
    }
    else {
        struct Elem* prev = cur;
        cur = cur->next;
        while (cur != NULL) {
            if (cur->key == key) {
                if (value == 0) {
                    cur = cur->next;
                    free(prev->next);
                    prev->next = cur;
                }
                else {
                    cur->value = value;
                }
                return;
            }
            prev = cur;
            cur = cur->next;
        }
        if (value != 0) {
            prev->next = generateelem(table, key, value);
        }
    }
}


int main() {
    int m;
    scanf("%d", &m);
    struct Table* table = inittable(m);
    char word[7];
    scanf("%s", word);
    while (strcmp(word, "END") != 0) {
        if (strcmp(word, "AT") == 0) {
            int key;
            scanf("%d", &key);
            printf("%d\n", COMAT(table, key, hasher));
        }
        if (strcmp(word, "ASSIGN") == 0) {
            int key;
            int value;
            scanf("%d %d", &key, &value);
            COMASSIGN(table, key, value, hasher);
        }
        // printall(table);
        scanf("%s", word);
    }
    tablefree(table);
}