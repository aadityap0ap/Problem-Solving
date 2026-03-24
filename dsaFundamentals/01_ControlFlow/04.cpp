// Write a C++ program to input sides of a triangle and check whether a triangle is equilateral, scalene or isosceles triangle.

// Input
// Input first side: 30
// Input second side: 30
// Input third side: 30
// Output
// Triangle is equilateral triangle

// Properties of triangle

// A triangle is said Equilateral Triangle, if all its sides are equal. If a, b, c are three sides of triangle. Then, the triangle is equilateral only if a == b == c.
// A triangle is said Isosceles Triangle, if its two sides are equal. If a, b, c are three sides of triangle. Then, the triangle is isosceles if either a == b or a == c or b == c.
// A triangle is said Scalene Triangle, if none of its sides are equal.

#include<bits/stdc++.h>
using namespace std;

int main(){
    int fs,ss,ts;
    cin>>fs>>ss>>ts;
    if(fs == ss && ss == ts ){
        cout<<"The given dimensions are of Equilateral triangle"<<endl;
    }
    else if(fs == ss || ss == ts || ts == fs){
        cout<<"The given dimensions are of Isosceles Triangle"<<endl;
    }
    else{
        cout<<"The given dimensions are of scalene triangle"<<endl;
    }
    return 0;
}