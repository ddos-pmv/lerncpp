#include <iostream>
#include "../genarr.h"

void insert(int * heap, int & heap_length, int insertingValue){
    heap[heap_length] = insertingValue;
    int i = heap_length++;
    while(i>0 && heap[i]<heap[(i-1)/2]){
            int tmp = heap[(i-1)/2];
            heap[(i-1)/2] = heap[i];
            heap[i] = tmp;
            i = (i-1)/2;
    }
}

int remove_min(int * heap, int & heap_length){
    int minValue = heap[0];
    heap[0] = heap[--heap_length];
    int i = 0;
    while(i<heap_length){
        int j = i;
        if(2*i + 1<heap_length && heap[2*i+1]<heap[j]){
            j = 2*i +1;
        }
        if(2*i +2 < heap_length && heap[2*i + 2] < heap[j]){
            j = 2*i +2;
        }
        int tmpValue =  heap[i];
        heap[i] = heap[j];
        heap[j] = tmpValue;
        if(i == j) i= heap_length;
        else i = j;
    }
    return minValue; 
}
int main(){ 
    const int size = 100;
    int* a = init_arr(size, 0, 20);
    int * buffer = new int[size];
    int heapFields= 0;
    for(int i = 0; i<size;i++){
        a[i] = remove_min(buffer,heapFields);
        std::cout<<a[i]<<" ";
    }
    delete[] buffer;
    return 0;
}
