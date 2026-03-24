// Problem 1
// Write a C++ program to input a number and find the sum of first and last digit of the number using a loop. 

// Input
// num = 12345
// Output
// Sum of first and last digit = 6

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int sum = 0;
    sum += n % 10;
    n = n / 10;
    while(n>=10){
        n = n /10;
    }
    sum += n;
    cout<<sum<<endl;
    return 0;
}