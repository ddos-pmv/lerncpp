#include <iostream>
#include "../genarr.h"

int main(){
    const int size = 20;
    int *arr = init_arr(size,0, 30);
    
    int right = size -1 ; 
    int left = 0;

    while(left<right){
        for(int i = left; i<right; i++){
            if(arr[i]>arr[i+1]){
                int tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
            }
        }
        right -= 1;
        for(int i = right; i>left; i--){
            if(arr[i]<arr[i-1]){
                int tmp = arr[i];
                arr[i] = arr[i-1];
                arr[i-1] = tmp;
            }
        }
        left+=1;
    }

    for(int i = 0; i<size; i++) std::cout<<arr[i]<<"\n";

    return 0;
}

