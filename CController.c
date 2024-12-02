#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <immintrin.h>
#include <time.h>

#define MIN -50
#define MAX 50

void calculate_distance(int n, double *x1, double *x2, double *y1, double *y2, double *z){
	for (int i = 0; i < n; i++){
		__m128d diffX = _mm_set_sd(x2[i] - x1[i]);
		__m128d diffY = _mm_set_sd(y2[i] - y1[i]);

		diffX = _mm_mul_sd(diffX, diffX);
		diffY = _mm_mul_sd(diffY, diffY);

		__m128d summation = _mm_add_sd(diffX, diffY);
		__m128d finalResult = _mm_sqrt_sd(summation, summation);

		_mm_store_sd(&z[i], finalResult);
	}
}

extern void calculateDist(int n, double *x1, double *x2, double *y1, double *y2, double *z);

int main(){
	int n = 268435456;
    double *x1 = (double*)malloc(n*sizeof(double));
    double *x2 = (double*)malloc(n*sizeof(double));
    double *y1 = (double*)malloc(n*sizeof(double));
    double *y2 = (double*)malloc(n*sizeof(double));
    double *z = (double*)malloc(n*sizeof(double));

    if(!x1 ||!x2 ||!y1 || !y2|| !z){
        printf("Memory allocation failed");
        return 1;
    }

    srand((unsigned int)time(NULL));

    for(int i = 0; i < n; i++){
        x1[i] = (rand() / (double)RAND_MAX) * (50 - (-50)) -50;
        x2[i] = (rand() / (double)RAND_MAX) * (50 - (-50)) -50;
        y1[i] = (rand() / (double)RAND_MAX) * (50 - (-50)) -50;
        y2[i] = (rand() / (double)RAND_MAX) * (50 - (-50)) -50;
        
    }


    //C kernel
    clock_t start = clock();
    calculate_distance(n, x1,x2,y1,y2,z);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time ran: %f\n", time_taken);

    int i;
    for(i = 0; i < 10; i++){
    	printf("Point A: (%.8f, %.8f) Point B : (%.8f, %.8f) Z[%d] = %.8f\n", x1[i], y1[i], x2[i], y2[i], i, z[i]);
    }

    //ASM kernel
    start = clock();
    calculateDist(n,x1,x2,y1,y2,z);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time ran: %f\n", time_taken);

    for(int i = 0; i < 10; i++){
    	printf("Point A: (%.8f, %.8f) Point B : (%.8f, %.8f) Z[%d] = %.8f\n", x1[i], y1[i], x2[i], y2[i], i, z[i]);
    }

    free(x1);
    free(x2);
    free(y1);
    free(y2);
    free(z);
	return 0;
}