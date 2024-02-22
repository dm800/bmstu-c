#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Elem {
    int index;
    int key;
    int cap;
    int* values;
    int current;
};

int comparsion(int a, int b) {
    return b - a;
}



struct Queue {
    struct Elem* *heap;
    int cap;
    int count;
};

void heapify(int (*compare)(int a, int b), int i, int n, struct Queue* base) {
    while (1) {
        int l = 2 * i + 1;
        int r = l + 1;
        int j = i;
        if ((l < n) && (compare(base->heap[i]->key, base->heap[l]->key) < 0)) {
            i = l;
        }
        if ((r < n) && (compare(base->heap[i]->key, base->heap[r]->key) < 0)) {
            i = r;
        }
        if (i == j) {
            break;
        }
        struct Elem* temp = base->heap[i];
        base->heap[i] = base->heap[j];
        base->heap[j] = temp;
        base->heap[i]->index = i;
        base->heap[j]->index = j;
    }
}

struct Queue* initqueue(int size) {
    struct Queue* queue = malloc(sizeof(struct Queue));
    queue->cap = size;
    queue->count = 0;
    queue->heap = calloc(size, sizeof(struct Elem));
}

void queprint(struct Queue* q) {
    int size = q->count;
    for (int i = 0; i < size; i++) {
        struct Elem* cur = q->heap[i];
        printf("(%d %d [", cur->index, cur->key);
        for (int k = cur->current; k < cur->cap; k++) {
            printf("%d ", cur->values[k]);
        }
        printf("])\n");
    }
}


void queinsert(struct Queue* q, struct Elem* ptr) {
    int i = q->count;
    q->count = i + 1;
    q->heap[i] = ptr;
    while ((i > 0) && (comparsion(q->heap[(i - 1) / 2]->key, q->heap[i]->key) < 0)) {
        struct Elem* temp = q->heap[(i - 1) / 2];
        q->heap[(i - 1) / 2] = q->heap[i];
        q->heap[i] = temp;
        q->heap[i]->index = i;
        i = (i - 1) / 2;
    }
    q->heap[i]->index = i;
}

void increasekey(struct Queue* q, struct Elem* max) {
    max->current += 1;
    max->key = max->values[max->current];
    heapify(comparsion, 0, q->count, q);
}

void elemfree(struct Elem *a) {
    free(a->values);
    free(a);
}

void quedeletemax(struct Queue* q) {
    q->count = q->count - 1;
    elemfree(q->heap[0]);
    if (q->count > 0) {
        q->heap[0] = q->heap[q->count];
        q->heap[0]->index = 0;
        heapify(comparsion, 0, q->count, q);
    }
}

void printans(struct Queue* q) {
    while (q->count > 0) {
        struct Elem* max = q->heap[0];
        printf("%d ", max->key);
        if (max->current == max->cap - 1) {
            quedeletemax(q);
        }
        else {
            increasekey(q, max);
        }
    }
}

void quefree(struct Queue *q) {
    free(q->heap);
    free(q);
}

int main() {
    int n;
    scanf("%d", &n);
    struct Queue* q = initqueue(n);
    int counters[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &counters[i]);
    }
    for (int i = 0; i < n; i++) {
        struct Elem* cur = malloc(sizeof(struct Elem));
        cur->current = 0;
        cur->values = calloc(counters[i], sizeof(int));
        cur->cap = counters[i];
        for (int k = 0; k < counters[i]; k++) {
            scanf("%d", &cur->values[k]);
        }
        cur->key = cur->values[0];
        queinsert(q, cur);
    }
    // queprint(q);
    printans(q);
    quefree(q);
}