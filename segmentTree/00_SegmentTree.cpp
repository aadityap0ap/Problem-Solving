#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class SegmentTree{
private:
    vector<ll> tree;
    vector<ll> arr;
    int n;

    void build(int index, int left, int right){
        if(left == right){
            tree[index] = arr[left];
            return;
        }
        int mid = (left + right) / 2;
        build(2*index+1, left, mid);
        build(2*index+2, mid+1, right);
        tree[index] = tree[2*index+1] + tree[2*index+2];
    }

    ll query(int index, int left, int right, int ql, int qr){
        if(qr < left || ql > right) return 0; // no overlap
        if(ql <= left && right <= qr) return tree[index]; // complete overlap
        
        int mid = (left + right) / 2;
        ll left_res = query(2*index+1, left, mid, ql, qr);
        ll right_res = query(2*index+2, mid+1, right, ql, qr);
        return left_res + right_res;
    }

    void update(int index, int left, int right, int pos, ll val){
        if(left == right){
            arr[left] = val;
            tree[index] = val;
            return;
        }
        
        int mid = (left + right) / 2;
        if(pos <= mid)
            update(2*index+1, left, mid, pos, val);
        else
            update(2*index+2, mid+1, right, pos, val);

        tree[index] = tree[2*index+1] + tree[2*index+2];
    }

public:
    SegmentTree(vector<ll>& input){
        arr = input;
        n = arr.size();
        tree.resize(4*n);
        build(0,0,n-1);
    }

    ll getSum(int l, int r){
        return query(0,0,n-1,l,r);
    }

    void setValue(int pos, ll val){
        update(0,0,n-1,pos,val);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<ll> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    SegmentTree st(arr);

    while(m--){
        int t;
        cin >> t;

        if(t == 1){
            int i;
            ll val;
            cin >> i >> val;
            st.setValue(i, val);
        }
        else{
            int l, r;
            cin >> l >> r;
            cout << st.getSum(l, r-1) << "\n";
        }
    }

    return 0;
}
