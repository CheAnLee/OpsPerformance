#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <arm_neon.h>

#define N 1000

void showM(double m[N*N]){
	for (int i=0; i<N*N; i++)
	{
		printf("%g ", m[i]);
		if (i%N == N-1)
			printf("\n");
	}
}

void matrix_multiply_double_precision_neon(float64_t  *A, float64_t  *B, float64_t *C, uint32_t n, uint32_t m, uint32_t k) {
	/* 
	 * Multiply matrices A and B, store the result in C. 
	 * It is the user's responsibility to make sure the matrices are compatible.
	 */	
	int A_idx;
	int B_idx;
	int C_idx;
	
	// these are the columns of a 4x4 sub matrix of A
	float64x2_t A0;
	float64x2_t A1;
	
	// these are the columns of a 4x4 sub matrix of B
	float64x2_t B0;
	float64x2_t B1;
	
	// these are the columns of a 4x4 sub matrix of C
	float64x2_t C0;
	float64x2_t C1;
	
	for (int i_idx=0; i_idx<n; i_idx+=2) {
		for (int j_idx=0; j_idx<m; j_idx+=2){
			// zero accumulators before matrix op
			C0=vmovq_n_f64(0);
			C1=vmovq_n_f64(0);
			for (int k_idx=0; k_idx<k; k_idx+=2){
				// compute base index to 2x2 block
				A_idx = n*i_idx + k_idx;
				B_idx = j_idx + k*k_idx;

				// load most current a values in row
				B0=vld1q_f64(B+B_idx);
				B1=vld1q_f64(B+B_idx+k);

				A0=vld1q_f64(A+A_idx);
				C0=vfmaq_laneq_f64(C0,B0,A0,0);
				C0=vfmaq_laneq_f64(C0,B1,A0,1);

				A1=vld1q_f64(A+A_idx+n);
				C1=vfmaq_laneq_f64(C1,B0,A1,0);
				C1=vfmaq_laneq_f64(C1,B1,A1,1);

				// multiply accumulate 2x1 blocks, i.e. each column C
			}
			//Compute base index for stores
			C_idx = n*i_idx + j_idx;
			vst1q_f64(C+C_idx, C0);
			vst1q_f64(C+C_idx+n,C1);
		}
	}
}

int main(int argc, char ** argv){
	double a[N*N] = {0};
	double b[N*N] = {0};
	double c[N*N] = {0};
	double c_neon[N*N] = {0};
//	double sum;
	struct timeval stime, etime;

	//printf("-> %f \n", pow(10,log10(FLT_MAX)/2));
	double MAX = pow(10,log10(DBL_MAX)/2);
	srand(time(NULL));
	for (int i=0; i<N*N; i++) {
		a[i]=(((double)rand()-RAND_MAX/2)/(RAND_MAX))*MAX;
		b[i]=(((double)rand()-RAND_MAX/2)/(RAND_MAX))*MAX;
	}

	//printf("--- a ---\n");
	//showM (a);
	//printf("--- b ---\n");
	//showM (b);

/*
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
*/

	//printf("--- c ---\n");
	//showM (c);


	gettimeofday(&stime, NULL);
	matrix_multiply_double_precision_neon(a,b,c_neon,N,N,N);
	gettimeofday(&etime, NULL);
	printf("=> %lu us\n", (etime.tv_sec-stime.tv_sec)*1000000+etime.tv_usec-stime.tv_usec);

	//printf("--- c (NEON) ---\n");
	//showM (c_neon);

	return 0;
}
