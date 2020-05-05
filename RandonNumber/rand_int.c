#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

#define N 1000

int main (int argc, char ** argv) {
	srand(time(NULL));

	for (int i=0; i<N; i++) {
		long rnum = ((long)rand()-RAND_MAX/2)*(((long)INT_MAX-INT_MIN)/(RAND_MAX));
		printf("rand: %li\n", rnum);
	}

	return 0;
}
