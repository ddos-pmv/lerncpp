#include <bits/stdc++.h>
#include <thread>
#include <atomic>

int main(){
    std::atomic<int> counter(0);

    auto foo = [&counter](){
        for(int i = 0; i < 100000; i++){
            counter++;
        };
    };

    std::thread t1(foo);
    std::thread t2(foo);

    t1.join();
    t2.join();

    std::cout << counter;

    return 0;
}
