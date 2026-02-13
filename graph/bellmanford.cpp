#include<iostream>
#include<vector>
#include<climits>
using namespace std;


int v,e;
vector<vector<int>>adj;
vector<int>dist;

void bellf(int src){
    dist[src] = 0;
    for(int i = 0;i<v-1;i++){
        for(int j = 0;j<e;j++){
            int U = adj[j][0];
            int V = adj[j][1];
            int W = adj[j][2];
        if(dist[U]!=INT_MAX && dist[V] > dist[U] + W){
            dist[V] = dist[U]+W;
        }
    }
    }
}

int main(){
    cin>>v>>e;
    adj.resize(e,vector<int>(3));
    dist.assign(v,INT_MAX);

    for(int i = 0;i<e;i++){
        cin>>adj[i][0]>>adj[i][1]>>adj[i][2];
    }

    bellf(0);
   for (int i = 0; i < v; i++) {
        cout << "Shortest distance to " << i << " is: ";
        if (dist[i] == INT_MAX)
            cout << "INF\n";
        else
            cout << dist[i] << "\n";
    }
    return 0;
}

