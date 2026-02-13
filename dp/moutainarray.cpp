#include<iostream>
#include<vector>
using namespace std;

int n;
vector<int>arr;
vector<int>dp_inc;
vector<int>dp_dec;
vector<int>parent_inc;
vector<int>parent_dec;
int solve_inc(int index){
        //basecase
        if(index == n){
            return 0;
        }
        //cache check
        if(dp_inc[index] != -1){
            return dp_inc[index];
        }
        //transititon
        int count = 1;
        parent_inc[index] = -1;
        for(int prev_index = 0;prev_index < index;prev_index++){
            if(arr[prev_index] < arr[index]){
                int temp =  1 + solve_inc(prev_index);
                if(temp > count){
                    count = temp;
                    parent_inc[index] = prev_index;
                }
            }
        }
        //save and return
        return dp_inc[index] = count;
    }

    int solve_dec(int index){
        //basecase
        if(index == n){
            return 0;
        }
        //cache check
        if(dp_dec[index] != -1){
            return dp_dec[index];
        }
        //transititon
        int count = 1;
        parent_dec[index] = -1
        for(int next_index = index+1;next_index < n;next_index++){
            if(arr[next_index] < arr[index]){
                int temp  =  1 + solve_dec(next_index);
                if(temp > count){
                    count = temp;
                    parent_dec[index] = next_index;
                }
            }
        }
        //save and return
        return dp_dec[index] = count;
    }



void solve(){
    cin>>n;
    arr.resize(n);
    for(int i= 0;i<n;i++){
        cin>>arr[i];
    }
    dp_inc.assign(n,-1);
    dp_dec.assign(n,-1);
    parent_inc.assign(n,-1);
    parent_dec.assign(n,-1);
    int best = 0;
    
}

int main(){
    solve();
    return 0;
}