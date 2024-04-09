#include <bits/stdc++.h>


using namespace std;

void dfs(vector<vector<int>>&graph, int v, vector<int> &visited, vector<int>  &order){
    visited[v] = 1;

    for(auto to: graph[v]){
        if(visited[to]==0){
            dfs(graph, to, visited, order);
        }
    }
    order.push_back(v);
}
void findCycle(vector<vector<int>>&graph, int v, vector<int> &visited, bool &hasCycle){
    visited[v] = 1;

    for(auto to: graph[v]){
        if(visited[to]==0){
            findCycle(graph, to, visited, hasCycle);
        }
        else if(visited[to]==1){
        hasCycle =  true;
        }
    }
    visited[v] = 2;
}


int main(){
    int n, m;
    cin>>n>>m;
    vector<vector<int>> vec(n);
    for(int i = 0 ;i<m; i ++){
        int a,b;
        cin>>a>>b;
        a--;
        b--;
        vec[a].push_back(b);
    }
    vector<int> visited(n,0);
    bool hasCycle  = false;
    findCycle(vec, 0, visited, hasCycle);
    fill(visited.begin(), visited.end(), 0);
    vector<int> order;
    for(int i = 0; i<n;i++){
        if(!visited[i]) dfs(vec, i, visited, order);
    }
    if(order.size() == n and !hasCycle){
        reverse(order.begin(), order.end());
        cout<<"Yes";
    }
    else{
        cout<<"No";
    }


    return 0;
}
