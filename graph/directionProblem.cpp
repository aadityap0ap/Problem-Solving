#include<iostream>
#include<vector>
#include<deque>
#include<climits>
using namespace std;

int n,m;
vector<vector<char>>grid;
vector<vector<int>>dist;

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

bool isValid(int valid_row,int valid_column){
    return valid_row>=0 && valid_row<n && valid_column>=0 && valid_column<m;
}

int findWeight(pair<int,int> node,int new_row, int new_col){
    int cr = node.first;
    int cc = node.second;
     if(new_row == cr&& new_col == (cc+1)&& grid[cr][cc] == 'R'){
        return 0;
    }
    else if(new_row == cr&& new_col == (cc - 1)&& grid[cr][cc] == 'L'){
        return 0;
    }
    else if(new_row == (cr+1)&& new_col == cc&& grid[cr][cc] == 'B'){
        return 0;
    }
    else if(new_row == (cr-1)&& new_col == cc&& grid[cr][cc] == 'U'){
        return 0;
    }
    else{
        return 1;
    }
}

int main(){
    cin>>n>>m;
    grid.resize(n,vector<char>(m));
    dist.assign(n,vector<int>(m,INT_MAX));
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            cin>>grid[i][j]; 
        }
    }
    deque<pair<int,int>>q;
    q.push_back({0,0});
    dist[0][0] = 0;
    while(!q.empty()){
        pair<int,int> node = q.front();
        q.pop_front();
        for(int i = 0;i<4;i++){
            int new_row = node.first+dr[i];
            int new_col = node.second+dc[i];
           if(!isValid(new_row,new_col)){
            continue;
        }
        int weight = findWeight(node,new_row,new_col);
        if(dist[new_row][new_col] > dist[node.first][node.second]+weight){
            dist[new_row][new_col] = dist[node.first][node.second]+weight;
            if(weight == 0){
                q.push_front({new_row,new_col});
            }
            else{
                q.push_back({new_row,new_col});
            }
         }
        }
    }
    //}
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << dist[i][j] <<" ";
        }
        cout << "\n";
    }

     return 0;
    }