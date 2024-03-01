#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.c"
#include "unit_tests.c"
#include "recoders.c"

int menu() {
    char* st = malloc(101);
    struct String* str1 = stringinit();
    struct Tests* tests = testsinit();
    while (1) {
        printf("Выберите метод: \n1. Выбор подстроки (введите SUB)\n");
        printf("2. Перекодирование строки (введите RECODE)\n");
        printf("3. Конкатенация строк (введите CONCAT)\n");
        printf("4. Автоматическая демонстрация всех методов (введите AUTO)\n");
        printf("5. Завершить взаимодействие (введите END)\n");
        scanf("%s", st);
        if ((strcmp(st, "END") == 0) || (strcmp(st, "5") == 0)) {
            break;
        }
        else if ((strcmp(st, "SUB") == 0) || (strcmp(st, "1") == 0)) {
            printf("Введите данные в формате: \n <ваша строка> <индекс начала> <индекс конца> (в случае ошибки в индексах будет возвращена изначальная строка)\n");
            scanf("%s", st);
            int n1, n2;
            scanf("%d %d", &n1, &n2);
            struct String* str1 = stringinit();
            writeinto(str1, st);
            struct String* ans = getsub(str1, n1, n2);
            printf("Полученная строка -> %s\n", ans->str);
            stringfree(ans);
            stringfree(str1);
        }
        else if ((strcmp(st, "RECODE") == 0) || (strcmp(st, "2") == 0)) {
            printf("Алгоритм перекодировки с помощью шифра Цезаря (сдвиг +3, поддерживаются только строки из английских букв)\n");
            scanf("%s", st);
            struct String* str1 = stringinit();
            writeinto(str1, st);
            recode(str1, caesar);
            printf("Полученная строка -> %s\n", str1->str);
            stringfree(str1);
        }
        else if ((strcmp(st, "CONCAT") == 0) || (strcmp(st, "3") == 0)) {
            printf("Введите 2 строки\n");
            struct String* str1 = stringinit();
            struct String* str2 = stringinit();
            scanf("%s", st);
            writeinto(str1, st);
            scanf("%s", st);
            writeinto(str2, st);
            struct String* str3 = concat(str1, str2);
            printf("Полученная строка -> %s \n", str3->str);
            stringfree(str1);
            stringfree(str2);
            stringfree(str3);
        }
        else if ((strcmp(st, "AUTO") == 0) || (strcmp(st, "4") == 0)) {
            struct String* str1;
            str1 = stringinit();
            printf("Строка 1 инициализирована, её содержимое -> %s\n", str1->str);
            char* st = malloc(10);
            writeinto(str1, "privet");
            printf("Строка 1 перезаписана, её содержимое -> %s\n", str1->str);
            struct String* str2;
            str2 = stringinit();
            printf("Строка 2 инициализирована, её содержимое -> %s\n", str2->str);
            writeinto(str2, "poka");
            printf("Строка 2 перезаписана, её содержимое -> %s\n", str2->str);
            struct String* str3;
            str3 = concat(str1, str2);
            printf("Строка 3 созданная путём конкатенации строки 1 и 2 -> %s\n", str3->str);
            struct String* str4;
            str4 = getsub(str3, 3, 7);
            printf("Строка 4 созданная путём выделения подстроки из строки 3 с 3 по 7 символ ");
            printf("(7 не включая, индексация с нуля) -> %s\n", str4->str);
            recode(str4, caesar);
            printf("Строка 4, перекодированная шифром цезаря (смещение +3) -> %s\n", str4->str);
            stringfree(str1);
            stringfree(str2);
            stringfree(str3);
            stringfree(str4);
            printf("Использованное место в памяти было освобождено\n");
        }
        else {
            printf("Команда не распознана, повторите ввод\n");
        }
    }
    free(st);
    testsfree(tests);
    return 0;
}