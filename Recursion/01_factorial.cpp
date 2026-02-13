// #include<bits/stdc++.h>
// using namespace std;

// int fact(int n){
//     //base case
//     if(n<=1) return 1;
//     return n * fact(n-1);
// }

// int main(){
//     int n;
//     cin>>n;
//     cout<<fact(n)<<endl;
// }

//sol using tail recursion
// tail recursion --> form of recursion where the recusive call is the last operation performed in the function
#include<bits/stdc++.h>
using namespace std;

int solve(int n, int product){
    if(n <= 1) return product;
    return solve(n-1,product*n);
}

int main(){
    int n;
    cin>>n;
    cout<<solve(n,1)<<endl;
    return 0;
}