#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <omp.h>
#define  Max(a,b) ((a)>(b)?(a):(b))
long long int N;
long long int THR = 1;
float maxeps = 0.1e-7;
int itmax = 100;
int i,j,k;
float eps;
float **A ,  **B;

void relax();
void resid();
void init();
void verify();

int main(int an, char **as)
{
	double start_time, end_time;
    start_time = omp_get_wtime();
	THR = strtoll(as[2], 0, 10);
	FILE *outf = fopen(as[4], "w");
	N = 2*2*2*2*2*2*strtoll(as[1], 0, 10) + 2;
	A = (float**)malloc(N * sizeof(float*));
	B = (float**)malloc(N * sizeof(float*));
	int i;
    for (i = 0; i < N; ++i) {
        A[i] = (float*)malloc(N * sizeof(float));
		B[i] = (float*)malloc(N * sizeof(float));
    }
	#pragma omp parallel num_threads(THR)
	{
		#pragma omp master
		{
			int it;
			#pragma omp master
			{
			init();


				for(it=1; it<=itmax; it++)
				{
                    #pragma omp taskwait
                    #pragma omp master
                    {
                        eps = 0.;
                    }

					relax();

					#pragma omp taskwait
					resid();
					#pragma omp taskwait

					fprintf(outf, "it=%4i   eps=%f\n", it,eps);

                    if (eps < maxeps) break;

				}
				#pragma omp taskwait
				verify(outf);
			}
		}
	}
	end_time = omp_get_wtime();
	FILE *file = fopen(as[3], "w");
    fprintf(file, "%f\n", end_time - start_time);
	fclose(file);
	fclose(outf);
	for (i = 0; i < N; ++i) {
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);
	return 0;

}

void init()
{
	for(j=0; j<=N-1; j++)
	for(i=0; i<=N-1; i++)
	{
		if(i==0 || i==N-1 || j==0 || j==N-1) A[i][j]= 0.;
		else A[i][j]= ( 1. + i + j ) ;
	}
}

void relax()
{
	for(j=2; j<=N-3; j++)
		#pragma omp task shared(B) firstprivate(i,j)
		{
			for(i=2; i<=N-3; i++)
			{
				B[i][j]=(A[i-2][j]+A[i-1][j]+A[i+2][j]+A[i+1][j]+A[i][j-2]+A[i][j-1]+A[i][j+2]+A[i][j+1])/8.;
			}
		}
}

void resid()
{
	for(j=1; j<=N-2; j++)
	#pragma omp task shared(A, eps) firstprivate(i,j)
	{
		float tmp = 0;
		for(i=1; i<=N-2; i++)
		{
			float e;
			e = fabs(A[i][j] - B[i][j]);
			A[i][j] = B[i][j];
			tmp = Max(tmp,e);

		}
		#pragma omp critical
        {
			eps = Max(eps, tmp);
		}
	}
}

void verify(FILE* outf)
{
	float s;
	s=0.;
	for(j=0; j<=N-1; j++)
	for(i=0; i<=N-1; i++)
	{
		s=s+A[i][j]*(i+1)*(j+1)/(N*N);
	}
	fprintf(outf, "  S = %f\n",s);
}
