#include <stdlib.h>
#include <stdio.h>
#include <string.h> //for memcpy()
#include <time.h>
#include <omp.h>
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

void merge(int arr[], int len, int tmp[]);
void mergesort(int arr[], int len, int tmp[]);
void mergesort_parallel(int arr[], int threads, int len, int tmp[]);
void order_check(int arr[], int len);


int main(){
    int count,len = LENGTH, threads;
    int *arr = (int*)malloc (len * sizeof (int));
    int *arr_cpy = (int*)malloc (len * sizeof (int));
    int *tmp = (int*)malloc (len * sizeof (int));
    //double time = 0.0;
    double start, end;
    printf("Length of Array to sort: %d\n", LENGTH);
	printf("Generating array with random numbers.\n\n");
    for (count = 0; count < len; count++){
        arr[count] = (rand () % 1001);
        arr_cpy[count] = arr[count];
    }

    threads = 1;
    printf("Assign %d thread(s).\n", threads );
    //clock_t begin = clock();
    start = omp_get_wtime();
    //omp_set_nested(1);
    mergesort_parallel(arr, threads, len, tmp);
    end = omp_get_wtime();
    //clock_t end = clock();
    order_check(arr,len);
    //time += (double)(end - begin) / CLOCKS_PER_SEC;
    //printf("Elapsed time was %f  *****\n", time);
    printf("Elapsed time was %.6f\n", end - start);
    for (count = 0; count < len; count++){
        arr[count] = arr_cpy[count];
    }
    // ******************************************
    threads = 2;
    printf("Assign %d thread(s).\n", threads );
    //clock_t begin = clock();
    start = omp_get_wtime();
    //omp_set_nested(1);
    mergesort_parallel(arr, threads, len, tmp);
    end = omp_get_wtime();
    //clock_t end = clock();
    order_check(arr,len);
    //time += (double)(end - begin) / CLOCKS_PER_SEC;
    //printf("Elapsed time was %f  *****\n", time);
    printf("Elapsed time was %.6f\n", end - start);
}

void merge(int arr[], int len, int tmp[]){
    int i1 = 0;
    int i2 = len / 2;
    int tmpi = 0;
    while (i1 < len / 2 && i2 < len){
        if (arr[i1] < arr[i2]){
            tmp[tmpi] = arr[i1];
            i1++;
        }
        else{
            tmp[tmpi] = arr[i2];
            i2++;
        }
        tmpi++;
    }
    while (i1 < len / 2){
        tmp[tmpi] = arr[i1];
        i1++;
        tmpi++;
    }
    while (i2 < len){
        tmp[tmpi] = arr[i2];
        i2++;
        tmpi++;
    }
    memcpy(arr, tmp, len * sizeof (int));
}
void mergesort(int arr[], int len, int tmp[]){
    if(len > 1){
        mergesort(arr, len/2, tmp);
        mergesort(arr + len/2, len-len/2, tmp);
        merge(arr, len, tmp);
    }
}
void mergesort_parallel(int a[], int threads, int len, int tmp[]){
    if(threads == 1){
        mergesort(a, len, tmp);
    }
    else if(threads > 1){
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergesort_parallel(a, threads/2, len/2, tmp);
            }
            #pragma omp section
            {
                mergesort_parallel(a + len/2, threads - threads/2, len-len/2,
                                            tmp + len/2);
            }
        }
        merge (a, len, tmp);
    }
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
