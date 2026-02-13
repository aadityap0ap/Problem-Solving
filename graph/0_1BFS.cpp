#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

int v,e;
vector<vector<pair<int,int>>>adj;
vector<int>distance;

int main(){
    cin>>v>>e;
    int src,dest;
    cin>>src>>dest;
    adj.resize(v);
    distance.assign(v,100);
    for(int i = 0;i<e;i++){
        int U,V,w;
        cin>>U>>V>>w;
        adj[U].push_back({V,w});
    }
   dequeue<int>deque;
   deque.push(src);
   distance[src] = 0;

   while(!deque.empty()){
    int node = deque.front();
    deque.pop();
    for(int i = 0;i<adj[node].size();i++){
        int neighbour = adj[node][i];
        distance[neighbour] = distance[node]+w;
        deque.front(neighbour);
    }
   }
    return 0;
}