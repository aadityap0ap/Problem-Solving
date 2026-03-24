// Problem 4
// Write a C++ program to find power of a number using for loop. 

// Input
// base = 2
// exponent = 5
// Output
// 2 ^ 5 = 32

#include<bits/stdc++.h>
using namespace std;

int main(){
    int base,exp;
    cin>>base>>exp;
    int p = 1;
    // while(exp != 0){
    //     p *= base;
    //     exp--;
    // }
    //using for loop
    for(int i = 1;i<=exp;i++){
        p *= base;
    }
    cout<<p<<endl;
    return 0;
}