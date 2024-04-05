#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve(){
    int n, k, x;
    cin >> n >> k >> x;

    vector<int> A(n+1, 0);
    for (int i = 1; i <= n; i++)
        cin >> A[i];

    std::sort(A.begin(), A.end());

    for (int i = 1; i <= n; i++)
        A[i] += A[i - 1];

    int ans = -1e9;
    for(int i = 0; i<=k; i++){
        ans = std::max(ans, 2*A[max(n-(i+x),0)] - A[n-i]);
    }

    cout<<ans<<"\n";
}

int main(){
    //ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;

    while (tc--)
        solve();
}
