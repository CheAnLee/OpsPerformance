#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <float.h>
#include <math.h>

#define N 1000

/*
void showM(float m[N*N]){
	for (int i=0; i<N*N; i++)
	{
		printf("%g ", m[i]);
		if (i%N == N-1)
			printf("\n");
	}
}
*/

int main(int argc, char ** argv){
	float a[N*N] = {0};
	float b[N*N] = {0};
	float c[N*N] = {0};
	float sum;

	//printf("-> %f \n", pow(10,log10(FLT_MAX)/2));
	float MAX = pow(10,log10(FLT_MAX)/2);
	srand(time(NULL));
	for (int i=0; i<N*N; i++) {
		a[i]=(((float)rand()-RAND_MAX/2)/(RAND_MAX))*MAX;
		b[i]=(((float)rand()-RAND_MAX/2)/(RAND_MAX))*MAX;
	}

	struct timeval stime, etime;
	gettimeofday(&stime, NULL);
	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < N; k++)
		{
 			sum = 0;

			for (int j = 0; j < N; j++)
 			{
				sum += a[i*N+j] * b[j*N + k];
 			}

 			// Product matrix elements are calculated and stored into array c.
 			c[i*N + k] = sum;					
 		}
	}
	gettimeofday(&etime, NULL);
	printf("=> %lu us\n", (etime.tv_sec-stime.tv_sec)*1000000+etime.tv_usec-stime.tv_usec);

	//printf("--- a ---\n");
	//showM (a);
	//printf("--- b ---\n");
//	showM (b);
//	printf("--- c ---\n");
//	showM (c);

	return 0;
}
