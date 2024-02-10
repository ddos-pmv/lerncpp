#include <iostream>
#include "../genarr.h"
#include "../timer.h"
int main(){
    Timer t;
    const int size = 1000;
    int *arr = init_arr(size,0, 100);
    
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

    return 0;
}

