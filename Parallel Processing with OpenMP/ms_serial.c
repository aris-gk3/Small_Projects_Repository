// Serial Implementation of a mested mergesort

#include <stdlib.h>
#include <stdio.h>
#include <string.h> //for memcpy()
#include <time.h>
#define LENGTH 67108864
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
//2097152
//4194304
//8388608
//16777216
//33554432
//67108864

void merge(int arr[], int len, int tmp[]);
void mergesort(int arr[], int len, int tmp[]);
void order_check(int arr[], int len);


int main(){
    int count,len = LENGTH;
    int *arr = (int*)malloc (len * sizeof (int));
    int *tmp = (int*)malloc (len * sizeof (int));
    double time = 0.0;

    printf("Length of Array to sort: %d\n", LENGTH);
	printf("Generating array with random numbers.\n\n");
    for (count = 0; count < len; count++){
        arr[count] = (rand () % 1001);
    }
    clock_t begin = clock();
    mergesort(arr, len, tmp);
    clock_t end = clock();
    order_check(arr,len);
    time += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Elapsed time was %f.\n", time);
}

void merge(int arr[], int len, int tmp[]){
    int i1 = 0;
    int i2 = len / 2;
    int tmpi = 0;
    while(i1 < len/2 && i2 < len){
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
    if(len > 1){//error with exit condition
        //printf("%d", len);
        mergesort(arr, len/2, tmp);
        mergesort(arr + len/2, len-len/2, tmp);
        merge(arr, len, tmp);
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
