// // Write a C++ program to print Fibonacci series up to n terms using loop. 

// // Input
// // N = 10
// // Output
// // Fibonacci series: 
// // 0, 1, 1, 2, 3, 5, 8, 13, 21, 34
// Fibonacci series is a series of numbers where the current number is the sum of previous two terms. For Example: 0, 1, 1, 2, 3, 5, 8, 13, 21, … , (n-1th + n-2th).

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    //int fib = 0;
    int a = 0;
    int b = 1;
    int c = 0;
    for(int i = 1;i<=n;i++){
        cout<<c<<" ";
        a=b;
        b=c;
        c = a+b;
    }
}