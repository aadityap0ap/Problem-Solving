// Write a C++ program to print all Prime numbers between 1 to n using loop

// Input
// end = 20
// Output
// Prime numbers between 1-20: 2, 3, 5, 7, 13, 17, 19

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n = 0;
   cin>>n;
   cout<<"Prime numbers between 1 to "<<n<<"is"<<" ";
    for(int i = 2;i<=n;i++){
         int factCount = 0;
        for(int j = 1;j<=i;j++){
            if(i % j == 0)factCount++;
        }
        if(factCount == 2){
            cout<<i<<" ";
        }
    }
}