#include<iostream>
#include<unordered_map>
#include<algorithm>
using namespace std;

int n,target;//n-->size of array
int arr[10010];
unordered_map<int, unordered_map<int,int>> dp;
// Using 2-level unordered_map for memoization: dp[i][curr_sum]
// Reason:
// 1. The state of our recursion is defined by two parameters: 
//    - i: current index in the array
//    - curr_sum: the current sum at this index
// 2. We need to store results for each unique combination of (i, curr_sum).
// 3. If we used only dp[curr_sum], we would overwrite results from different indices i,
//    leading to incorrect answers.
// 4. unordered_map allows us to handle negative sums and dynamically store only 
//    the sums that actually occur, which is memory efficient.
// Conclusion: dp[i][curr_sum] ensures correct memoization for all recursion states.


int rec(int i,int curr_sum){
    //pruning
    //basecase
    if(i==n){
        if(curr_sum == target){
            return 1;
        }
        else{
            return 0;
        }
    }
    //cache check
     if(dp[i].count(curr_sum)) return dp[i][curr_sum];
    //transititon
    int plus = rec(i+1,curr_sum + arr[i]);
    int minus = rec(i+1,curr_sum - arr[i]);
    //save and return
    return dp[i][curr_sum] = plus + minus;
}

void solve(){
    cin>>n>>target;
    for(int i = 0;i<n;i++){
        cin>>arr[i];
    }
    cout<<rec(0,0)<<endl;
}

int main(){
    solve();

    return 0;
}