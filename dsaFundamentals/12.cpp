// Write a program in C++ to input a number and check whether the number is prime number or not using for loop.

// Input
// num = 17
// Output
// 17 is a prime number.

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int total_factors = 0;
    // Edge case
    if(n <= 1){
        cout << n << " is not a prime number" << endl;
        return 0;
    }
    for(int i = 1;i<=n;i++){
        if(n % i == 0)total_factors++;
        if(total_factors > 2){
        cout<<n<<"is not a prime number"<<endl;
        return 0;
        }
    }
        cout<<n<<"is a prime number"<<endl;
    return 0;
}