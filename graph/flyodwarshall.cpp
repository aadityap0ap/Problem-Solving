#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int n,e;
vector<vector<int>>dist;

void flyodW(){
    for(int k = 0;k<n;k++){// this loop is for intermediate nodes
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n;j++){
                if(dist[i][k] != INT_MAX && dist[k][j] !=INT_MAX){
                    dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }
    }
}

int main(){
    cin>>n>>e;
    dist.assign(n,vector<int>(n,INT_MAX));
    for(int i = 0;i<n;i++){
        dist[i][i] = 0; // we are doing this as we know to reach a node from itself will be 0 only
    }
    for(int i = 0;i<e;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dist[u][v] = min(dist[u][v],w);
        dist[v][u] = min(dist[v][u],w);
    }
    flyodW();
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(dist[i][j]==INT_MAX){
                cout<<"1NF"<<" ";
            }
            else{
                cout<<dist[i][j]<<" ";
            }
        }
        cout<<endl;
    }
    return 0;
}