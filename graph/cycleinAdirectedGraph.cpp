#include <iostream>
#include<queue>
#include<vector>
using namespace std;



int main()
{
    int V,e;
    cin>>V>>e;
    vector<int>InDegree(V,0);
    vector<vector<int>>adj(V);
    for(int i = 0;i<e;i++){
        int u ,v;
        cin>>u>>v;
        adj[u].push_back(v);
        InDegree[v]++;
    }
    vector<int>ans;
    queue<int>q;
    //vector<bool>visited(V,false);
    for(int i = 0;i<V;i++){
        if(InDegree[i] == 0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int node = q.front();
        q.pop();
        ans.push_back(node);
        for(int i = 0;i<adj[node].size();i++){
            int neighbour = adj[node][i];
            InDegree[neighbour]--;
            if(InDegree[neighbour] == 0){
                q.push(neighbour);
            }
        }
    }
    int k = ans.size();
    if(k==V){
        //return true;
        cout<<"There is no cycle";
    }
    else{
        //return false;
        cout<<"There is a cycle";
    }

    return 0;
}