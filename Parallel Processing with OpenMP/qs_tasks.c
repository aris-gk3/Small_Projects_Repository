#include <stdlib.h>
#include <stdio.h>
#include <string.h> //for memcpy()
#include <time.h>
#include <omp.h>
#include<math.h>
#include <stdlib.h>
#define USE_OMP 1
#define LENGTH 524288
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


void order_check (int arr[], int len);

void quicksort(int arr[], int low, int high);
int partition (int arr[], int low, int high);
void swap(int *A, int *B);
void sort_w_threads(int arr[], int arr_cpy[], int len, int threads);

int main(int argc, char *argv[]) {
    int count,len = LENGTH, threads;
    int *arr = (int*)malloc (len * sizeof (int));
	int *arr_cpy = (int*)malloc (len * sizeof (int));
    double start, end;

	printf("Length of Array to sort: %d\n", LENGTH);
	printf("Generating array with random numbers.\n\n");

    srand(314159);
    for (count = 0; count < len; count++){
        arr[count] = (rand () % 1001);
		arr_cpy[count] = arr[count];
    }
	sort_w_threads(arr, arr_cpy, len, 1);
	sort_w_threads(arr, arr_cpy, len, 2);

	return 0;
}

void order_check (int arr[], int len){
    int count;
    for(count = 0; count < len-1; count++){
        if(arr[count]>arr[count+1]){
            printf("Sotring order is incorrect.\n");
            return;
        }
    }
    printf("Sotring order is correct.\n");
}

void quicksort(int arr[], int low, int high){
	if(low < high){
		int i = partition(arr, low, high);
		#pragma omp task firstprivate(arr,low,i)
		{
			quicksort(arr,low, i-1);

		}
		#pragma omp task firstprivate(arr, high,i)
		{
			quicksort(arr, i+1, high);
		}
	}
}
int partition (int arr[], int low, int high){
	int pivot = arr[high];
	int i = (low - 1);
    int count;
	for(count = low; count <= high-1; count++){
		if (arr[count] <= pivot){
			i++;
			swap(&arr[i], &arr[count]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}
void swap(int *A, int *B){
	int tmp;
    tmp = *A;
	*A = *B;
	*B = tmp;
}

void sort_w_threads(int arr[], int arr_cpy[], int len, int threads){
	printf("Assign to %d different thread(s).\n", threads);
    omp_set_num_threads(threads);
    double start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single nowait
        quicksort(arr, 0, len-1);
    }
	//quickSort(arr,0,n-1);
	double end = omp_get_wtime();
	order_check (arr, LENGTH);
	printf("Elapsed time was %6f\n\n",end-start);
	for (int count = 0; count < len; count++){
		arr[count] = arr_cpy[count];
    }
}
