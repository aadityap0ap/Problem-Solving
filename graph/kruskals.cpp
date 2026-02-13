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
            
*/


#include<bits/stdc++.h>
using namespace std;
using state = pair<int,int>;
int n , e ;
vector<pair<int,state>> edges;
vector<int>r;
vector<int>s;
vector<int>rep;
int cost = 0;

void input(int n , int e){
    for( int i = 0 ; i< e ;i ++ ){
        int u , v , w;
        cin>> u >> v >> w;
        edges.push_back({u,{v,w}});
    }
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

int find_representative(int i){
    if(i == rep[i]){
        return i;
    }
    else{
        return rep[i] = find_representative(rep[i]);
    }
}

void DSU(int x,int y,int w){
    int rep_x = find_representative(x);
    int rep_y = find_representative(y);
    if(rep_x == rep_y) return; //if both the rep of x and y are same then we can say that they are of same components
    else{
        if(r[rep_x] > r[rep_y]){
            rep[rep_y] = rep[rep_x];
           
        }
       else if(r[rep_x] < r[rep_y]){
            rep[rep_x] = rep[rep_y];
            
        }
        else{
            rep[rep_x] = rep[rep_y];
            r[rep_y]++;
        }
    }
    cost+=w;;
}
bool cmp(const pair<int,pair<int,int>> &a, const pair<int,pair<int,int>> &b) {
    return a.second.second < b.second.second;
}

void kruskals(){
// In Kruskal's algorithm, we are building an MST by adding edges in increasing order of weight.
// To avoid cycles, before adding an edge (u, v) we must check if u and v are already in the same connected component.

// Naive way: Use DFS/BFS to check if u and v are connected
//   - This would increase the time complexity (O(V+E) per check).

// Efficient way: Use DSU (Disjoint Set Union / Union-Find)
//   - DSU can quickly (almost O(1)) tell if u and v belong to the same component
//   - If they are in different components, we union them (merge the sets)
//   - This lets us efficiently grow the MST without creating cycles.

// So, DSU is used in Kruskal's to efficiently keep track of connected components 
// while adding edges to form the MST.
// Kruskal’s is basically connecting components, which is exactly what DSU is built for


sort(edges.begin(), edges.end(), cmp);
rep.resize(n);
r.assign(n,0);
s.assign(n,1);
for(int i = 0;i<n;i++){
    rep[i] = i;
}
for(int i = 0;i<e;i++){
    int u = edges[i].first;
    int v = edges[i].second.first;
    int w = edges[i].second.second;
    DSU(u,v,w);
}




}

int main(){
    
    cin>> n >> e;
    
    input(n,e);
    print(n,e);
    kruskals();
    cout<<cost<<endl;
    
    
    
    return 0;
}