#include <iostream>
#include "../genarr.h"

int sort(int arr[], int l, int r){
    int x = arr[r];

    int less = l;
    for(int i = l; i<r; ++i){
        if(arr[i] <= x){
            int tmp= arr[i];
            arr[i] = arr[less];
            arr[less] = tmp;

            less++;
        }
    }

    int tmp = arr[less];
    arr[less] = arr[r];
    arr[r] = tmp;


    return less;
            

    
}


void  recursive_function(int arr[], int l, int r){
    if(l<r){
        int q= sort(arr, l,r);
        recursive_function(arr,l, q-1);
        recursive_function(arr,q+1, r);
    }
}
    
int main(){
    const int size = 10;
    int* arr = init_arr(size, 0, 50);
    
    for(int i =0; i<size; i++)std::cout<<arr[i]<<"\n";
    std::cout<<"\n\n\n\n";

    recursive_function(arr,0, size-1);
     
    for(int i =0; i<size; i++)std::cout<<arr[i]<<"\n";

    delete[] arr;

    return 0;
}
