#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
    int top;
    int cap;
    int *value;
};

void stackadd(struct Stack *stack, int val) {
    if (stack->cap == stack->top){
        int *newval = malloc(((int)(stack->cap * 2 + 1)) * sizeof(int));
        for (int i = 0; i < stack->cap; i++) {
            newval[i] = stack->value[i];
        }
        stack->cap = stack->cap * 2 + 1;
        free(stack->value);
        stack->value = newval;
    }
    stack->value[stack->top] = val;
    stack->top += 1;
}

void comadd(struct Stack *stack) {
    stack->top -= 1;
    stack->value[stack->top - 1] = stack->value[stack->top] + stack->value[stack->top - 1];
}

void comsub(struct Stack *stack) {
    stack->top -= 1;
    stack->value[stack->top - 1] = stack->value[stack->top] - stack->value[stack->top - 1];
}

void commul(struct Stack *stack) {
    stack->top -= 1;
    stack->value[stack->top - 1] = stack->value[stack->top] * stack->value[stack->top - 1];
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

void comdiv(struct Stack *stack) {
    stack->top -= 1;
    stack->value[stack->top - 1] = stack->value[stack->top] / stack->value[stack->top - 1];
}

void commax(struct Stack *stack) {
    stack->top -= 1;
    stack->value[stack->top - 1] = max(stack->value[stack->top], stack->value[stack->top - 1]);
}

void commin(struct Stack *stack) {
    stack->top -= 1;
    stack->value[stack->top - 1] = stack->value[stack->top] + stack->value[stack->top - 1] - 
    max(stack->value[stack->top], stack->value[stack->top - 1]);
}

void comneg(struct Stack *stack) {
    stack->value[stack->top - 1] = -stack->value[stack->top - 1];
}

void comdup(struct Stack *stack) {
    stackadd(stack, stack->value[stack->top - 1]);
}

void comswap(struct Stack *stack) {
    int temp = stack->value[stack->top - 1];
    stack->value[stack->top - 1] = stack->value[stack->top - 2];
    stack->value[stack->top - 2] = temp;
}

int main() {
    struct Stack *workplace = malloc(sizeof(struct Stack));
    workplace->top = 0;
    workplace->cap = 1;
    workplace->value = malloc(10 * sizeof(int));
    char word[6];
    scanf("%s", word);
    while (strcmp(word, "END") != 0) {
        if (strcmp(word, "CONST") == 0) {
            int n;
            scanf("%d", &n);
            stackadd(workplace, n);
        };
        if (strcmp(word, "ADD") == 0) {
            comadd(workplace);
        }
        if (strcmp(word, "SUB") == 0) {
            comsub(workplace);
        }
        if (strcmp(word, "MUL") == 0) {
            commul(workplace);
        }
        if (strcmp(word, "DIV") == 0) {
            comdiv(workplace);
        }
        if (strcmp(word, "MAX") == 0) {
            commax(workplace);
        }
        if (strcmp(word, "MIN") == 0) {
            commin(workplace);
        }
        if (strcmp(word, "NEG") == 0) {
            comneg(workplace);
        }
        if (strcmp(word, "DUP") == 0) {
            comdup(workplace);
        }
        if (strcmp(word, "SWAP") == 0) {
            comswap(workplace);
        }
        scanf("%s", word);
    }
    printf("%d", workplace->value[0]);
    free(workplace->value);
    free(workplace);
}