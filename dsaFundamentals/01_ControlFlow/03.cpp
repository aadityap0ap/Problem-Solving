// Write a C++ program to input amount from user and print minimum number of notes (Rs. 500, 100, 50, 20, 10, 5, 2, 1) required for the amount.

// Input
// 567890
// Output
// Total Number of Notes
// 500 = 1135
// 100 = 3
// 50 = 1
// 20 = 2
// 10 = 0
// 5 = 0
// 2 = 0
// 1 = 0

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int note500,note100,note50,note20,note10,note5,note2,note1;
    note500 = note100 = note50 = note20 = note10 = note5 = note2 = note1 = 0;
    if(n >= 500){
        note500 = n / 500;
        n = n - note500*500; 
    }
    if(n >= 100){
        note100 = n / 100;
        n -= note100 * 100;
    }
     if(n >= 50){
        note50 = n / 50;
        n -= note50 * 50;
    }
    if(n >= 20){
        note20 = n / 20;
        n -= note20 * 20;
    }
     if(n >= 10){
        note10 = n / 10;
        n -= note10 * 10;
    }
     if(n >= 5){
        note5 = n / 5;
        n -= note5 * 5;
    }
     if(n >= 2){
        note2 = n / 2;
        n -= note2 * 2;
    }
     if(n >= 1){
        note1 = n / 1;
        n -= note1 * 1;
    }
     cout<<"Total number of notes "<<endl;
    cout<<"500 ="<< note500<<endl;
    cout<<"100 ="<< note100<<endl;
    cout<<"50 ="<< note50<<endl;
    cout<<"20 ="<< note20<<endl;
    cout<<"10 ="<< note10<<endl;
    cout<<"5 ="<< note5<<endl;
    cout<<"2 ="<< note2<<endl;
    cout<<"1 ="<< note1<<endl;
return 0;
}