// write a C++ program to input number from user and check number is palindrome or not using loop. 

// Input
// num = 121
// Output
// 121 is palindrome

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int rev = 0;
    int num;
    num = n;
    while(n != 0){
        rev = (rev * 10) + (n % 10);
        n = n / 10;
    }
    if(rev == num){
        cout<<"palindrome"<<endl;
    }
    else{
        cout<<"Not Palindroem"<<endl;
    }
    return 0;
}
