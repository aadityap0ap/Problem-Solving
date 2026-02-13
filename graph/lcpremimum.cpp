// q->all path from source lead to destination
#include<iostream>
#include<vector>
using namespace std;

int n,e;
vector<vector<int>>g;
vector<int>visited;
int src,dest;

bool dfs(int node){
//    if(node == dest) return true;
         if (g[node].empty()) {
        // leaf node: must be destination
        return node == dest;
      }
    if(visited[node] == 1) return false;
    if(visited[node] == 2) return true;
    visited[node] = 1;
    for(int j = 0;j<g[node].size();j++){
        int neigh = g[node][j];
            if(!dfs(neigh)){
                return false;
            }
    }
    visited[node]  = 2;
    return true;
}

int main(){
    cin>>n>>e;
    g.resize(n);
    visited.assign(n,0);
    for(int i = 0;i<e;i++){
        int u ,v;
        cin>>u>>v;
        g[u].push_back(v);
    }
    cin>>src>>dest;
            if(!dfs(src)){
                cout<<"true"<<endl;
            }
            else{
                cout<<"false"<<endl;
            }
        
   
    return 0;
}