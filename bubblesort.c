void bubblesort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j))
{
    unsigned long c = 1;
    unsigned long i;
    unsigned long iterations = 0;
    if (nel >= 2) {
        while (c != 0) {
            c = 0;
            for (i = iterations; i < nel - 1 - iterations; i++) {
                if (compare(i, i + 1) == 1) {
                    swap(i, i + 1);
                    c += 1;
                }
            }
            if (c == 0) {
                break;
            }
            c = 0;
            for (i = nel - 1; i > iterations; i--) {
                if (compare(i, i - 1) == -1) {
                    swap(i, i - 1);
                    c += 1;
                }
            }
            if (c == 0) {
                break;
            }
            iterations += 1;
        }
    }
}