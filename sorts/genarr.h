#include <cstdlib>
#include <ctime>

int* init_arr(int size, int start, int end){
    srand(time(0));

    int* arr = new int[size];
    for(int i = 0; i<size; i++){
        arr[i] = start +rand() %(end + 1 - start);
    }

    return arr;



}

