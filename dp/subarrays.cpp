//you are given an array and you have to divide it into k subarrays such that sum of the minimum of each subarray is as small as possible
#include<iostream>
#include<climits>
using namespace std;

int n; //no of elements in an array
int arr[10010];
int dp[1001][101];

int rec(int i,int x){ //i is the element we are starting and x is the no of partition
    //pruning
    //basecase
    if(i==-1){ //this will check whether we have checked all element or not
        if(x==0){//this will check whether we had done the required no of partition or not
            return 0;
        }
        else{ // this will check whether we have done the partition more than required or not---> if we have done more than requires than this will return 1e9
            return INT_MAX;
        }
    }
    //cache check
    //transition
    int ans = INT_MAX;
    for(int j = 0;j<n;j++){
       
    }
    //save and return
     
}


void solve(){
    cin>>n;
    for(int i = 0;i<n;i++){
        cin>>arr[i];
    }

}


int main(){
    solve();
    return 0
}