#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.c"
#include "recoders.c"


struct Test {
    char* in;
    char* out;
    char* function;
};

struct Tests {
    struct Test** list;
    int count;
    int cap;
};


void testfree(struct Test* test) {
    free(test->in);
    free(test->out);
    free(test->function);
    free(test);
}

void testsfree(struct Tests* tests) {
    for (int i = 0; i < tests->count; i++) {
        testfree(tests->list[i]);
    }
    free(tests->list);
    free(tests);
}


struct Test* maketest(char* in, char* out, char* func) {
    struct Test* test = malloc(sizeof(struct Test));
    test->in = malloc(strlen(in) + 1);
    strcpy(test->in, in);
    test->out = malloc(strlen(out) + 1);
    strcpy(test->out, out);
    test->function = malloc(strlen(func) + 1);
    strcpy(test->function, func);
    return test;
}

struct Tests* testsinit() {
    struct Tests* tests = malloc(sizeof(struct Tests));
    tests->count = 9;
    tests->cap = 10;
    tests->list = malloc(sizeof(struct Test*) * tests->cap);
    tests->list[0] = maketest("abcdef 3 5", "de", "SUB");
    tests->list[1] = maketest("abcdef 4 4", "", "SUB");
    tests->list[2] = maketest("abcdef 5 4", "abcdef", "SUB");
    tests->list[3] = maketest("abcdef 0 10", "abcdef", "SUB");
    tests->list[4] = maketest("abcdef -2 4", "abcdef", "SUB");
    tests->list[5] = maketest("abcdef", "defghi", "RECODE");
    tests->list[6] = maketest("xyz", "abc", "RECODE");
    tests->list[7] = maketest("abc def", "abcdef", "CONCAT");
    tests->list[8] = maketest("123 456", "123456", "CONCAT");
    return tests;
}

void testsextend(struct Tests* tests) {
    tests->cap *= 2;
    struct Test** list = malloc(sizeof(struct Test*) * tests->cap);
    for (int i = 0; i < tests->count; i++) {
        list[i] = tests->list[i];
    }
    free(tests->list);
    tests->list = list;
}

void testsadd(struct Tests* tests, struct Test* test) {
    if (tests->count < tests->cap) {
        tests->list[tests->count] = test;
        tests->count += 1;
    }
    else {
        testsextend(tests);
        testsadd(tests, test);
    }
}

char** split(char* str, char* del) {
    char** tokens = malloc(sizeof(char*) * 3);
    char* istr = strtok(str, " ");
    int i = 0;
    while (istr != NULL) {
        tokens[i] = istr;
        i += 1;
        istr = strtok(NULL, " ");
    }
    return tokens;
}

struct String* testsub(struct Test* test) {
    struct String* str1 = stringinit();
    char** tokens = split(test->in, " ");
    writeinto(str1, tokens[0]);
    struct String* str2 = getsub(str1, atoi(tokens[1]), atoi(tokens[2]));
    free(tokens);
    return str2;
}

struct String* testrecode(struct Test* test) {
    struct String* str1 = stringinit();
    writeinto(str1, test->in);
    recode(str1, caesar);
    return str1;
}

struct String* testconcat(struct Test* test) {
    struct String* str1 = stringinit();
    struct String* str2 = stringinit();
    char** tokens = split(test->in, " ");
    writeinto(str1, tokens[0]);
    writeinto(str2, tokens[1]);
    struct String* str3 = stringinit();
    str3 = concat(str1, str2);
    stringfree(str1);
    stringfree(str2);
    free(tokens);
    return str3;
}

struct String* checktest(struct Test* test) {
    if (strcmp(test->function, "SUB") == 0) {
        return testsub(test);
    }
    else if (strcmp(test->function, "RECODE") == 0) {
        return testrecode(test);
    }
    else if (strcmp(test->function, "CONCAT") == 0) {
        return testconcat(test);
    }
}

void completetests(struct Tests* tests) {
    int failed = 0;
    for (int i = 0; i < tests->count; i++) {
        printf("Проверяем тест {%s} на функции %s, ожидаемый вывод: {%s}\t\t\t", tests->list[i]->in, tests->list[i]->function, tests->list[i]->out);
        struct String* ans = checktest(tests->list[i]);
        if (strcmp(ans->str, tests->list[i]->out) == 0) {
            printf("OK\n");
        }
        else {
            printf("FAIL\nОжидаемое значение: %s\nПолученное значение: %s\n", tests->list[i]->out, ans->str);
            failed += 1;
        }
        stringfree(ans);
    }
    if (failed == 0) {
        printf("Все тесты пройдены успешно\n");
    }
    else {
        printf("Количество тестов, завершившихся неправильным ответом: %d\n", failed);
    }
}

int main() {
    struct Tests* tests = testsinit();
    char* n;
    while (strcmp(n, "1") != 0) {
        printf("Тесты инициализированы.\n");
        printf("1. Запустить существующие\n");
        printf("2. Добавить новый\n");
        scanf("%s", n);
        if (strcmp(n, "2") == 0) {
            printf("Введите название функции, которую необходимо проверить (SUB, CONCAT или RECODE)\n");
            scanf("%s", n);
            if (strcmp(n, "SUB") == 0) {
                printf("Введите желаемую строку и индексы\n");
                char* in = malloc(101);
                char* st1 = malloc(101);
                char* st2 = malloc(101);
                scanf("%s %s %s", in, st1, st2);
                strcat(in, " ");
                strcat(in, st1);
                strcat(in, " ");
                strcat(in, st2);
                printf("Введите желаемый вывод для программы\n");
                char* out = malloc(101);
                scanf("%s", out);
                struct Test* test = maketest(in, out, "SUB");
                testsadd(tests, test);
                free(in);
                free(st1);
                free(st2);
                free(out);
            }
            else if (strcmp(n, "CONCAT") == 0) {
                printf("Введите обе строки\n");
                char* st1 = malloc(101);
                char* st2 = malloc(101);
                scanf("%s %s", st1, st2);
                strcat(st1, " ");
                strcat(st1, st2);
                printf("Введите желаемый вывод для программы\n");
                char* out = malloc(101);
                scanf("%s", out);
                struct Test* test = maketest(st1, out, "CONCAT");
                testsadd(tests, test);
                free(st1);
                free(st2);
                free(out);
            }
            else if (strcmp(n, "RECODE") == 0) {
                printf("Введите строку\n");
                char* st1 = malloc(101);
                scanf("%s", st1);
                printf("Введите желаемый вывод для программы\n");
                char* out = malloc(101);
                scanf("%s", out);
                struct Test* test = maketest(st1, out, "RECODE");
                testsadd(tests, test);
                free(st1);
                free(out);
            }
            else {
                printf("Название теста не распознано\n");
            }
        }
        else if (strcmp(n, "1") != 0) {
            printf("Команда не распознана\n");
        }
    }
    completetests(tests);
}