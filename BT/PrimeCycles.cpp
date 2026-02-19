#include <bits/stdc++.h>
using namespace std;

int n;
bool taken[20];
vector<int> prime;
int cnt = 0;

bool isPrime(int x) {
    return x == 2 || x == 3 || x == 5 || x == 7 ||
           x == 11 || x == 13 || x == 17 || x == 19 ||
           x == 23 || x == 29 || x == 31 || x == 37;
}



void solve(){
    //base case
    if(prime.size() == n){
        if(isPrime(prime[0] + prime.back())){
            cnt++;
        }
        return;
    }
    for(int i = 2;i<=n;i++){
        if(!taken[i] && isPrime(i + prime.back())){
            taken[i] = true;
            prime.push_back(i);
            solve();
            prime.pop_back();
            taken[i] = false;
        }
    }
}


int main() {
    cin >> n;
    prime.push_back(1);
    taken[1] = true;
    solve();
    cout <<cnt<< endl;
    return 0;
}
