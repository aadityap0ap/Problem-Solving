// Problem 4
// Write a C++ program to input a number from user and find Prime factors of the given number using loop.

// Input
// num = 10
// Output
// Prime factors of 10: 2, 5

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
   
    cout<<"Prime Fctors of "<<n<<"is"<<" ";
    for(int i = 2;i<=n;i++){
         int factCount = 0;
        for(int j = 1;j<=i;j++){
            if(i % j == 0)factCount++;
        }
        if(factCount == 2 && (n % i == 0)){
            cout<<i<<" ";
        }
    }
    return 0;
}