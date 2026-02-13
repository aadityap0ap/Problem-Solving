#include<iostream>
#include<vector>
using namespace std;

int n,e;
vector<vector<int>>adj;
vector<bool>visited;
vector<int>ans;

void DFS(int node){
    visited[node] = true;
     ans.push_back(node);
    for(int j = 0;j<adj[node].size();j++){
        int neigh = adj[node][j];
        if(!visited[neigh]){
            DFS(neigh);
        }
    }
   
}

int main(){
    cin>>n>>e;
    adj.resize(n);
    visited.assign(n,false);
    ans.clear();
    for(int i = 0;i<e;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 0;i<n;i++){
        if(!visited[i]){
            DFS(i);
        }
    }
    cout<<"The DFS for the graph is:"<<endl;
    for(int i = 0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    return 0;
}