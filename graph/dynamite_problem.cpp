#include<iostream>
#include<vector>
#include<climits>
#include<deque>
#include<queue>
#include<algorithm>

using namespace std;
using state = pair<int,int>;

int w,k;
int row,column;
int srcR,srcC,destR,destC;
int length = 0;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
vector<vector<char>>arr;
vector<vector<int>>dist;
vector<vector<int>>dist2;
vector<vector<bool>>visited;
vector<vector<state>>parent;
vector<vector<int>>ways;
vector<vector<int>>broken_walls;



bool isValid(int new_row,int new_col){
    return new_row >=0 && new_row < row && new_col>=0 && new_col < column;
}

void BFS_ShortestPath(){
    queue<state>q;
    q.push({srcR,srcC});
    visited[srcR][srcC] = true;
    dist[srcR][srcC] = 0;
    parent[srcR][srcC] = {-1,-1};
    ways[srcR][srcC] = 1;
    while(!q.empty()){
      state curr = q.front();
      q.pop();
      int r = curr.first;
      int c = curr.second;
      for(int i = 0;i<4;i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        if(!isValid(nr,nc) || arr[nr][nc]!='.') continue;
            if(dist[nr][nc] > dist[r][c] + 1){
                dist[nr][nc] = dist[r][c] + 1;
                parent[nr][nc] = {r,c};
                ways[nr][nc] = ways[r][c];  
                q.push({nr,nc});
            }
            else if(dist[nr][nc] == dist[r][c] + 1){
                ways[nr][nc] += ways[r][c];  
            }
        }
      }
    }

vector<state> constructPath(){
    vector<state>ans;
    state curr = {destR,destC};
    while(curr.first!=-1 && curr.second!=-1){
        ans.push_back({curr.first,curr.second});
        curr = parent[curr.first][curr.second];
    }
    reverse(ans.begin(),ans.end());
    return ans;
}


bool BFS(){
    queue<state>q;
    q.push({srcR,srcC});
    visited[srcR][srcC] = true;
    dist[srcR][srcC] = 0;
    parent[srcR][srcC] = {-1,-1};
    while(!q.empty()){
      state curr = q.front();
      q.pop();
      int r = curr.first;
      int c = curr.second;
      if(r == destR && c == destC){
        return true;
      }
      for(int i = 0;i<4;i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        if(isValid(nr,nc) && visited[nr][nc] == false && arr[nr][nc] =='.'){
            visited[nr][nc] = true;  
            q.push({nr,nc});
        }
         
      }
    }
    return false;

    }
    

int dynamite_req(){
    deque<pair<int,state>>que;
    broken_walls.assign(row,vector<int>(column,INT_MAX));
    broken_walls[srcR][srcC] = 0;
    que.push_back({0,{srcR,srcC}});
    while(!que.empty()){
        auto curr = que.front();
        que.pop_front();
        int wall_broken_till_now = curr.first;
        int r = curr.second.first;
        int c = curr.second.second;
        
    for(int i = 0;i<4;i++){
       // int neigh = arr[i][j];
        int nr =r+dr[i];
        int nc = c+dc[i];
          
        if(!isValid(nr,nc)) continue;
            if(arr[nr][nc] == '#'){
                w = 1;
            }
            else{
                w = 0;
            }
            if(broken_walls[nr][nc] > wall_broken_till_now + w){
               broken_walls[nr][nc] = wall_broken_till_now + w ;
                if(w == 1){
                    que.push_back({wall_broken_till_now+1,{nr,nc}});
                }
                else{
                    que.push_front({wall_broken_till_now,{nr,nc}});
                }
            }
        
    }
    //return dist[destR][destC];
}
return broken_walls[destR][destC];
}

void MinPath_with_K_WallsBroken(){
    queue<pair<int,state>>q;
    q.push({k,{srcR,srcC}});
    set<pair<int,state>>visited;
    visited.insert({k,{srcR,srcC}});
    dist2.assign(row,vector<int>(column,INT_MAX));
    dist2[srcR][srcC] = 0;
    while(!q.empty()){
        auto curr = q.top();
        int can_break = curr.first;
        int r = curr.second.first;
        int c = curr.second.second;
        for(int i = 0;i<4;i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(!isValid(nr,nc)) continue;
            int walls_used;
            if(arr[nr][nc] == '#'){
                walls_used = 1;
            }
            else{
                walls_used = 0;
            }
            int rem_walls = k - walls_used;
            if(rem_walls > 0 && !visited.count({rem_walls,{nr,nc}})){
                visited.insert({rem_walls,{nr,nc}});
                if(dist2[nr][nc] > dist2[r][c]+1){
                    dist2[nr][nc] = dist2[r][c] +1;
                    q.push({rem_walls,{nr,nc}});
                }
            }
        }
    }
}


int main(){
        // 1. Find if we can reach from S to E                         -->done
        // 2. Find the shortest path lenght if you can reach           -->done
        // 3. Print the shortest path                                  -->done
        // 4. Find the number of shortest path                         -->done
        // 5. Find the minimum number number of walls that needs to be broken to reach E -->done
        //6. If you are allowed to break K walls then find the shortest path to reach E


    cin>>row>>column;
    arr.resize(row,vector<char>(column));
    dist.assign(row,vector<int>(column,INT_MAX));
    visited.assign(row,vector<bool>(column,false));
    parent.assign(row,vector<state>(column,{-1,-1}));
    ways.resize(row,vector<int>(column,0));
    broken_walls.resize(row,vector<int>(column,INT_MAX));
    for(int i = 0;i<row;i++){
        for(int j = 0;j<column;j++){
            char element;
            cin>>element;
            arr[i][j] = element;
        }
    }

    // for(int  i= 0;i<row;i++){
    //     for(int j = 0;j<column;j++){
    //         cout<<arr[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    cin>>srcR>>srcC>>destR>>destC;
    if(BFS()){
        cout<<"We can reach from source to destination "<<endl;
        BFS_ShortestPath();
        cout<<"The lenght of shortest path"<<" "<<dist[destR][destC]<<endl;
        cout<<"The No of shortest path"<<" "<<ways[destR][destC]<<endl;
        vector<state>ans = constructPath();
            for(int i = 0;i<ans.size();i++){
                cout<<"("<<ans[i].first<<","<<ans[i].second<<")";
            }
            cout<<endl;
    }
    else{
        cout<<"We can not reach from source to destination"<<endl;
       //5 5

 return 0;
    }
    
    int count = dynamite_req();
     if(count == INT_MAX){
        cout<<"We cant reach even without breaking the wall"<<endl;
     }
     else{
        cout<<"The dynamites we need to use"<<" "<<count<<endl;
     }
    return 0;
}

