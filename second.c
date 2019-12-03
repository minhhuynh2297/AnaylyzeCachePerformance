#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double startTime, stopTime;
void test(){
	int touch =0;
	int *array1 = (int*) malloc(99999999 * sizeof(int));
	for(int n=8192; n<33554432; n=n*2){
		for(int stride=4; stride<4194305; stride=stride*4){
			startTime=clock();
			for(int times=0; times < 9999; times++){
				for(int i=0; i<n; i=i+stride){
					array1[i]=0;
					touch = array1[i]+touch;
				}
			}
			stopTime=clock();
			printf("array: %d, stride: %d; SEQUENTIAL; %f secs\n", n, stride, (stopTime-startTime)/CLOCKS_PER_SEC);
		}

	}	

}


int main(int argc, char** argv) {

	test();

	
//	printf("SEQUENTIAL; %f secs\n",(stopTime-startTime)/CLOCKS_PER_SEC);

}


