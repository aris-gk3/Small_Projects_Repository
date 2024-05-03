#include <stdlib.h>
#include <stdio.h>
#include <time.h>   // for clock_t, clock(), CLOCKS_PER_SEC
#include <omp.h>
#define USE_OMP 1
#define LENGTH 16384
#define THREADS 1
//2048
//4096
//8192
//16384
//32768
//65536
//131072
//262144
//524288
//1048576

void swap(int *A, int *B);
void sort_w_threads(int arr[], int arr_cpy[], int len, int threads);


int main(){
    int count,phase,temp,len = LENGTH;
    printf("Length of Array to sort: %d\n", LENGTH);
	printf("Generating array with random numbers.\n\n");
    int *arr = (int*)malloc(len * sizeof(int));
    int *arr_cpy = (int*)malloc(len * sizeof(int));
    double start, end;

    for (count = 0; count < len; count++) {
        arr[count] = (rand() % 10000);
        arr_cpy[count] = arr[count];
    }

    sort_w_threads(arr, arr_cpy, LENGTH, 1);
    sort_w_threads(arr, arr_cpy, LENGTH, 2);

    return 0;
}


void swap(int *A, int *B){
    int temp = *A;
    *A = *B;
    *B = temp;
}

void sort_w_threads(int arr[], int arr_cpy[], int len, int threads){
    int temp = len, count , phase;
    printf("Assign %d threads.\n", threads);
    double start = omp_get_wtime();
    if(!USE_OMP){
        for(phase = 0;phase < len; phase++){
            if(phase % 2 == 0){
                for(count = 1; count < len; count +=2){
                    if(arr[count-1]>arr[count]){
                        temp = arr[count-1];
                        arr[count-1] = arr[count];
                        arr[count] = temp;
                    }
                }
            }
            else{
                for(count = 1; count < len-1; count +=2){
                    if(arr[count]>arr[count+1]){
                        temp = arr[count+1];
                        arr[count+1] = arr[count];
                        arr[count] = temp;
                    }
                }
            }
        }
    }
    else{
        #pragma omp parallel num_threads(threads) default(none) shared(arr,len) private(count,temp,phase)
        for(phase = 0; phase < len; phase++){
            if(phase % 2 == 0){
                #pragma omp for
                for(count = 1; count < len; count += 2){
                    if(arr[count-1] > arr[count]){
                        temp = arr[count-1];
                        arr[count-1] = arr[count];
                        arr[count] = temp;
                        //swap(arr+count-1,arr+count);
                    }
                }
            }
            else{
                #pragma omp for
                for(count = 1; count < len-1; count += 2){
                    if(arr[count] > arr[count+1]){
                        temp = arr[count+1];
                        arr[count+1] = arr[count];
                        arr[count] = temp;
                        //swap(arr+count+1,arr+count);
                    }
                }
            }
        }
    }
    double end = omp_get_wtime();
    //Validating
    for(count = 0; count < len-1; count++){
        if(arr[count] > arr[count+1]){
            printf("Sorting is incorrect.\n");
        }
    }
    printf("Sorting is correct.\n");
    for (count = 0; count < len; count++){
		arr[count] = arr_cpy[count];
    }
    printf("Elapsed time was %.6f\n\n", end - start);
}