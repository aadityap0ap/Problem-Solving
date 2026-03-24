// Write a program to find maximum between three numbers.

// Input
// Input num1 : 10
// Input num2 : 20
// Input num3 : 15
// Output
// Maximum among all three numbers is 20

#include<bits/stdc++.h>
using namespace std; 

int main(){
    int num1,num2,num3;
    cin>>num1>>num2>>num3;
    int num;
    if(num1 > num2 && num1 > num3)num = num1;
    else if(num3 > num1 && num3 > num2)num = num3;
    else num = num2;
    cout<<"Maximum Among all three number is"<<num<<endl;
    return 0;
}