#include <iostream>
#include "../genarr.h"

int main(){
    const int size = 20;

    int *arr = init_arr(size, 0, 100);

    for(int i = 0; i<size - 1; i++){
        for (int j = 0; j<size - i  - 1; j++){
            if(arr[j]>arr[j+1]){
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;

            }
        }
    }
    for(int i = 0; i<size; i++)std::cout<<arr[i]<<"\n";



}
