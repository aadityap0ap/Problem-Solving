// Write a C++ program to input a character from user and check whether given character is alphabet, digit or special character.

// Input
// Input any character: 3
// Output
// Character is Digit

#include<bits/stdc++.h>
using namespace std;

int main(){
    char c;
    cin>>c;
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        cout<<"Character is Alphabet"<<endl;
    }
    else if((c >= '0' && c <= '9')){
        cout<<"Character is Digit"<<endl;
    }
    else{
        cout<<"Character is Special Character"<<endl;
    }
}