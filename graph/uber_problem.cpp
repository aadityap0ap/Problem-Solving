#include<bits/stdc++.h>
using namespace std;

using state = pair<int,int>;

int n,e;
vector<vector<pair<int,state>>> arr;     
vector<int> mini;                        
vector<int> cost;                        
int capacity = 15;
set<state> visited;

void Dikstra(state start){
    visited.insert(start);
    priority_queue<pair<int,state>, vector<pair<int,state>>, greater<pair<int,state>>> que;
    que.push({0,start});
    mini[start.second] = 0;

    while(!que.empty()){
        auto curr = que.top();
        que.pop();
        int cost_till_curr = curr.first;
        int fuel_left_till_curr = curr.second.first;
        int curr_node = curr.second.second;

        for(auto &v : arr[curr_node]){
            int neigh = v.first;
            int petrol_needed = v.second.first;

            if(petrol_needed <= fuel_left_till_curr){
                if(!visited.count({fuel_left_till_curr - petrol_needed ,neigh})){
                    visited.insert({fuel_left_till_curr - petrol_needed ,neigh});
                    que.push({cost_till_curr,{fuel_left_till_curr - petrol_needed ,neigh}});
                    mini[neigh] = min(mini[neigh], cost_till_curr);
                }
            }
            else{
                int fuel_required = petrol_needed - fuel_left_till_curr;
                if(fuel_required <= capacity - fuel_left_till_curr){
                    int req_cost = fuel_required * cost[curr_node];
                    mini[neigh] = min(mini[neigh], cost_till_curr + req_cost);
                    if(!visited.count({0,neigh})){
                        visited.insert({0,neigh});
                        que.push({cost_till_curr + req_cost,{0,neigh}});
                    }
                }
            }
        }
    }
}

int main(){
    cin >> n >> e;
    arr.resize(n);
    cost.resize(n);
    mini.assign(n, INT_MAX);

    for (int i = 0; i < n; i++) {
        cin >> cost[i]; // cost of petrol at each node
    }

    for (int i = 0; i < e; i++) {
        int u, v, p, d;
        cin >> u >> v >> p >> d;
        arr[u].push_back({v,{p, d}});
        arr[v].push_back({u,{p, d}});
    }

    Dikstra({0, 0}); //{fuel_left,node}

    for (int i = 0; i < n; i++) {
        cout << "Min cost to reach node " << i << " = " << mini[i] << "\n";
    }

    return 0;
}
