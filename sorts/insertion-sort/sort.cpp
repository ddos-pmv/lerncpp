#include <iostream>
#include "../genarr.h"


int main(){

    const int size = 25;
    int *arr = init_arr(size, 0, 50);

    for(int i = 1; i<size; i++){
       int tmp = arr[i];
       int j = i;
       while(j>0 && arr[j-1]>tmp){
           arr[j] = arr[j-1];
           j--;
       }
       arr[j] = tmp;
    }

    for(int i = 0; i<size; i++) std::cout<<arr[i]<<"\n";

    delete[] arr;

    return 0;
}
