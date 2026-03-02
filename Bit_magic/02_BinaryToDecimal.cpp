#include<bits/stdc++.h>
using namespace std;

string binary;
int decNum;

void solve(){
    //101
    int n = binary.length();
    int p = 1;
    for(int i = n-1;i>=0;i--){
        decNum += p * (binary[i] - '0');
        p = p*2; 
    }
}

int main(){
    cin>>binary;
    decNum = 0;
    solve();
    cout<<decNum<<endl;
    return 0;
}

/**
 * Time Complexity (TC): O(n)
 *
 * Where n = length of the binary string.
 *
 * Why?
 * Because we are traversing the entire binary string once
 * using a for loop:
 *
 * for(int i = n-1; i >= 0; i--)
 *
 * The loop runs exactly n times.
 *
 * Inside the loop, all operations:
 *      (binary[i] - '0')
 *      multiplication
 *      addition
 * are constant time operations → O(1)
 *
 * So total TC = O(n)
 *
 * --------------------------------------------------
 *
 * Space Complexity (SC): O(1)
 *
 * Why?
 * We are not using any extra data structure
 * that depends on input size.
 *
 * We only use:
 *      int n
 *      int p
 *      int decNum
 *
 * These are constant variables.
 *
 * Therefore,
 * SC = O(1)
 */