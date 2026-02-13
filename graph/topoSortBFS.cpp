#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int V,e;
vector<vector<int>>adj;
vector<int>InDegree;
vector<int>topo;
vector<int>topo1;
vector<bool>visited;

void topoBybfs(){
queue<int>que;
for(int i = 0;i<V;i++){
    if(InDegree[i]==0){
        que.push(i);
    }
}
while(!que.empty()){
    int node = que.front();
    que.pop();
    topo.push_back(node);
    for(int j = 0;j<adj[node].size();j++){
        int neighbour = adj[node][j];
        InDegree[neighbour]--;
        if(InDegree[neighbour]==0){
            que.push(neighbour);
        }
    }
}
}

void topoBydfs(int node){
    visited[node] = true;
    for(int j = 0;j<adj[node].size();j++){
        int neighbour = adj[node][j];
        if(visited[neighbour]==false){
            topoBydfs(neighbour);
        }
    }
    topo1.push_back(node);
}


int main(){

cin>>V>>e;
adj.resize(V);
InDegree.resize(V,0);
//topo.resize(V);
visited.assign(V,false);
for(int i = 0;i<e;i++){
    int u,v;
    cin>>u>>v;
    adj[u].push_back(v);
    InDegree[v]++;
}
for(int i = 0;i<V;i++){
    if(visited[i]==0){
        topoBydfs(i);
    }
}
cout<<"Topological Sort by DFS: "<<" ";
reverse(topo1.begin(),topo1.end());
for(int i = 0;i<topo1.size();i++){
    cout<<topo1[i]<<" ";
}
cout<<endl;
cout<<"Topological Sort by BFS: "<<" ";
topoBybfs();
for(int i = 0;i<topo.size();i++){
    cout<<topo[i]<<" ";
}
cout<<endl;
return 0;
}