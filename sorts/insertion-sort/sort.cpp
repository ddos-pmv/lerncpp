#include <iostream>
#include "../genarr.h"

#include "../timer.h"

int main(){
    Timer t;
    const int size = 1000;
    int *arr = init_arr(size, 0, 100);

    for(int i = 1; i<size; i++){
       int tmp = arr[i];
       int j = i;
       while(j>0 && arr[j-1]>tmp){
           arr[j] = arr[j-1];
           j--;
       }
       arr[j] = tmp;
    }

    delete[] arr;

    return 0;
}
