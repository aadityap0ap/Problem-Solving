#include<iostream>
#include<vector>

using namespace std;
using state = pair<int,int>;

int n,e;
vector<state>g;
vector<int>rep; // it is used to representative for each node
vector<int>r; // it is used to store the rank of each node or in other word the height
vector<int>s; //it is used to store the size of a particular connected components
int components;


int find_representative(int i){
    if(i == rep[i]){
        return i;
    }
    else{
        return rep[i] = find_representative(rep[i]);
    }
}

void DSU(int x,int y){
    int rep_x = find_representative(x);
    int rep_y = find_representative(y);
    if(rep_x == rep_y) return; //if both the rep of x and y are same then we can say that they are of same components
    else{
        if(r[rep_x] > r[rep_y]){
            rep[rep_y] = rep[rep_x];
            s[rep_x]+= s[rep_y];
        }
       else if(r[rep_x] < r[rep_y]){
            rep[rep_x] = rep[rep_y];
            s[rep_y]+= s[rep_x];
        }
        else{
            rep[rep_x] = rep[rep_y];
            s[rep_x] += s[rep_y];
            r[rep_x]++;
        }
    }
    components--;
}

int main(){
    cin>>n>>e;
    rep.resize(n);
    s.assign(n,1);
    r.assign(n,0);
    components = n;
    for(int i = 0;i<n;i++){
        rep[i] = i;
    }
     for( int i = 0 ; i < e ;i ++ ){
        int u , v ;
        cin>> u >> v;
        g.push_back({u,v});
        DSU(u,v);
    }
    
    
    for( int i = 0 ; i < e ;i++ ){
        cout<< g[i].first << "--> " << g[i].second <<endl;
    }
    cout<<"The total components are"<<components<<endl;
   for(int i = 0;i<n;i++){
    cout<<"The rep of "<<i<<"is"<<rep[i]<<" "<<endl;
   }
   cout<<endl;
   for(int i = 0;i<n;i++){
    cout<<"The size of "<<i<<"is"<<s[i]<<" "<<endl;
   }
   cout<<endl;
   for(int i = 0;i<n;i++){
    cout<<"The rank of "<<i<<"is"<<r[i]<<" "<<endl;
   }
   cout<<endl;
  


  return 0;
}