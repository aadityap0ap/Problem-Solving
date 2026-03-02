#include<bits/stdc++.h>
using namespace std;

int n;
string binary;

void solve(){
    while(n > 0){
       binary += to_string(n % 2);
        n = n / 2;
    }
}

int main(){
    cin>>n;
    solve();
    reverse(begin(binary),end(binary));
    cout<<binary<<endl;
    return 0;
}

/**
 * Time Complexity (TC): O(log₂(n)) ≈ O(log n)
 *
 * Why?
 * Because in every iteration:
 *      n = n / 2
 *
 * If:
 *      n = n / b
 * then number of iterations = log_b(n)
 *
 * Here b = 2,
 * so iterations = log₂(n)
 *
 * Also, reverse(binary.begin(), binary.end())
 * takes O(k) time where k = number of binary digits.
 *
 * Since number of binary digits = log₂(n),
 * reverse also takes O(log n).
 *
 * So total time:
 *      O(log n) + O(log n) = O(log n)
 *
 * Final TC = O(log n)
 *
 * --------------------------------------------------
 *
 * Space Complexity (SC): O(log n)
 *
 * Why?
 * Because we are storing the binary representation of n
 * inside a string.
 *
 * Number of binary digits of n = log₂(n).
 *
 * So the string stores log₂(n) characters.
 *
 * Therefore,
 * SC = O(log n)
 */