#include "menu.c"


int main() {
    int k = menu();
    if (!k) {
        printf("Выполнение программы завершено");
    }
    return 0;
}
