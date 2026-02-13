#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int minJumps(vector<int>& arr) {
    int n = arr.size();
    if (n == 1) return 0;

    // Create map of value -> indices
    vector<vector<int>> mp(n); // We'll dynamically add indices for simplicity
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < mp.size(); j++) {
            if (!mp[j].empty() && arr[mp[j][0]] == arr[i]) {
                mp[j].push_back(i);
                found = true;
                break;
            }
        }
        if (!found) {
            vector<int> v;
            v.push_back(i);
            mp.push_back(v);
        }
    }

    vector<int> dist(n, INT_MAX);
    queue<int> q;
    dist[0] = 0;
    q.push(0);

    while (!q.empty()) {
        int idx = q.front(); q.pop();

        if (idx == n - 1) return dist[idx];

        // Move to adjacent indices
        if (idx + 1 < n && dist[idx + 1] > dist[idx] + 1) {
            dist[idx + 1] = dist[idx] + 1;
            q.push(idx + 1);
        }
        if (idx - 1 >= 0 && dist[idx - 1] > dist[idx] + 1) {
            dist[idx - 1] = dist[idx] + 1;
            q.push(idx - 1);
        }

        // Move to same-value indices
        for (int i = 0; i < mp.size(); i++) {
            if (!mp[i].empty() && arr[mp[i][0]] == arr[idx]) {
                for (int j = 0; j < mp[i].size(); j++) {
                    int sameIdx = mp[i][j];
                    if (dist[sameIdx] > dist[idx] + 1) {
                        dist[sameIdx] = dist[idx] + 1;
                        q.push(sameIdx);
                    }
                }
                // Clear indices to avoid revisiting
                mp[i].clear();
                break;
            }
        }
    }

    return -1;
}

int main() {
    vector<int> arr = {100, -23, -23, 404, 100, 23, 23, 23, 3, 404};
    cout << "Minimum jumps: " << minJumps(arr) << endl;
    return 0;
}


/*
        Minimum Spanning Tree (MST)
            A Minimum Spanning Tree of a weighted, connected, undirected graph is:
        
        Spanning Tree:
            A subgraph that connects all vertices of the graph.
            Has exactly V - 1 edges (where V is number of vertices).
            Contains no cycles.
        
        Minimum:
            Among all possible spanning trees, the MST has the minimum possible total edge weight (sum of weights of all edges in the tree).
            
            
        Key Point::
         MST only works on undirected and weighted graph
         If the question involves connecting nodes with minimum cost it is pointing to MST
         
            
            
        Two Algorithm: 
        1. Kruskal's --->  O( E*LogE )
        2. Prim's    --->  O( E*LogV )
        
        
        there can be multiple MST possible for given pair of edges 
        if the edge weight of all the edges is different then only the MST is unique
        
        if the question ask is there multiple MST or not
        if you call the union function for same component with same edge weight that means there are multiple MST
*/


#include<bits/stdc++.h>
using namespace std;
using state = pair<int,int>;
vector<pair<int,state>> edges;
vector<int> parent;
vector<int> ranks;
int cost = 0;

void input(int n , int e){
    for( int i = 0 ; i< e ;i ++ ){
        int u , v , w;
        cin>> u >> v >> w;
        edges.push_back({u,{v,w}});
    }
    parent.resize(n);
    for( int i = 0; i < n ; i++) parent[i] = i;
    ranks.assign(n,0);
}

void print(int n , int e ){
    
    cout<< "Input edges are: " << endl;
    for( int i = 0; i < e ;i++ ){
        int u = edges[i].first;
        int v = edges[i].second.first;
        int w = edges[i].second.second;
        cout<< u << "---> { " << v << "," << w << " }" << endl;
    }
}

int find(int x){
    if( x == parent[x] ) return x;
    return parent[x] = find(parent[x]);
}

void Union( int u , int v , int w){
    int u_parent = find(u);
    int v_parent = find(v);
    
    if( u_parent == v_parent ){
        // can reach from some other way 
        return ;
    }
    
    int u_rank = ranks[u_parent];
    int v_rank = ranks[v_parent];
    
    if( u_rank >= v_rank ){
        parent[v_parent] = u_parent;
        if( u_rank == v_rank ) ranks[u_parent]++;
    }
    else{
        parent[u_parent] = v_parent;
    }
    
    cost += w;
}


void Kruskal(int e){
    // kruskal Algorithm helps us to connect all the nodes of a graph in acyclic manner 
    // and with minimum cost 
    
    /*
    
        it is an greedy appraoch where we find create those edges which have the least weight 
        means at first we assume no node is connected to anyone and we start connecting nodes which 
        have minimum edge weight between them
        
        Connecting two nodes/component can be done very efficiently with the help of DSU algo
        we don't care about the actuall connection, we are concern about the total edges weight should
        be minimum
        
        
        Why we use DSU : 
        ALgo says at first we assume we havn't connected any nodes and starts connecting nodes with minimum 
        edges weights ( connecting nodes points to DSU firstly )
        then if say we have already reached to v through u to check this without DSU we need to DFS(u) which 
        might take o(n) time to check if we can alrady reach to v from u or not which DSU's find function 
        can tell us in O(1) time complexity 
    */
    
    sort(edges.begin(), edges.end(), [](pair<int,state> &a , pair<int,state> &b){
        return a.second.second < b.second.second;
    });
    
    
    // we have sorted the edges and now simply traverse through all the edges and combine them
    // when you combine two nodes simply add the edge weight to the cost

    for( int i = 0; i < e ; i++ ){
        int u = edges[i].first;
        int v= edges[i].second.first;
        int w = edges[i].second.second;
        Union(u,v,w);
    }
    
}



int main(){
    int n , e ;
    cin>> n >> e;
    
    input(n,e);
    print(n,e);
    Kruskal(e);
    
    
    cout<< "Minimum cost to connect all cities is : " << cost << endl;
    
    // next question could be printing all the edges we made
    
    
    return 0;
}