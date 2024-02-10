#include <iostream>
#include "../genarr.h"
#include "../timer.h"
int main(){
    Timer t;
    const int size = 1000;
    int* arr = init_arr(size, 0, 100);
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

    delete[]arr;
    

}
