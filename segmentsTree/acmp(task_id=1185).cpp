#include <bits/stdc++.h>
using namespace std;
#define ll long long


void setVal( int pos, int value, vector<ll> &tree){
    tree[pos] = value;
    while(pos!=1){
        pos/=2;
        tree[pos] =  tree[pos*2] + tree[pos*2+1];
    }
    return;
}

ll sum(int l, int r, vector<ll> &tree){
    ll sm = 0;
    while(l<=r){
        if(l%2!=0) {
            sm += tree[l];
            l++;
        }
        if(r%2==0){
            sm+=tree[r];
            r--;
        }
        l /=2;
        r /= 2;

    }
    return sm;
}


int main(){
    int n, m; cin>>n;

    int col =  (int)pow(2,(int)ceil(log2(n))+1);
    int start = pow(2,(int)ceil(log2(n)));

    vector<ll>tree(col, 0);
    vector<int> vec(n);
    for(int i = 0; i<n; i++){
        cin>>vec[i];
        setVal(i+start, vec[i], tree);
    }
    cin>>m;

    while(m--){
        char flag;
        int l,r;
        cin>>flag>>l>>r;
        if(flag=='u'){
            setVal(start + l-1,r, tree);
        }
        else{
            ll ans  =  sum(l+start -1, r+start-1,tree);
            cout<<ans<<" ";
        }


    }


    return 0;
};