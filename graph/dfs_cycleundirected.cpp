#include<iostream>
#include<vector>
using namespace std;

int n,e;
vector<vector<int>>adj;
vector<bool>visited;

bool DFS(int node,int parent){
    visited[node] = 1;
    for(int j = 0;j<adj[node].size();j++){
        int neigh = adj[node][j];
        if(visited[neigh] ==false){
            if(DFS(neigh,node)){
                return true;
            }
        }
        else if(neigh != parent){
            
            return true;
        }
    }
        
        return false;
    
}

int main(){
    cin>>n>>e;
    adj.resize(n);
    visited.assign(n,false);
    for(int i = 0;i<e;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 0;i<n;i++){
        if(visited[i] == false){
            if(DFS(i,-1)){
                cout<<"Cycle detected"<<endl;
                return 0;
            }
        }
    }
               cout<<"No cycle detected"<<endl;

    return 0;
}