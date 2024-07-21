#include <bits/stdc++.h>


using namespace std;


void solve(){
    int n;
    cin>>n;
    vector<int> p(n);
    for(int i =0;i<n; i++){
        cin>>p[i];
        p[i]--;
    }

    vector<int> used(n);
    vector<int>ans(n);
    for(int i= 0 ;i<n; i++){
        if(!used[i]){
            vector<int>cur;
            int j = i;
            while(!used[j]){
                cur.push_back(j);
                used[j] = true;
                j = p[j];

            }
            for(auto el: cur)ans[el] = (int)cur.size();

        }
    }
    for(auto el: ans) cout<<el<<' ';
    cout<<'\n';





}


int main(){
    int t; cin>>t;
    while(t--) solve();


    return  0;
}