#include <iostream>
#include "../genarr.h"
#include <vector>

void mergeSort(int * a, int l, int r){
    if(r- l<2) return;
    else if(r - l==2){
        if(a[l] > a[l+1]){
            int tmp = a[l];
            a[l] = a[l+1];
            a[l+1] = tmp;
        }
    }

    mergeSort(a, l, (l+r)/2);
    mergeSort(a, (r+l)/2, r);

    std::vector<int> b;
    int b1 = l;
    int e1 = (l+r)/2;
    int b2 = e1;

    while(b.size()<r-l){
        if(b1>=e1 || (b2<r && a[b2]<a[b1])){
            b.push_back(a[b2]);
            b2++;
        }
        else{
            b.push_back(a[b1]);
            b1++;
        }
    }

    for(size_t i = l; i<r;i++)a[i] = b[i-l];


}

int main(){
    const int size = 20;

    int * arr = init_arr(size,0, 33);

    mergeSort(arr,0,size);


    for(size_t i = 0; i<size; i++) std::cout<<arr[i]<<"\n";

    delete[] arr;


    return 0;
}
