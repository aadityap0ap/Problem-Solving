// Problem 5
// Write a C++ program to input electricity unit charge and calculate the total electricity bill according to the given condition:
// For first 50 units Rs. 0.50/unit
// For next 100 units Rs. 0.75/unit
// For next 100 units Rs. 1.20/unit
// For unit above 250 Rs. 1.50/unit
// An additional surcharge of 20% is added to the bill.

#include<bits/stdc++.h>
using namespace std;

int main(){
    float n;
    cin>>n;
    float price = 0;
   
    if(n <= 50){
        price = n * 0.50;
    }
    else if(n <= 150){
        price = 25 + ((n-50) * 0.75); 
    }
    else if(n<= 250){
        price = 100 + ((n - 150) * 1.20);
    }
    else{
        price = 220 + ((n - 250)* 1.50);
    }
    float tax = price * 0.20;
    price += tax;
    cout<<price<<endl;
    return 0;
}