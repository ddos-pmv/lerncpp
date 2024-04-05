#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;cin>>n;
    vector<vector<int>> vec(n, vector<int>(n,INT_MAX));

    for(int  i = 0 ; i<n;i++){
        for(int j = 0; j<n; j++){
            int tmp;cin>>tmp;
            if(tmp == 0 and  i == j) vec[i][j] =tmp;
            else if(tmp!=0) vec[i][j] = tmp;
        }
    }
    for(int k = 0; k<n; k++){
        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                vec[i][j] = min(vec[i][j], vec[i][k]+vec[k][j]);
            }
        }
    }
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            cout<<vec[i][j]<<" ";
        }
        cout<<'\n';
    }

    return 0;
}
