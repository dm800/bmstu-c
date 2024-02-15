#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Task {
    int low, high;
};

struct Stack {
    int cap;
    int top;
    struct Task *data;
};

void swap(int ind1, int ind2, long *in) {
    long temp = in[ind1];
    in[ind1] = in[ind2];
    in[ind2] = temp;
}

int partition(int low, int high, long *in) {
    int i = low;
    int j = low;
    while (j < high) {
        if (in[j] <= in[high]) {
            swap(i, j, in);
            i++;
        }
        j++;
    }
    swap(i, high, in);
    return i;
}


void sorting(long *in, int low, int high, int m) {
    if (low < high) {
        int q = partition(low, high, in);
        sorting(in, low, q - 1, m);
        sorting(in, q + 1, high, m);
    }
}

struct Stack* stackinit(int size) {
    struct Stack *stack = malloc(sizeof(struct Stack));;
    stack->cap = size;
    stack->top = 0;
    stack->data = malloc(sizeof(struct Task) * size);
    return stack;
}

void stackappend(struct Stack *stack, struct Task elem) {
    stack->data[stack->top] = elem;
    stack->top = stack->top + 1;
}

struct Task stackpop(struct Stack *stack) {
    stack->top = stack->top - 1;
    return stack->data[stack->top];
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    long arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%ld", &arr[i]);
    }
    struct Stack *tasks;
    tasks = stackinit(n);
    struct Task task;
    task.low = 0;
    task.high = n - 1;
    stackappend(tasks, task);
    while (tasks->top != 0) {
        struct Task current = stackpop(tasks);
        int q = partition(current.low, current.high, arr);
        struct Task task1;
        task1.low = current.low;
        task1.high = q - 1;
        struct Task task2;
        task2.low = q + 1;
        task2.high = current.high;
        if (task1.low < task1.high) {
            stackappend(tasks, task1);
        }
        if (task2.low < task2.high) {
            stackappend(tasks, task2);
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%ld ", arr[i]);
    }
    free(tasks->data);
    free(tasks);
}