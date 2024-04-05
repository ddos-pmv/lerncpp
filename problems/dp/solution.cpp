#include <iostream>
#include <vector>
using namespace std;

int main(){
    
    int n, m; cin>>n>>m;
    vector<int> a(n), was(10e4+10, 0);
    vector<int> dp(n, 0);
    for(int i = 0; i<n; i++) cin>>a[i];
    for(int i = n-1; i>=0; i--){
        dp[i] = dp[i+1] + !was[a[i]];
        was[a[i]] = 1;
    }
        

    return 0;
}
