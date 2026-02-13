#include<bits/stdc++.h>
using namespace std;

void reverseString(string s, int index){
    if(index == s.length()) return;
    reverseString(s,index+1);
    cout<<s[index]<<" ";
}

int main(){
    string s;
    cin>>s;
    reverseString(s,0);
    cout<<endl;
    return 0;
}