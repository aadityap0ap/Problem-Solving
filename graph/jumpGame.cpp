#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<queue>

using namespace std;
using state = pair<int,int>;

int n,d; //n-->no of elements in the array.....d-->the no of nodes we are using as a reference point
vector<int>arr;
set<state>g;


int main(){
    cin>>n>>d;
    arr.resize(n);
    g.resize();
    for(int i = 0;i<n;i++){
        cin>>arr[i]>>" ";
    }
    for(int i = 0;i<arr.size();i++){
        if(!g[])
    }

    return 0;
}