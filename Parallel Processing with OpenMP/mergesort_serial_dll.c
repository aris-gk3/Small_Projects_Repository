#include<stdio.h>
#include<stdlib.h>
#include <time.h>   // for clock_t, clock(), CLOCKS_PER_SEC
#include <omp.h>
#define LENGTH 65536
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

struct Node{
    int data;
    struct Node *next, *prev;
};

struct Node *split(struct Node *head);
struct Node *merge(struct Node *first, struct Node *second);
struct Node *mergeSort(struct Node *head);
void insert(struct Node **head, int data);
void print_list(struct Node *head);
void swap(int *A, int *B);
struct Node *split(struct Node *head);
void ascending_order_check(struct Node *head);


int main(void){
    struct Node *head = NULL;
    int count, len = LENGTH;
    double start,end;

    for(count=0; count < len; count++){
        insert(&head, rand() % 1001);
    }

    start = omp_get_wtime();
    head = mergeSort(head);
    end = omp_get_wtime();

    printf("N = %d\n", len);
    printf("Elapsed Time was: %f seconds\n", end-start);
    ascending_order_check(head);
    return 0;
}


struct Node *split(struct Node *head){
    struct Node *fast = head,*slow = head;
    while (fast->next && fast->next->next){
        fast = fast->next->next;
        slow = slow->next;
    }
    struct Node *temp = slow->next;
    slow->next = NULL;
    return temp;
}
struct Node *merge(struct Node *first, struct Node *second){
    if (!first)
        return second;

    // If second linked list is empty
    if (!second)
        return first;

    // Pick the smaller value
    if (first->data < second->data)
    {
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}
struct Node *mergeSort(struct Node *head){
    if (!head || !head->next)
        return head;
    struct Node *second = split(head);

    // Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);

    // Merge the two sorted halves
    return merge(head,second);
}
void insert(struct Node **head, int data){
    struct Node *temp =
        (struct Node *)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = temp->prev = NULL;
    if (!(*head))
        (*head) = temp;
    else
    {
        temp->next = *head;
        (*head)->prev = temp;
        (*head) = temp;
    }
}
void print_list(struct Node *head){
    while(head){
        printf("%d ",head->data);
        head = head->next;
    }
    printf("\n");
}
void swap(int *A, int *B){
    int temp = *A;
    *A = *B;
    *B = temp;
}
void ascending_order_check(struct Node *head){
    int l=1;
    while(head->next){
        l++;
        if(head->data > head->next->data){
            printf("Sorting is incorrect\n");
            break;
        }
        head = head->next;
    }
    if(l==LENGTH)
        printf("Sorting is correct.\n");
    else
        printf("Sorting is  correct, length is incorrect l=%d\n",l);
}
