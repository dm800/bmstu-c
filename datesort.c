#include <stdio.h>
#include <stdlib.h>

struct Date {
    int Day, Month, Year;
};

int daykey(struct Date elem) {
    int temp = elem.Day;
    return temp - 1;
}

int monthkey(struct Date elem) {
    return elem.Month - 1;
}

int yearkey(struct Date elem) {
    return elem.Year - 1970;
}

void distribsort(struct Date *in, size_t nel, size_t n, int (*key)(struct Date elem), struct Date *dest) {
    int count[n];
    for (int i = 0; i < n; i++) {
        count[i] = 0;
    }
    int j = 0;
    while (j < nel) {
        int k = key(in[j]);
        count[k] += 1;
        j++;
    }
    int i = 1;
    while (i < n) {
        count[i] += count[i - 1];
        i++;
    }
    int s = 0;
    j = nel - 1;
    while (j >= 0) {
        int k = key(in[j]);
        s = count[k] - 1;
        count[k] = s;
        dest[s] = in[j];
        j--;
    }
    
}

void datesort(struct Date *in, size_t nel, struct Date *dest) {
    // days
    for (int i = 0; i < nel; i++) {
        dest[i] = in[i];
    }
    struct Date temp[nel];
    distribsort(dest, nel, 31, daykey, temp);
    for (int i = 0; i < nel; i++) {
        dest[i] = temp[i];
    }
    // months
    distribsort(dest, nel, 12, monthkey, temp);
    for (int i = 0; i < nel; i++) {
        dest[i] = temp[i];
    }
    // years
    distribsort(dest, nel, 61, yearkey, temp);
    for (int i = 0; i < nel; i++) {
        dest[i] = temp[i];
    }
}

int main()
{
  int n = 0;
  scanf("%d", &n);
  struct Date arr[n]; 
  struct Date ans[n]; 
  for (int i = 0; i < n; i++) {
      scanf("%d", &arr[i].Year);
      scanf("%d", &arr[i].Month);
      scanf("%d", &arr[i].Day);
  }
  datesort(arr, n, ans);
  for (int i = 0; i < n; i++) {
      printf("%04d %02d %02d \n", ans[i].Year, ans[i].Month, ans[i].Day);
  }
}