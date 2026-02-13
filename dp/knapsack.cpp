//this is a solution for the problem where we can take one item only once
// #include<iostream>
// #include<climits>
// using namespace std;

// int n,target;
// int wt[10010], value[10010];
// int dp[10010][10010];


// int rec(int i ,int w){
//     //pruning

//     //basecase
//     if (i == n) return 0;

//     //cache check
//     if (dp[i][w] != -1) return dp[i][w];
//     //int ans = 0;
//      int ans = rec(i + 1, w); // skip
//     //transition
//     if (w + wt[i] <= target) {
//         ans = max(ans, value[i] + rec(i + 1, w + wt[i]));
//     }
//     // save and return
//     return dp[i][w] = ans;
// }

// void solve(){
//     cin>>n;
//     cin>>target;
//     for(int i = 0;i<n;i++){
//         cin>>wt[i]>>value[i];
//     }
//      // initialize dp with -1
//     for (int i = 0; i <= n; i++) {
//         for (int j = 0; j <= target; j++) {
//             dp[i][j] = -1;
//         }
//     }

//     cout << rec(0, 0) << "\n";
// }


//this is for the questions where we can take one option infinite numbers of times till we reach the target

#include<iostream>
#include<climits>
using namespace std;

int n,target;
int wt[10010], value[10010];
int dp[10010][10010];


int rec(int i ,int w){
    //pruning

    //basecase
    if (i == n) return 0;

    //cache check
    if (dp[i][w] != -1) return dp[i][w];
    //int ans = 0;
     int ans = rec(i + 1, w); // skip
    //transition
    if (w + wt[i] <= target) {
        ans = max(ans, value[i] + rec(i, w + wt[i]));
    }
    // save and return
    return dp[i][w] = ans;
}

void solve(){
    cin>>n;
    cin>>target;
    for(int i = 0;i<n;i++){
        cin>>wt[i]>>value[i];
    }
     // initialize dp with -1
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= target; j++) {
            dp[i][j] = -1;
        }
    }

    cout << rec(0, 0) << "\n";
}


int main(){
     solve();
    
    return 0;
}