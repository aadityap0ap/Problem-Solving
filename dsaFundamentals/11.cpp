// Problem 1
// Write a Program to input a number from user and find all factors of the given number using for loop. 

// Input
// num = 12
// Output
// Factors of 12: 1, 2, 3, 4, 6, 12

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    cout<<"Factor of"<<n<<"is"<<" ";
    for(int i = 1;i<=12;i++){
        if(n % i == 0){
            cout<<i<<" ";
        }
    }
    return 0;
}