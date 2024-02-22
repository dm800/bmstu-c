#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dqueue {
    int* data;
    int* mstack;
    int cap;
    int top1;
    int top2;
};

struct Dqueue* queinit(int n) {
    int* values = calloc(n, sizeof(int));
    int* mvalues = calloc(n, sizeof(int));
    struct Dqueue* pointer = malloc(sizeof(struct Dqueue));
    pointer->data = values;
    pointer->mstack = mvalues;
    pointer->cap = n;
    pointer->top1 = 0;
    pointer->top2 = n - 1;
    return pointer;
}

int queempty(struct Dqueue* queue) {
    if ((queue->top1 == 0) && (queue->top2 == queue->cap - 1)) {
        return 1;
    }
    return 0;
}

void queincrease(struct Dqueue* queue) {
    int* new = calloc(queue->cap * 2, sizeof(int));
    int* newm = calloc(queue->cap * 2, sizeof(int));
    for (int i = queue->top2 + 1; i < queue->cap; i++) {
        new[queue->cap + i] = queue->data[i];
        newm[queue->cap + i] = queue->mstack[i];
    }
    for (int i = 0; i < queue->top1; i++) {
        new[i] = queue->data[i];
        newm[i] = queue->mstack[i];
    }
    free(queue->data);
    free(queue->mstack);
    queue->top2 += queue->cap;
    queue->cap *= 2;
    queue->data = new;
    queue->mstack = newm;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

void queenq(struct Dqueue* queue, int value) {
    if (queue->top2 < queue->top1) {
        queincrease(queue);
    }
    if (queue->top1 == 0) {
        queue->mstack[queue->top1] = value;
    }
    else {
        queue->mstack[queue->top1] = max(queue->mstack[queue->top1 - 1], value);
    }
    queue->data[queue->top1] = value;
    queue->top1 += 1;
}

int quemax(struct Dqueue* queue) {
    if (queue->top1 == 0) {
        return queue->mstack[queue->top2 + 1];
    }
    else if (queue->top2 == queue->cap - 1) {
        return queue->mstack[queue->top1 - 1];
    }
    else {
        return max(queue->mstack[queue->top1 - 1], queue->mstack[queue->top2 + 1]);
    }
}

int quedeq(struct Dqueue* queue) {
    if (queue->top2 == queue->cap - 1) {
        while (queue->top1 != 0) {
            queue->top1 -= 1;
            if (queue->top2 == queue->cap - 1) {
                queue->mstack[queue->top2] = queue->data[queue->top1];
            }
            else {
                queue->mstack[queue->top2] = max(queue->data[queue->top1], queue->mstack[queue->top2 + 1]);
            }
            queue->data[queue->top2] = queue->data[queue->top1];
            queue->top2 -= 1;
        }
    }
    queue->top2 += 1;
    int val = queue->data[queue->top2];
    return val;
}

int main() {
    struct Dqueue* que = queinit(8);
    char word[6];
    scanf("%s", word);
    while (strcmp(word, "END") != 0) {
        if (strcmp(word, "ENQ") == 0) {
            int n;
            scanf("%d", &n);
            queenq(que, n);
        }
        if (strcmp(word, "DEQ") == 0) {
            printf("%d\n", quedeq(que));
        }
        if (strcmp(word, "MAX") == 0) {
            printf("%d\n", quemax(que));
        }
        if (strcmp(word, "EMPTY") == 0) {
            if (queempty(que) == 1) {
                printf("true\n");
            }
            else {
                printf("false\n");
            }
        }
        /* for (int i = 0; i < que->cap; i++) {
            printf("%d ", que->data[i]);
        }
        printf("\n");
        for (int i = 0; i < que->cap; i++) {
            printf("%d ", que->mstack[i]);
        }
        printf("\n"); */
        scanf("%s", word);
    }
    free(que->mstack);
    free(que->data);
    free(que);
    return 0;
}