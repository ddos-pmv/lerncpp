#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;

vector<int> bfs(vector<vector<int>> &graph, int start){
    vector<int> visited(graph.size(), 0);
    vector<int> dist(graph.size(),INF);

    queue<int> q;
    visited[start] = 1;
    dist[start] = 0;

    q.push(start);

    while(!q.empty()){
        int v = q.front();
        q.pop();

        for(const auto &to : graph[v]){
            if(!visited[to]){
                visited[to] = 1;
                dist[to] = dist[v]+1;
                q.push(to);
            }
        }
    }
    return dist;


}

int main(){
    int n; cin>>n;
    vector<vector<int>> vec(n);
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n ; j++){
            int t;cin>>t;
            if(t!=0){
                vec[i].push_back(j);
            }
        }
    }
    int a, b;
    cin>>a>>b;

    vector<int> dist = bfs( vec, a-1);
    int ans = dist[b-1];
    if(ans == INF){
        cout<<-1;
    }
    else cout<<ans;


    return 0;
}
