#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Queue {
    int *data;
    int cap;
    int count;
    int head;
    int tail;
};

void queueadd(struct Queue *queue, int val) {
    queue->data[queue->tail] = val;
    queue->count += 1;
    queue->tail = (queue->tail + 1) % queue->cap;
    if (queue->count == queue->cap) {
        int* temp = malloc(queue->cap * 2 * (sizeof(int)));
        for (int i = 0; i < queue->cap; i++) {
            temp[i] = queue->data[(i + queue->head) % queue->cap];
        }
        queue->head = 0;
        queue->tail = queue->cap;
        queue->cap *= 2;
        free(queue->data);
        queue->data = temp;
    }
}

int queuedeq(struct Queue *queue) {
    int val = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->cap;
    queue->count -= 1;
    return val;
}

char* queueempty(struct Queue *queue) {
    if (queue->count == 0) {
        return "true";
    }
    return "false";
}

int main() {
    struct Queue* queue = malloc(sizeof(struct Queue));
    queue->data = malloc((sizeof(int) * 4));
    queue->cap = 4;
    queue->count = 0;
    queue->head = 0;
    queue->tail = 0;
    char word[6];
    scanf("%s", word);
    while (strcmp(word, "END") != 0) {
        if (strcmp(word, "ENQ") == 0) {
            int n;
            scanf("%d", &n);
            queueadd(queue, n);
        };
        if (strcmp(word, "DEQ") == 0) {
            printf("%d\n", queuedeq(queue));
        }
        if (strcmp(word, "EMPTY") == 0) {
            printf("%s\n", queueempty(queue));
        }
        //printf("%d %d %d %d %d %d %d %d %d %d\n", queue->data[0], queue->data[1], queue->data[2], queue->data[3],
        //queue->data[4], queue->data[5], queue->data[6], queue->data[7], queue->head, queue->tail);
        scanf("%s", word);
    }
    free(queue->data);
    free(queue);
}