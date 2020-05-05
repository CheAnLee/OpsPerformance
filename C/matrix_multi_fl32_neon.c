#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <arm_neon.h>

#define N 1500

void showM(float m[N*N]){
	for (int i=0; i<N*N; i++)
	{
		printf("%g ", m[i]);
		if (i%N == N-1)
			printf("\n");
	}
}

void matrix_multiply_neon(float32_t  *A, float32_t  *B, float32_t *C, uint32_t n, uint32_t m, uint32_t k) {
	/* 
	 * Multiply matrices A and B, store the result in C. 
	 * It is the user's responsibility to make sure the matrices are compatible.
	 */	
	int A_idx;
	int B_idx;
	int C_idx;
	
	// these are the columns of a 4x4 sub matrix of A
	float32x4_t A0;
	float32x4_t A1;
	float32x4_t A2;
	float32x4_t A3;
	
	// these are the columns of a 4x4 sub matrix of B
	float32x4_t B0;
	float32x4_t B1;
	float32x4_t B2;
	float32x4_t B3;
	
	// these are the columns of a 4x4 sub matrix of C
	float32x4_t C0;
	float32x4_t C1;
	float32x4_t C2;
	float32x4_t C3;
	
	for (int i_idx=0; i_idx<n; i_idx+=4) {
		for (int j_idx=0; j_idx<m; j_idx+=4){
			// zero accumulators before matrix op
			C0=vmovq_n_f32(0);
			C1=vmovq_n_f32(0);
			C2=vmovq_n_f32(0); 
			C3=vmovq_n_f32(0);
			for (int k_idx=0; k_idx<k; k_idx+=4){
				// compute base index to 4x4 block
				A_idx = n*i_idx + k_idx;
				B_idx = j_idx + k*k_idx;

				// load most current a values in row
				B0=vld1q_f32(B+B_idx);
				B1=vld1q_f32(B+B_idx+k);
				B2=vld1q_f32(B+B_idx+2*k);
				B3=vld1q_f32(B+B_idx+3*k);

				A0=vld1q_f32(A+A_idx);
				C0=vfmaq_laneq_f32(C0,B0,A0,0);
				C0=vfmaq_laneq_f32(C0,B1,A0,1);
				C0=vfmaq_laneq_f32(C0,B2,A0,2);
				C0=vfmaq_laneq_f32(C0,B3,A0,3);

				A1=vld1q_f32(A+A_idx+n);
				C1=vfmaq_laneq_f32(C1,B0,A1,0);
				C1=vfmaq_laneq_f32(C1,B1,A1,1);
				C1=vfmaq_laneq_f32(C1,B2,A1,2);
				C1=vfmaq_laneq_f32(C1,B3,A1,3);

				A2=vld1q_f32(A+A_idx+2*n);
				C2=vfmaq_laneq_f32(C2,B0,A2,0);
				C2=vfmaq_laneq_f32(C2,B1,A2,1);
				C2=vfmaq_laneq_f32(C2,B2,A2,2);
				C2=vfmaq_laneq_f32(C2,B3,A2,3);

				A3=vld1q_f32(A+A_idx+3*n);
				C3=vfmaq_laneq_f32(C3,B0,A3,0);
				C3=vfmaq_laneq_f32(C3,B1,A3,1);
				C3=vfmaq_laneq_f32(C3,B2,A3,2);
				C3=vfmaq_laneq_f32(C3,B3,A3,3);

				// multiply accumulate 4x1 blocks, i.e. each column C
			}
			//Compute base index for stores
			C_idx = n*i_idx + j_idx;
			vst1q_f32(C+C_idx, C0);
			vst1q_f32(C+C_idx+n,C1);
			vst1q_f32(C+C_idx+2*n,C2);
			vst1q_f32(C+C_idx+3*n,C3);
		}
	}
}

int main(int argc, char ** argv){
	float a[N*N] = {0};
	float b[N*N] = {0};
	float c[N*N] = {0};
//	float sum;

	//printf("-> %f \n", pow(10,log10(FLT_MAX)/2));
	float MAX = pow(10,log10(FLT_MAX)/2);
	srand(time(NULL));
	for (int i=0; i<N*N; i++) {
		a[i]=(((float)rand()-RAND_MAX/2)/(RAND_MAX))*MAX;
		b[i]=(((float)rand()-RAND_MAX/2)/(RAND_MAX))*MAX;
	}

	//printf("--- a ---\n");
	//showM (a);
	//printf("--- b ---\n");
	//showM (b);

	struct timeval stime, etime;
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

	//printf("--- c ---\n");
	//showM (c);
*/

	gettimeofday(&stime, NULL);
	matrix_multiply_neon(a,b,c,N,N,N);
	gettimeofday(&etime, NULL);
	printf("=> %lu us\n", (etime.tv_sec-stime.tv_sec)*1000000+etime.tv_usec-stime.tv_usec);

	//printf("--- c (NEON) ---\n");
	//showM (c);

	return 0;
}
