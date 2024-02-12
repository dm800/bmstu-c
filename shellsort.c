void shellsort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j))
{
	unsigned long n1 = 1, n2 = 1, n3 = 2;
	while (n3 < nel) {
		n1 = n2;
		n2 = n3;
		n3 = n2 + n1;
	}
	long step = n2;
	long i = 0;
	long loc = 0;
	while (step >= 1) {
		step = n2;
		i = step;
		while (i < nel) {
			loc = i - step;
			while ((loc >= 0) && (compare(loc + step, loc) < 0)) {
				swap(loc + step, loc);
				loc -= step;
			}
			i += 1;
		}
		n3 = n2;
		n2 = n1;
		n1 = n3 - n2;
	}
}