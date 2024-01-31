#include <iostream>
#include "../genarr.h"

int main(){
    const int size = 20;
    int* arr = init_arr(size, 0, 40);
    int step = size - 1;

    while(step>=1){
        for(int i = 0; i+step<size; i++){
            if(arr[i] >arr[i+step]){
                int tmp = arr[i];
                arr[i] = arr[i+step];
                arr[i+step] = tmp;

            }
        }

        step /= 1.247; 
    }

    for(int i = 0; i<size; i++) std::cout<<arr[i]<<"\n";

    

}
