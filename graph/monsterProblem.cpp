#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;

int row,column;
vector<vector<char>>arr;
pair<int,int>person; //only one person is on the grid thats why we are not using vector here but in monsters more than one monster can be on grid
vector<pair<int,int>>monsters;
vector<vector<bool>>visited;
//we are creating two different grid for person and monster to store their time to reach a particular coordinate.
vector<vector<int>>distance_monsters;
vector<vector<bool>>visited_monsters;
vector<vector<int>>distance_person;
vector<vector<bool>>visited_person;



int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool isValid(int vr, int vc){
    return (vr >= 0 && vr < row && vc >= 0 && vc < column && arr[vr][vc] != '#');
}

void bfs_Monsters(){
    queue<pair<int,int>>que;
    for(int i= 0;i<monsters.size();i++){
        int mr = monsters[i].first;
        int mc = monsters[i].second;
        que.push({mr,mc});
        visited_monsters[mr][mc] = true;
        distance_monsters[mr][mc] = 0;
    }
    while(!que.empty()){
        pair<int,int>current = que.front();
        que.pop();
        for(int k = 0;k<4;k++){
            int r = current.first + dr[k];
            int c = current.second + dc[k];
            if(isValid(r,c) && visited_monsters[r][c] == false){
                visited_monsters[r][c] = true;
                distance_monsters[r][c] = distance_monsters[current.first][current.second] + 1;
                que.push({r,c});
            }
        }
    }
}

int main(){
   
    cin>>row>>column;
    arr.resize(row,vector<char>(column));
    visited.assign(row,vector<bool>(column,false));
    distance_monsters.assign(row,vector<int>(column,INT_MAX));
    distance_person.assign(row,vector<int>(column,INT_MAX));
    visited_monsters.assign(row,vector<bool>(column,false));
    visited_person.assign(row,vector<bool>(column,false));
    for(int i = 0;i<row;i++){
        for(int j = 0;j<column;j++){
            char element;
            cin>>element;
            if(element=='P'){
                person={i,j};
            }
            if(element =='M'){
                monsters.push_back({i,j});
            }
            arr[i][j] = element;
        }
    }

    bfs_Monsters();

//input array
cout<<"The Input array is :"<<endl;
for(int i = 0;i<row;i++){
    for(int j = 0;j<column;j++){
        cout<<arr[i][j]<<" ";
    }
    cout<<endl;
}  

cout << "\nVisited Monsters:\n";
for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++){
        cout << visited_monsters[i][j] << " ";
    }
    cout << endl;
}

cout << "\nDistance Monsters:\n";
for(int i = 0; i < row; i++){
    for(int j = 0; j < column; j++){
        if(distance_monsters[i][j] == INT_MAX)
            cout << "INF ";
        else
            cout << distance_monsters[i][j] << " ";
    }
    cout << endl;
}

    return 0;
}
