#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;

int v,e,w;
using state = pair<int,int>;
vector<vector<state>>g;
vector<int>weight;

void dij(int src){
    priority_queue<state>pq;
    pq.push({start,0});
    weight[start] = 0; 

    while(!pq.empty()){
        state node = q.front();
        q.pop();
        for(int i = 0;i<adj[node].size();i++){
            int neigh_node = node.second().first;
             int wt = node.second().second;
             if(weight[neigh_node]>weight[node]+wt){
                weight[neigh_node] = weight[node]+wt;
             }
        }
        
        
    }
}

int main(){
    cin>>v>>e>>w;
    g.resize(v,vector<int>(e));
    weight.assign(v,INT_MAX);
    for(int i = 0;i<e;i++){
    adj[u].push_back({v,w});
    }
   
    dij(0);

    return 0;
}