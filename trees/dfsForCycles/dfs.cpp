#include <bits/stdc++.h>


using namespace std;

void dfs(vector<vector<int>>&graph, int v, vector<int> &visited, int from, bool &hasCycle){
    visited[v] = 1;

    for(auto to: graph[v]){
        if(to!=from){
            if(visited[to]==0){
                dfs(graph, to, visited, v, hasCycle);
            }
            else if(visited[to]==1){
                hasCycle =  true;
            }
        }
    }
    visited[v] = 2;
}


int main(){
    int n, m;
    cin>>n>>m;
    vector<vector<int>> vec(n);
    set<pair<int, int>> st;
    for(int i = 0 ;i<m; i ++){
        int a,b;
        cin>>a>>b;
        a--;
        b--;
        if(st.find({a,b})==st.end()){
            vec[b].push_back(a);
            vec[a].push_back(b);
            st.erase({a,b});
            st.erase({b,a});
        }
    }
    vector<int> visited(n,0);
    bool hasCycle = false;
    dfs(vec, 0, visited, -1, hasCycle);
    if(hasCycle){
        cout<<"YES";
    }
    else cout<<"NO";


    return 0;
}
