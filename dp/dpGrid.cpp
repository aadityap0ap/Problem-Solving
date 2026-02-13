#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int r,c;
vector<vector<int>>grid;
vector<vector<int>>dp;

int solve(int row,int col){
    //pruning
    if(row>=r || col>= c){ // this will check whether we had gone out of bound or not;
        return INT_MIN;
    }
    //basecase
    if(row == r-1 && col == c -1){ // this will check whether we had reached or destination or not;
        return grid[row][col];
    }
    //cache check
    if(dp[row][col] != -1){
        return dp[row][col];
    }
    //transition
    int right = solve(row,col+1);
    int down = solve(row + 1,col);

    //save and return
    return dp[row][col] = grid[row][col] + max(right,down);
}

int main(){
    cin>>r>>c;
    grid.resize(r,vector<int>(c));
    dp.assign(r+1,vector<int>(c+1,-1));
    for(int i = 0;i<r;i++){
        for(int j = 0;j<c;j++){
            cin>>grid[i][j];
        }
    }

    // for(int i = 0;i<r;i++){
    //     for(int j = 0;j<c;j++){
    //         cout<<grid[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    cout << solve(0, 0) << endl; 
    


    return 0;
}