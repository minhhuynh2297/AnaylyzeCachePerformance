#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define min(a,b) (((a)<(b))?(a):(b))

int** multiply_matrices(int**, int**, int, int, int, int);
void freeAll(int**, int, int);
void writeMatrix(FILE *fout, int **matrix, int m, int n);

double startTime, stopTime;

int main(int argc, char** argv) {

	FILE* fin;
	FILE* fout;

	/* open the file */
	fin = fopen(argv[1], "r");
	
	/* read the file */
	int m1 = 0;
	int n1 = 0;
	int m2 = 0;
	int n2 = 0;
	int i = 0;
	int j = 0;
	
	if(fscanf(fin, "%d %d", &m1, &n1) != 2) {
		printf("error\n");
		return 0;
	}
	
	int** array1 = (int**) malloc(m1 * sizeof(int*));
	
	for(i = 0; i < m1; i ++) {
		array1[i] = (int*) malloc(n1 * sizeof(int));
	}
	
	for(i = 0; i < m1; i ++) {
		for(j = 0; j < n1; j ++) {
			if(fscanf(fin, "%d", &array1[i][j]) != 1) {
				printf("error\n");
				return 0;
			}
			if(j == n1 - 1) {
				fscanf(fin, "\n");
			} else {
				fscanf(fin, " ");
			}
		}
	}
	
	fscanf(fin, "\n");
	
	if(fscanf(fin, "%d %d", &m2, &n2) != 2) {
		printf("error\n");
		return 0;
	}
	
	int** array2 = (int**) malloc(m2 * sizeof(int*));
	
	for(i = 0; i < m2; i ++) {
		array2[i] = (int*) malloc(n2 * sizeof(int));
	}
	
	for(i = 0; i < m2; i ++) {
		for(j = 0; j < n2; j ++) {
			if(fscanf(fin, "%d", &array2[i][j]) != 1) {
				printf("error\n");
				return 0;
			}
			if(j == n2 - 1) {
				fscanf(fin, "\n");
			} else {
				fscanf(fin, " ");
			}
		}
	}
	fclose(fin);
	
	/* add the matrices and print the result */
	if(m2 != n1) {
		printf("error\n");
		return 0;
	}
	
	startTime = clock();
	int** product = multiply_matrices(array1, array2, m1, n1, m2, n2);
	stopTime = clock();
	
	printf("%d * %d; SEQUENTIAL; %f secs\n", m1, n2, (stopTime-startTime)/CLOCKS_PER_SEC);
	
	fout = fopen("matrix_result2.txt", "w");
	writeMatrix(fout, product, m1, n2);
	fclose(fout);
	
	freeAll(array1, m1, n1);
	freeAll(array2, m2, n2);
	freeAll(product, m1, n2);
	
	//print_matrix(product, m1, n2);
	return 0;
}

int** multiply_matrices(int** matrix1, int** matrix2, int m1, int n1, int m2, int n2) {
	if(n1 != m2) {
		printf("error\n");
		return NULL;
	}
	
	int jj, kk, i, j, k; 
	int blockSize=1000;
	int sum=0; 
	int** product = (int**) malloc(m1 * sizeof(int*));

	for(i = 0; i < m1; i ++) {
		product[i] = (int*) malloc(n2 * sizeof(int));
	}
	
	for(i=0; i<m1;i++){
		for(j=0; j<n2; j++){
			product[i][j]=0;
		}
	}

	for(kk=0;kk<blockSize; kk+=blockSize){
		for(jj=0; jj< blockSize; jj+=blockSize){
			for(i =0; i< m1; i++) {
				for (j=jj; j<min(jj+blockSize, n2); j++){
				sum=product[i][j];	
					for(k=kk; k<min(kk+blockSize, n1); k++){
						sum+=matrix1[i][k]*matrix2[k][j];
					}
					product[i][j]=sum; 
				}
			}

		}
	}
	
	return product;
} 


/* Freeing fcts ------------------------------------------------------- */
void freeAll(int **matrix, int m, int n) {
	int i;
	for (i=0; i<m; i++) {

		free(matrix[i]);
	}
	free(matrix);
}

void writeMatrix(FILE *fout, int **matrix, int m, int n) {
	int i,j;

	for(i=0; i<m; i++) {     
		for(j=0; j<n; j++)  
			fprintf(fout,"%d ",matrix[i][j]); 
		putc('\n',fout);
   }
}


