#include<iostream>
#include<vector>
using namespace std;

int n,e;
vector<vector<int>>adj;
vector<int>visited;

bool DFS(int node){
    visited[node] = 1;
    for(int j = 0;j<adj[node].size();j++){
        int neigh = adj[node][j];
        if(visited[neigh] ==0){
            if(DFS(neigh)){
                return true;
            }
        }
        else if(visited[neigh] == 1){
            return true;
        }
    }
        visited[node] = 2;
        return false;
    
}

int main(){
    cin>>n>>e;
    adj.resize(n);
    visited.assign(n,0);
    for(int i = 0;i<e;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        //adj[v].push_back(u);
    }

    for(int i = 0;i<n;i++){
        if(visited[i] == 0){
            if(DFS(i)){
                cout<<"Cycle detected"<<endl;
                return 0;
            }
        }
    }
               cout<<"No cycle detected"<<endl;

    return 0;
}