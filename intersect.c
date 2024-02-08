#include <math.h>
#include <stdio.h>

int main()
{
    int n1 = 0, n2 = 0;
    long s1 = 0, s2 = 0;
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) {
        int t;
        scanf("%d", &t);
        s1 = s1 + pow(2, t);
    }
    scanf("%d", &n2);
    for (int i = 0; i < n2; i++) {
        int t;
        scanf("%d", &t);
        s2 = s2 + pow(2, t);
    }
    long answer;
    answer = s1 & s2;
    int i = 0;
    while (answer > 0) {
        if ((answer % 2) == 1) {
            printf("%d ", i);
        }
        answer = answer / 2;
        i++;
    }
    return 0;
}