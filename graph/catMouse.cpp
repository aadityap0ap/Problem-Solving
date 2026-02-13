#include <bits/stdc++.h>
using namespace std;

// Helper function to get parent states
vector<tuple<int,int,int>> parents(vector<vector<int>>& graph, int m, int c, int turn) {
    vector<tuple<int,int,int>> res;
    if(turn == 0) { // mouse just moved, parent was cat's turn
        for(int i = 0; i < graph[c].size(); i++){
            int pc_prev = graph[c][i];
            if(pc_prev == 0) continue; // cat cannot go to hole
            res.push_back(make_tuple(m, pc_prev, 1));
        }
    } else { // turn == 1, cat just moved, parent was mouse's turn
        for(int i = 0; i < graph[m].size(); i++){
            int pm_prev = graph[m][i];
            res.push_back(make_tuple(pm_prev, c, 0));
        }
    }
    return res;
}

int catMouseGame(vector<vector<int>>& graph) {
    int n = graph.size();
    const int DRAW = 0, MOUSE = 1, CAT = 2;

    vector<vector<vector<int>>> color(n, vector<vector<int>>(n, vector<int>(2, DRAW)));
    vector<vector<vector<int>>> degree(n, vector<vector<int>>(n, vector<int>(2, 0)));

    // Initialize degrees
    for(int m = 0; m < n; m++){
        for(int c = 0; c < n; c++){
            degree[m][c][0] = graph[m].size(); // mouse turn
            degree[m][c][1] = graph[c].size(); // cat turn
            for(int i = 0; i < graph[c].size(); i++){
                if(graph[c][i] == 0) degree[m][c][1]--; // cat cannot go to hole
            }
        }
    }

    queue<tuple<int,int,int,int>> q;

    // Base cases
    for(int i = 1; i < n; i++){
        // Mouse at hole -> mouse wins
        color[0][i][0] = MOUSE;
        color[0][i][1] = MOUSE;
        q.push(make_tuple(0, i, 0, MOUSE));
        q.push(make_tuple(0, i, 1, MOUSE));

        // Cat catches mouse -> cat wins
        color[i][i][0] = CAT;
        color[i][i][1] = CAT;
        q.push(make_tuple(i, i, 0, CAT));
        q.push(make_tuple(i, i, 1, CAT));
    }

    // BFS
    while(!q.empty()){
        tuple<int,int,int,int> state = q.front(); q.pop();
        int m = get<0>(state);
        int c = get<1>(state);
        int turn = get<2>(state);
        int result = get<3>(state);

        vector<tuple<int,int,int>> par = parents(graph, m, c, turn);
        for(int i = 0; i < par.size(); i++){
            int pm = get<0>(par[i]);
            int pc = get<1>(par[i]);
            int pt = get<2>(par[i]);

            if(color[pm][pc][pt] != DRAW) continue;

            if((pt == 0 && result == MOUSE) || (pt == 1 && result == CAT)){
                color[pm][pc][pt] = result;
                q.push(make_tuple(pm, pc, pt, result));
            } else {
                degree[pm][pc][pt]--;
                if(degree[pm][pc][pt] == 0){
                    color[pm][pc][pt] = (pt == 0) ? CAT : MOUSE;
                    q.push(make_tuple(pm, pc, pt, color[pm][pc][pt]));
                }
            }
        }
    }

    return color[1][2][0]; // initial state: mouse at 1, cat at 2, mouse turn
}
