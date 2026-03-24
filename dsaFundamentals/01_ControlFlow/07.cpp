// Problem 2
// Write a C++ program to input a number from the user and calculate product of its digits. 

// Input
// num = 1234
// Output
// Product of digits: 24

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int product = 1;
    while(n>=10){
        product *= n % 10;
        n = n / 10;
    }
    product *= n;
    cout<<product<<endl;
    return 0;
}