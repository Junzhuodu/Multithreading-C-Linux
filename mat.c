#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define M 3 
#define N 4 
#define P 5 

int A[M][N];
int B[N][P];
int C[M][P];

void *matmult(void *arg){
	int row = (int)arg, col;
	int i, t; 

	for (col = 0; col < P; col++){
		t = 0; 
		for (i = 0; i < N; i++)
			t += A[row][i] * B[i][col];
		C[row][col] = t; 
		printf("%d\n", t);
	}
	return (0);
}

main(){
	int i; 
	pthread_t thr[M];
	int error;

	for (i = 0; i < M; i++){
		if (error = pthread_create(
			&thr[i],
			0,
			matmult,
			(void *)i)){
			fprintf(stderr, 
				"pthread_create: %s", 
				strerror(error));
		exit(1);
		}
	}
	for (i = 0; i < M; i++){
		pthread_join(thr[i], 0);
		printf("%s%d\n", "hello: ", i);
	}
}
