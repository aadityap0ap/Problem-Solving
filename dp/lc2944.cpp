// q--> minimum mnumber of coin for fruits
#include<iostream>
using namespace std;

int n;
int arr[10010];
int dp[10010][101];

int rec(int level,int total_coins_used){
    //Pruning
    
    //Base Case
    if(level == arr.size()-1){
        return 0;
    }
    //Cache Check
    if(dp[level][total_coins_used] != -1){
        return dp[level][total_coins_used];
    }
    //Transition
    
    //Save and return
}


void solve(){
    cin>>n;
    for(int i = 0;i<n;i++){
        cin>>arr[i];
    }
}

int main(){
    solve();
    return 0;
}