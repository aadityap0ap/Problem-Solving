#include<bits/stdc++.h>
using namespace std;
using state = pair<int,int>;

vector<vector<char>> arr;
state start, finish;
vector<vector<int>> dist; // to each particular node
vector<vector<state>> parent;
vector<vector<int>> ways; // number of shortest paths
vector<vector<int>> broken_walls;
vector<vector<int>> dist2; // to each particular node

int k;




void input(int row, int column) {

	for( int i = 0 ; i < row ; i ++ ) {
		for( int j = 0 ; j < column ; j ++ ) {
			char element;
			cin>> element;


			if( element == 'S' ) start = {i,j};
			else if( element == 'E' ) finish = {i,j};

			arr[i][j] = element ;



		}
	}

	dist.assign(row,vector<int>(column,100));
	parent.assign(row,vector<state>(column, {-1,-1}));
	ways.assign(row,vector<int>(column,0));
	broken_walls.assign(row, vector<int>(column, 100));
    dist2.assign(row, vector<int>(column, 100));

}

void print(int row, int column) {
	for( int i = 0 ; i < row ; i++ ) {
		for( int j = 0 ; j < column ; j++ ) {
			cout<< arr[i][j] << "  ";
		}
		cout<< endl;
	}
}

bool isValid(int row, int col) {
	return (row>=0 and col>=0 and row < arr.size() and col < arr[0].size() and arr[row][col] != '#');
}

bool isValid2(int row, int col) {
	return (row>=0 and col>=0 and row < arr.size() and col < arr[0].size() );
}

void BFS1(state start) {

	// in case of unweighted graph you just need to maintain a visited array,distance array and a queue containing
	// state of node and other constraits , if we have already visited the node before we don't go there again


	int n = arr.size();
	int m = arr[0].size();
	vector<int> dr = {0,0,-1,1};
	vector<int> dc = {-1,1,0,0};
	// in the queue we need to push  __state_of_node__ + constraints
	// we always need a visited array to make sure that we don't come back to same state of node again and again
	// what should be inside visited ?
	//  visited always contains the state of the node
	// the minimum value of the variable will be stored in seprate array ( dist in this case )
	queue<state> que;
	vector<vector<bool>> visited(n,vector<bool>(m,false)); // for each node

	dist[start.first][start.second] = 0;
	visited[start.first][start.second] = true;
	que.push(start);
	parent[start.first][start.second] = {-1,-1};
	ways[start.first][start.second] = 1;

	while( !que.empty() ) {

		// pop the element
		state curr_node = que.front();
		que.pop();

		// traverse through all its neigh
		for( int i = 0 ; i < 4 ; i ++ ) {
			int nr = curr_node.first + dr[i];
			int nc = curr_node.second + dc[i];

			if( isValid(nr,nc) ) {
				if( !visited[nr][nc] ) {
					dist[nr][nc] = dist[curr_node.first][curr_node.second] + 1;
					visited[nr][nc] = true;
					parent[nr][nc] = curr_node;
					que.push({nr,nc});
					ways[nr][nc] = ways[curr_node.first][curr_node.second];
				}
				else {
					// if we have already visited that node
					if( dist[nr][nc] == dist[curr_node.first][curr_node.second] + 1 ) {
						ways[nr][nc] = ways[nr][nc] + ways[curr_node.first][curr_node.second];
					}
				}
			}
		}


	}

}



void BFS2(state start ) {


	vector<int> dr = {0,0,-1,1};
	vector<int> dc = {-1,1,0,0};
	broken_walls[start.first][start.second] = 0;
	deque<pair<int,state>> que;  // there are two states for single node there need to pass the state/level with node
	que.push_back({0,start}); // can reach to start node with zero walls broken
	// two levels => x and x + 1

	while(!que.empty()) {

		auto curr = que.front();
		que.pop_front();

		state curr_node = curr.second;
		int broken_till_curr_node = curr.first;

		// traverse in all its neighbours

		for( int i = 0; i < 4; i++ ) {
			int nr = curr_node.first + dr[i];
			int nc = curr_node.second + dc[i];

			if(!isValid2(nr,nc)) continue;
			int weight ;
			if( arr[nr][nc] == '#' ) weight = 1;
			else weight = 0;


			// for next node we need to check whether we have visited it or not
			// we always visited the best part of the node therefore if we have visited the node then there
			// is no need to go back to that node again
			if( broken_walls[nr][nc] > broken_till_curr_node + weight) {
				broken_walls[nr][nc] = broken_till_curr_node + weight;
				if( weight == 0 ) {
					// no cost will be there
					// we are still at the same level
					que.push_front({broken_till_curr_node,{nr,nc}});
				}
				if( weight == 1) {
					// 1 cost will be there
					que.push_back({broken_till_curr_node+1,{nr,nc}});
				}
			}
		}

	}

}


void BFS3(state start, int k ) {

	vector<int> dr = {0,0,-1,1};
	vector<int> dc = {-1,1,0,0};

	queue<pair<int,state>> que;
	// whatever we push into the que we mark that state visited i.e. visited array should contain que element
	set<pair<int,state>> visited;
	visited.insert({k,start}); // we can come at start node with 0 wall breaked
	// 0 wall available krke shortest path , 1 wall available krke shortest path ... n wall available krke shortest path from each node
	dist2[start.first][start.second] = 0;
	que.push({k,start});


	while( !que.empty() ) {
		auto curr = que.front();
		que.pop();
		int can_break = curr.first;
		state curr_node = curr.second;

		// go to all its neighbours
      for( int i = 0; i < 4; i++ ){
          int nr = curr_node.first + dr[i];
          int nc = curr_node.second + dc[i];
          
          if(!isValid2(nr,nc)) continue;
          
          int dk;
          if( arr[nr][nc] == '#') dk = 1;
          else dk = 0;
          int neigh_k = can_break - dk;
          
          // state of neigh node -->  neigh_k,nr,nc
          
          if( (neigh_k >= 0 ) and !visited.count({neigh_k,{nr,nc}})){
              // if we haven't visited this state of neigh node before then push that in queue
              visited.insert({neigh_k,{nr,nc}});
              dist2[nr][nc] = min(dist2[nr][nc] , dist2[curr_node.first][curr_node.second] + 1);
              que.push({neigh_k,{nr,nc}});
          }

      }


	}



}


int main() {

	int row, column;
	cin>> row >> column;
	cin>> k;
	arr.resize(row,vector<char>(column));

	input(row,column);
	print(row,column);


	// there can be many variations of this ques:
	/*
	    1. Find if we can reach from S to E                         
	    2. Find the shortest path length if you can reach           
	    3. Print the shortest path                                  
	    4. Find the number of shortest path                         
	    5. Find the minimum number number of walls that needs to be broken to reach E     
	    6. If you are allowed to break K walls then find the shortest path to reach E

	*/


	//  Find if we can reach to E or not and find the shortest lenght if you can
	BFS1(start); // start is the state of node, we don't need to consider any constraint when we are at a node


	if(dist[finish.first][finish.second] != 100) {
		cout<< "\nWe can reach to finish point with minimum steps: " << dist[finish.first][finish.second] << endl;


		// if the path exist lets print the path now for this we need to maintain a parent array for all the nodes
		// and keep on updating that in BFS's while loop
		state finish_point = finish;
		vector<state> path;
		while( parent[finish_point.first][finish_point.second].first != -1 and  parent[finish_point.first][finish_point.second].second != -1 ) {
			path.push_back(finish_point);
			finish_point = parent[finish_point.first][finish_point.second];
		}
		path.push_back(start);

		reverse(path.begin(),path.end());
		for( int i = 0; i < path.size(); i++ ) {
			cout<< "Step "<< i+1 << " : " << path[i].first << "," << path[i].second<< endl;
		}


		cout<< "\nNumber of shortest path to reach finish point:  "<< ways[finish.first][finish.second] << endl;

	}
	else {
		cout<< "\nWe can't reach to finish point without breaking any wall" << endl;
		// find the minimum number of walls you need to break
		// whatever you are finding you need to store them in seprate array for each node
		broken_walls.assign(row,vector<int>(column,100)); // at first we can reach to each node by breaking infinite walls
		BFS2(start);

		cout<< "\nBroken walls array: \n";
		for( int i = 0 ; i < row; i++ ) {
			for( int j = 0 ; j < column ; j++ ) {
				cout<< broken_walls[i][j] << "  ";
			}
			cout<< endl;
		}
		cout<< "\nMinimum number of walls need to break to reach finish point: "<< broken_walls[finish.first][finish.second] << endl;
	}



	// next question is to find the minimum number of walls you need to break to reach the final destination
	// that means this is sure that there is no way to reach to the final desitnation

	// we can do it as we were doing for the minimum distance, but in case of distance it was sure that if
	// you pop something from the que , you are already at the best state of that node, but in this case if
	// you have first pushed a node with 1 wall broken to reach to that node , and from another path you can come
	// by broking 0 walls then also you need to push into the queue and relax the edges around it which would increase
	// the time complexity
	// there are two solutions for this problem
	// either use the priority queue just like in dijkstra or use the deque
	// when we are using priority queue we make sure we don't pop the element with 1 level first than 0 level elements
	// similarly in case of deque we will push the elements with level 0 from bottom so that they can be processed first

	// implementatoin for this is in else condition with function BFS2






	// last ques it we are allowed to break K walls to reach to the final destination
	// therefore for each node we need to maintain what are the number of walls we can break from current node
	// so that we can take decision whether we can move to wall or not

	BFS3(start,k);



	cout<< "\nDistance array : \n";
	for( int i = 0; i < row; i++ ) {
		for( int j = 0 ; j < column; j++ ) {
			if( dist[i][j] == 100 ) cout<< "X" << "  ";
			else cout<< dist[i][j] << "  ";
		}
		cout<< endl;
	}
	
	
		
	cout<< "\nDistance array if we can break " << k << " walls" << endl;
	for( int i = 0 ; i < row ; i++ ){
	    for( int j = 0 ; j < column; j++ ){
            if( dist2[i][j] == 100 ){
                cout<< "X" << "  ";
            }
            else cout<< dist2[i][j] << "  "; 
	    }
	    cout<< endl;
	}





	return 0;
}







#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int minJumps(vector<int>& arr) {
    int n = arr.size();
    if (n == 1) return 0;

    vector<vector<int>> mp(n);
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < mp.size(); j++) {
            if (!mp[j].empty() && arr[mp[j][0]] == arr[i]) {
                mp[j].push_back(i);
                found = true;
                break;
            }
        }
        if (!found) {
            vector<int> v;
            v.push_back(i);
            mp.push_back(v);
        }
    }

    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;

    int steps = 0;

    while (!q.empty()) {
        int size = q.size(); // all nodes at current level
        for (int s = 0; s < size; s++) {
            int idx = q.front(); q.pop();

            if (idx == n - 1) return steps;

            // Adjacent moves
            if (idx + 1 < n && !visited[idx + 1]) {
                visited[idx + 1] = true;
                q.push(idx + 1);
            }
            if (idx - 1 >= 0 && !visited[idx - 1]) {
                visited[idx - 1] = true;
                q.push(idx - 1);
            }

            // Teleport moves
            for (int i = 0; i < mp.size(); i++) {
                if (!mp[i].empty() && arr[mp[i][0]] == arr[idx]) {
                    for (int j = 0; j < mp[i].size(); j++) {
                        int sameIdx = mp[i][j];
                        if (!visited[sameIdx]) {
                            visited[sameIdx] = true;
                            q.push(sameIdx);
                        }
                    }
                    mp[i].clear(); // avoid revisiting
                    break;
                }
            }
        }
        steps++; // increment step after processing current level
    }

    return -1;
}

int main() {
    vector<int> arr = {100, -23, -23, 404, 100};
    cout << "Minimum jumps: " << minJumps(arr) << endl;
    return 0;
}




#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int minJumps(vector<int>& arr) {
    int n = arr.size();
    if (n == 1) return 0;

    // Create map of value -> indices
    vector<vector<int>> mp(n); // We'll dynamically add indices for simplicity
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < mp.size(); j++) {
            if (!mp[j].empty() && arr[mp[j][0]] == arr[i]) {
                mp[j].push_back(i);
                found = true;
                break;
            }
        }
        if (!found) {
            vector<int> v;
            v.push_back(i);
            mp.push_back(v);
        }
    }

    vector<int> dist(n, INT_MAX);
    queue<int> q;
    dist[0] = 0;
    q.push(0);

    while (!q.empty()) {
        int idx = q.front(); q.pop();

        if (idx == n - 1) return dist[idx];

        // Move to adjacent indices
        if (idx + 1 < n && dist[idx + 1] > dist[idx] + 1) {
            dist[idx + 1] = dist[idx] + 1;
            q.push(idx + 1);
        }
        if (idx - 1 >= 0 && dist[idx - 1] > dist[idx] + 1) {
            dist[idx - 1] = dist[idx] + 1;
            q.push(idx - 1);
        }

        // Move to same-value indices
        for (int i = 0; i < mp.size(); i++) {
            if (!mp[i].empty() && arr[mp[i][0]] == arr[idx]) {
                for (int j = 0; j < mp[i].size(); j++) {
                    int sameIdx = mp[i][j];
                    if (dist[sameIdx] > dist[idx] + 1) {
                        dist[sameIdx] = dist[idx] + 1;
                        q.push(sameIdx);
                    }
                }
                // Clear indices to avoid revisiting
                mp[i].clear();
                break;
            }
        }
    }

    return -1;
}

int main() {
    vector<int> arr = {100, -23, -23, 404, 100, 23, 23, 23, 3, 404};
    cout << "Minimum jumps: " << minJumps(arr) << endl;
    return 0;
}


class Solution {
public:
    vector<int> countOfPairs(int n, int x, int y) {
        x--; y--; // convert to 0-indexed

        // build adjacency list
        vector<vector<int>> adj(n);
        for (int i = 0; i < n - 1; i++) {
            adj[i].push_back(i + 1);
            adj[i + 1].push_back(i);
        }
        if (x != y) {           // avoid duplicate self-loop
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        vector<int> ans(n, 0); // ans[d] = number of pairs at distance d

        // BFS from each node
        for (int src = 0; src < n; src++) {
            vector<int> dist(n, -1);
            queue<int> q;
            q.push(src);
            dist[src] = 0;

            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.push(v);
                    }
                }
            }

            // count pairs only once (src < j)
            for (int j = src + 1; j < n; j++) {
                ans[dist[j]]+=2;
            }
        }

        ans.erase(ans.begin()); // remove distance 0 count
        return ans;
    }
};


class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();
        const int DRAW = 0, MOUSE = 1, CAT = 2;
        
        // color[m][c][t]: 0=draw, 1=mouse wins, 2=cat wins
        vector<vector<vector<int>>> color(n, vector<vector<int>>(n, vector<int>(2, DRAW)));
        
        // degree[m][c][t]: number of next moves for this state
        vector<vector<vector<int>>> degree(n, vector<vector<int>>(n, vector<int>(2, 0)));
        
        for (int m = 0; m < n; ++m) {
            for (int c = 0; c < n; ++c) {
                degree[m][c][0] = graph[m].size();       // mouse turn
                degree[m][c][1] = graph[c].size();       // cat turn
                for (int v : graph[c]) if (v == 0) degree[m][c][1]--; // cat cannot go to hole
            }
        }
        
        queue<tuple<int,int,int,int>> q; // (m, c, turn, result)
        
        // Base cases
        for (int i = 1; i < n; ++i) {
            color[0][i][0] = color[0][i][1] = MOUSE;
            q.push({0,i,0,MOUSE});
            q.push({0,i,1,MOUSE});
            
            color[i][i][0] = color[i][i][1] = CAT;
            q.push({i,i,0,CAT});
            q.push({i,i,1,CAT});
        }
        
        while (!q.empty()) {
            auto [m, c, t, res] = q.front(); q.pop();
            
            // Iterate over parent states
            for (auto [pm, pc, pt] : parents(graph, m, c, t)) {
                if (color[pm][pc][pt] != DRAW) continue;
                
                if ((pt == 0 && res == MOUSE) || (pt == 1 && res == CAT)) {
                    color[pm][pc][pt] = res;
                    q.push({pm,pc,pt,res});
                } else {
                    degree[pm][pc][pt]--;
                    if (degree[pm][pc][pt] == 0) {
                        color[pm][pc][pt] = (pt == 0) ? CAT : MOUSE;
                        q.push({pm,pc,pt,color[pm][pc][pt]});
                    }
                }
            }
        }
        
        return color[1][2][0]; // initial state: mouse at 1, cat at 2, mouse turn
    }
    
private:
    vector<tuple<int,int,int>> parents(vector<vector<int>>& graph, int m, int c, int t) {
        vector<tuple<int,int,int>> res;
        if (t == 1) { // current cat turn, last move was mouse
            for (int pm : graph[m]) res.push_back({pm, c, 0});
        } else {      // current mouse turn, last move was cat
            for (int pc : graph[c]) if (pc != 0) res.push_back({m, pc, 1});
        }
        return res;
    }
};




class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();
        
        // 0 = unknown, 1 = mouse wins, 2 = cat wins
        vector<vector<vector<int>>> color(n, vector<vector<int>>(n, vector<int>(2, 0)));
        vector<vector<vector<int>>> degree(n, vector<vector<int>>(n, vector<int>(2, 0)));
        
        // Initialize degree (number of next moves for each state)
        for(int m = 0; m < n; m++){
            for(int c = 0; c < n; c++){
                degree[m][c][0] = graph[m].size();       // Mouse's turn
                degree[m][c][1] = graph[c].size();       // Cat's turn
            }
        }

        queue<tuple<int,int,int>> q; // state = (mouse, cat, turn)
        
        // Terminal states
        for(int i = 0; i < n; i++){
            // Mouse at hole (0) → mouse wins
            if(i != 0){
                color[0][i][0] = 1; // mouse turn
                color[0][i][1] = 1; // cat turn
                q.push({0, i, 0});
                q.push({0, i, 1});
            }
            // Cat catches mouse → cat wins
            color[i][i][0] = 2;
            color[i][i][1] = 2;
            q.push({i, i, 0});
            q.push({i, i, 1});
        }

        // BFS propagation
        while(!q.empty()){
            auto [m, c, t] = q.front(); q.pop();
            int curColor = color[m][c][t];
            
            // Get all parent states that can move to (m,c,t)
            vector<tuple<int,int,int>> parents;
            if(t == 0){ // mouse just moved → parent is cat's turn
                for(int pc : graph[c]){
                    if(pc == 0) continue; // cat cannot go to hole
                    parents.push_back({m, pc, 1});
                }
            } else { // t==1, cat just moved → parent is mouse's turn
                for(int pm : graph[m]){
                    parents.push_back({pm, c, 0});
                }
            }

            for(auto &[pm, pc, pt] : parents){
                if(color[pm][pc][pt] != 0) continue; // already determined

                // If current state is a win for current player → parent can force win
                if(curColor == (pt == 0 ? 1 : 2)){
                    color[pm][pc][pt] = curColor;
                    q.push({pm, pc, pt});
                } else { 
                    // decrease degree, if all children are losing → parent loses
                    degree[pm][pc][pt]--;
                    if(degree[pm][pc][pt] == 0){
                        color[pm][pc][pt] = (pt == 0 ? 2 : 1); // losing state for current turn
                        q.push({pm, pc, pt});
                    }
                }
            }
        }

        // Game starts at mouse=1, cat=2, mouse's turn
        return color[1][2][0];
    }
};


---
comments: true
difficulty: Hard
edit_url: https://github.com/doocs/leetcode/edit/main/solution/0900-0999/0913.Cat%20and%20Mouse/README_EN.md
tags:
    - Graph
    - Topological Sort
    - Memoization
    - Math
    - Dynamic Programming
    - Game Theory
---

<!-- problem:start -->

# [913. Cat and Mouse](https://leetcode.com/problems/cat-and-mouse)

[中文文档](/solution/0900-0999/0913.Cat%20and%20Mouse/README.md)

## Description

<!-- description:start -->

<p>A game on an <strong>undirected</strong> graph is played by two players, Mouse and Cat, who alternate turns.</p>

<p>The graph is given as follows: <code>graph[a]</code> is a list of all nodes <code>b</code> such that <code>ab</code> is an edge of the graph.</p>

<p>The mouse starts at node <code>1</code> and goes first, the cat starts at node <code>2</code> and goes second, and there is a hole at node <code>0</code>.</p>

<p>During each player&#39;s turn, they <strong>must</strong> travel along one&nbsp;edge of the graph that meets where they are.&nbsp; For example, if the Mouse is at node 1, it <strong>must</strong> travel to any node in <code>graph[1]</code>.</p>

<p>Additionally, it is not allowed for the Cat to travel to the Hole (node <code>0</code>).</p>

<p>Then, the game can end in three&nbsp;ways:</p>

<ul>
	<li>If ever the Cat occupies the same node as the Mouse, the Cat wins.</li>
	<li>If ever the Mouse reaches the Hole, the Mouse wins.</li>
	<li>If ever a position is repeated (i.e., the players are in the same position as a previous turn, and&nbsp;it is the same player&#39;s turn to move), the game is a draw.</li>
</ul>

<p>Given a <code>graph</code>, and assuming both players play optimally, return</p>

<ul>
	<li><code>1</code>&nbsp;if the mouse wins the game,</li>
	<li><code>2</code>&nbsp;if the cat wins the game, or</li>
	<li><code>0</code>&nbsp;if the game is a draw.</li>
</ul>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>
<img alt="" src="https://fastly.jsdelivr.net/gh/doocs/leetcode@main/solution/0900-0999/0913.Cat%20and%20Mouse/images/cat1.jpg" style="width: 300px; height: 300px;" />
<pre>
<strong>Input:</strong> graph = [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
<strong>Output:</strong> 0
</pre>

<p><strong class="example">Example 2:</strong></p>
<img alt="" src="https://fastly.jsdelivr.net/gh/doocs/leetcode@main/solution/0900-0999/0913.Cat%20and%20Mouse/images/cat2.jpg" style="width: 200px; height: 200px;" />
<pre>
<strong>Input:</strong> graph = [[1,3],[0],[3],[0,2]]
<strong>Output:</strong> 1
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>3 &lt;= graph.length &lt;= 50</code></li>
	<li><code>1&nbsp;&lt;= graph[i].length &lt; graph.length</code></li>
	<li><code>0 &lt;= graph[i][j] &lt; graph.length</code></li>
	<li><code>graph[i][j] != i</code></li>
	<li><code>graph[i]</code> is unique.</li>
	<li>The mouse and the cat can always move.&nbsp;</li>
</ul>

<!-- description:end -->

## Solutions

<!-- solution:start -->

### Solution 1: Topological Sorting

According to the problem description, the state of the game is determined by the position of the mouse, the position of the cat, and the player who is moving. The outcome can be directly determined in the following situations:

-   When the positions of the cat and the mouse are the same, the cat wins. This is a winning state for the cat and a losing state for the mouse.
-   When the mouse is at the hole, the mouse wins. This is a winning state for the mouse and a losing state for the cat.

To determine the result of the initial state, we need to traverse all states starting from the boundary states. Each state includes the position of the mouse, the position of the cat, and the player who is moving. Based on the current state, we can determine all possible states from the previous round. The player who moved in the previous round is the opposite of the player who is moving in the current state, and the positions of the players in the previous round are different from their positions in the current state.

We use the tuple $(m, c, t)$ to represent the current state and $(pm, pc, pt)$ to represent a possible state from the previous round. The possible states from the previous round are:

-   If the player moving in the current round is the mouse, then the player moving in the previous round is the cat. The position of the mouse in the previous round is the same as the current position of the mouse, and the position of the cat in the previous round is any adjacent node of the current position of the cat.
-   If the player moving in the current round is the cat, then the player moving in the previous round is the mouse. The position of the cat in the previous round is the same as the current position of the cat, and the position of the mouse in the previous round is any adjacent node of the current position of the mouse.

Initially, all states except the boundary states are unknown. Starting from the boundary states, for each state, we determine all possible states from the previous round and update the results. The update logic is as follows:

1. If the player moving in the previous round is the same as the winner in the current round, then the player moving in the previous round can reach the current state and win. We directly update the state of the previous round to the winner of the current round.
2. If the player moving in the previous round is different from the winner in the current round, and all states that the player moving in the previous round can reach are losing states for that player, then we update the state of the previous round to the winner of the current round.

For the second update logic, we need to record the degree of each state. Initially, the degree of each state represents the number of nodes the player moving in that state can move to, which is the number of adjacent nodes of the node where the player is located. If the player is the cat and the node is adjacent to the hole, the degree of that state is reduced by $1$.

When all states have been updated, the result of the initial state is the final result.

The time complexity is $O(n^3)$, and the space complexity is $O(n^2)$. Here, $n$ is the number of nodes in the graph.

<!-- tabs:start -->

#### Python3

```python
HOLE, MOUSE_START, CAT_START = 0, 1, 2
MOUSE_TURN, CAT_TURN = 0, 1
MOUSE_WIN, CAT_WIN, TIE = 1, 2, 0


class Solution:
    def catMouseGame(self, graph: List[List[int]]) -> int:
        def get_prev_states(state):
            m, c, t = state
            pt = t ^ 1
            pre = []
            if pt == CAT_TURN:
                for pc in graph[c]:
                    if pc != HOLE:
                        pre.append((m, pc, pt))
            else:
                for pm in graph[m]:
                    pre.append((pm, c, pt))
            return pre

        n = len(graph)
        ans = [[[0, 0] for _ in range(n)] for _ in range(n)]
        degree = [[[0, 0] for _ in range(n)] for _ in range(n)]
        for i in range(n):
            for j in range(1, n):
                degree[i][j][MOUSE_TURN] = len(graph[i])
                degree[i][j][CAT_TURN] = len(graph[j])
            for j in graph[HOLE]:
                degree[i][j][CAT_TURN] -= 1
        q = deque()
        for j in range(1, n):
            ans[0][j][MOUSE_TURN] = ans[0][j][CAT_TURN] = MOUSE_WIN
            q.append((0, j, MOUSE_TURN))
            q.append((0, j, CAT_TURN))
        for i in range(1, n):
            ans[i][i][MOUSE_TURN] = ans[i][i][CAT_TURN] = CAT_WIN
            q.append((i, i, MOUSE_TURN))
            q.append((i, i, CAT_TURN))
        while q:
            state = q.popleft()
            t = ans[state[0]][state[1]][state[2]]
            for prev_state in get_prev_states(state):
                pm, pc, pt = prev_state
                if ans[pm][pc][pt] == TIE:
                    win = (t == MOUSE_WIN and pt == MOUSE_TURN) or (
                        t == CAT_WIN and pt == CAT_TURN
                    )
                    if win:
                        ans[pm][pc][pt] = t
                        q.append(prev_state)
                    else:
                        degree[pm][pc][pt] -= 1
                        if degree[pm][pc][pt] == 0:
                            ans[pm][pc][pt] = t
                            q.append(prev_state)
        return ans[MOUSE_START][CAT_START][MOUSE_TURN]
```

#### Java

```java
class Solution {
    private int n;
    private int[][] g;
    private int[][][] ans;
    private int[][][] degree;

    private static final int HOLE = 0, MOUSE_START = 1, CAT_START = 2;
    private static final int MOUSE_TURN = 0, CAT_TURN = 1;
    private static final int MOUSE_WIN = 1, CAT_WIN = 2, TIE = 0;

    public int catMouseGame(int[][] graph) {
        n = graph.length;
        g = graph;
        ans = new int[n][n][2];
        degree = new int[n][n][2];
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                degree[i][j][MOUSE_TURN] = g[i].length;
                degree[i][j][CAT_TURN] = g[j].length;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j : g[HOLE]) {
                --degree[i][j][CAT_TURN];
            }
        }
        Deque<int[]> q = new ArrayDeque<>();
        for (int j = 1; j < n; ++j) {
            ans[0][j][MOUSE_TURN] = MOUSE_WIN;
            ans[0][j][CAT_TURN] = MOUSE_WIN;
            q.offer(new int[] {0, j, MOUSE_TURN});
            q.offer(new int[] {0, j, CAT_TURN});
        }
        for (int i = 1; i < n; ++i) {
            ans[i][i][MOUSE_TURN] = CAT_WIN;
            ans[i][i][CAT_TURN] = CAT_WIN;
            q.offer(new int[] {i, i, MOUSE_TURN});
            q.offer(new int[] {i, i, CAT_TURN});
        }
        while (!q.isEmpty()) {
            int[] state = q.poll();
            int t = ans[state[0]][state[1]][state[2]];
            List<int[]> prevStates = getPrevStates(state);
            for (var prevState : prevStates) {
                int pm = prevState[0], pc = prevState[1], pt = prevState[2];
                if (ans[pm][pc][pt] == TIE) {
                    boolean win
                        = (t == MOUSE_WIN && pt == MOUSE_TURN) || (t == CAT_WIN && pt == CAT_TURN);
                    if (win) {
                        ans[pm][pc][pt] = t;
                        q.offer(prevState);
                    } else {
                        if (--degree[pm][pc][pt] == 0) {
                            ans[pm][pc][pt] = t;
                            q.offer(prevState);
                        }
                    }
                }
            }
        }
        return ans[MOUSE_START][CAT_START][MOUSE_TURN];
    }

    private List<int[]> getPrevStates(int[] state) {
        List<int[]> pre = new ArrayList<>();
        int m = state[0], c = state[1], t = state[2];
        int pt = t ^ 1;
        if (pt == CAT_TURN) {
            for (int pc : g[c]) {
                if (pc != HOLE) {
                    pre.add(new int[] {m, pc, pt});
                }
            }
        } else {
            for (int pm : g[m]) {
                pre.add(new int[] {pm, c, pt});
            }
        }
        return pre;
    }
}
```

#### C++

```cpp
const int HOLE = 0;
const int MOUSE_START = 1;
const int CAT_START = 2;
const int MOUSE_TURN = 0;
const int CAT_TURN = 1;
const int MOUSE_WIN = 1;
const int CAT_WIN = 2;
const int TIE = 0;

class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();
        int ans[n][n][2];
        int degree[n][n][2];
        memset(ans, 0, sizeof ans);
        memset(degree, 0, sizeof degree);
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                degree[i][j][MOUSE_TURN] = graph[i].size();
                degree[i][j][CAT_TURN] = graph[j].size();
            }
            for (int j : graph[HOLE]) {
                --degree[i][j][CAT_TURN];
            }
        }
        auto getPrevStates = [&](int m, int c, int t) {
            int pt = t ^ 1;
            vector<tuple<int, int, int>> pre;
            if (pt == CAT_TURN) {
                for (int pc : graph[c]) {
                    if (pc != HOLE) {
                        pre.emplace_back(m, pc, pt);
                    }
                }
            } else {
                for (int pm : graph[m]) {
                    pre.emplace_back(pm, c, pt);
                }
            }
            return pre;
        };
        queue<tuple<int, int, int>> q;
        for (int j = 1; j < n; ++j) {
            ans[0][j][MOUSE_TURN] = ans[0][j][CAT_TURN] = MOUSE_WIN;
            q.emplace(0, j, MOUSE_TURN);
            q.emplace(0, j, CAT_TURN);
        }
        for (int i = 1; i < n; ++i) {
            ans[i][i][MOUSE_TURN] = ans[i][i][CAT_TURN] = CAT_WIN;
            q.emplace(i, i, MOUSE_TURN);
            q.emplace(i, i, CAT_TURN);
        }
        while (!q.empty()) {
            auto [m, c, t] = q.front();
            q.pop();
            int x = ans[m][c][t];
            for (auto [pm, pc, pt] : getPrevStates(m, c, t)) {
                if (ans[pm][pc][pt] == TIE) {
                    bool win = (x == MOUSE_WIN && pt == MOUSE_TURN) || (x == CAT_WIN && pt == CAT_TURN);
                    if (win) {
                        ans[pm][pc][pt] = x;
                        q.emplace(pm, pc, pt);
                    } else {
                        if (--degree[pm][pc][pt] == 0) {
                            ans[pm][pc][pt] = x;
                            q.emplace(pm, pc, pt);
                        }
                    }
                }
            }
        }
        return ans[MOUSE_START][CAT_START][MOUSE_TURN];
    }
};
```

#### Go

```go
const (
	hole       = 0
	mouseStart = 1
	catStart   = 2
	mouseTurn  = 0
	catTurn    = 1
	mouseWin   = 1
	catWin     = 2
	tie        = 0
)

func catMouseGame(graph [][]int) int {
	ans := [50][50][2]int{}
	degree := [50][50][2]int{}
	n := len(graph)
	for i := 0; i < n; i++ {
		for j := 1; j < n; j++ {
			degree[i][j][mouseTurn] = len(graph[i])
			degree[i][j][catTurn] = len(graph[j])
		}
		for _, j := range graph[hole] {
			degree[i][j][catTurn]--
		}
	}
	type tuple struct{ m, c, t int }
	q := []tuple{}
	for j := 1; j < n; j++ {
		ans[0][j][mouseTurn], ans[0][j][catTurn] = mouseWin, mouseWin
		q = append(q, tuple{0, j, mouseTurn})
		q = append(q, tuple{0, j, catTurn})
	}
	for i := 1; i < n; i++ {
		ans[i][i][mouseTurn], ans[i][i][catTurn] = catWin, catWin
		q = append(q, tuple{i, i, mouseTurn})
		q = append(q, tuple{i, i, catTurn})
	}
	getPrevStates := func(m, c, t int) []tuple {
		pre := []tuple{}
		pt := t ^ 1
		if pt == catTurn {
			for _, pc := range graph[c] {
				if pc != hole {
					pre = append(pre, tuple{m, pc, pt})
				}
			}
		} else {
			for _, pm := range graph[m] {
				pre = append(pre, tuple{pm, c, pt})
			}
		}
		return pre
	}
	for len(q) > 0 {
		state := q[0]
		m, c, t := state.m, state.c, state.t
		q = q[1:]
		x := ans[m][c][t]
		for _, prevState := range getPrevStates(m, c, t) {
			pm, pc, pt := prevState.m, prevState.c, prevState.t
			if ans[pm][pc][pt] == tie {
				win := (x == mouseWin && pt == mouseTurn) || (x == catWin && pt == catTurn)
				if win {
					ans[pm][pc][pt] = x
					q = append(q, tuple{pm, pc, pt})
				} else {
					degree[pm][pc][pt]--
					if degree[pm][pc][pt] == 0 {
						ans[pm][pc][pt] = x
						q = append(q, tuple{pm, pc, pt})
					}
				}
			}
		}
	}
	return ans[mouseStart][catStart][mouseTurn]
}
```

#### TypeScript

```ts
function catMouseGame(graph: number[][]): number {
    const [HOLE, MOUSE_START, CAT_START] = [0, 1, 2];
    const [MOUSE_TURN, CAT_TURN] = [0, 1];
    const [MOUSE_WIN, CAT_WIN, TIE] = [1, 2, 0];

    function get_prev_states(state: [number, number, number]): [number, number, number][] {
        const [m, c, t] = state;
        const pt = t ^ 1;
        const pre = [] as [number, number, number][];

        if (pt === CAT_TURN) {
            for (const pc of graph[c]) {
                if (pc !== HOLE) {
                    pre.push([m, pc, pt]);
                }
            }
        } else {
            for (const pm of graph[m]) {
                pre.push([pm, c, pt]);
            }
        }
        return pre;
    }

    const n = graph.length;
    const ans: number[][][] = Array.from({ length: n }, () =>
        Array.from({ length: n }, () => [TIE, TIE]),
    );
    const degree: number[][][] = Array.from({ length: n }, () =>
        Array.from({ length: n }, () => [0, 0]),
    );

    for (let i = 0; i < n; i++) {
        for (let j = 1; j < n; j++) {
            degree[i][j][MOUSE_TURN] = graph[i].length;
            degree[i][j][CAT_TURN] = graph[j].length;
        }
        for (const j of graph[HOLE]) {
            degree[i][j][CAT_TURN] -= 1;
        }
    }

    const q: [number, number, number][] = [];

    for (let j = 1; j < n; j++) {
        ans[0][j][MOUSE_TURN] = ans[0][j][CAT_TURN] = MOUSE_WIN;
        q.push([0, j, MOUSE_TURN], [0, j, CAT_TURN]);
    }
    for (let i = 1; i < n; i++) {
        ans[i][i][MOUSE_TURN] = ans[i][i][CAT_TURN] = CAT_WIN;
        q.push([i, i, MOUSE_TURN], [i, i, CAT_TURN]);
    }

    while (q.length > 0) {
        const state = q.shift()!;
        const [m, c, t] = state;
        const result = ans[m][c][t];

        for (const prev_state of get_prev_states(state)) {
            const [pm, pc, pt] = prev_state;
            if (ans[pm][pc][pt] === TIE) {
                const win =
                    (result === MOUSE_WIN && pt === MOUSE_TURN) ||
                    (result === CAT_WIN && pt === CAT_TURN);
                if (win) {
                    ans[pm][pc][pt] = result;
                    q.push(prev_state);
                } else {
                    degree[pm][pc][pt] -= 1;
                    if (degree[pm][pc][pt] === 0) {
                        ans[pm][pc][pt] = result;
                        q.push(prev_state);
                    }
                }
            }
        }
    }

    return ans[MOUSE_START][CAT_START][MOUSE_TURN];
}
```

#### C#

```cs
public class Solution {
    private int n;
    private int[][] g;
    private int[,,] ans;
    private int[,,] degree;

    private const int HOLE = 0, MOUSE_START = 1, CAT_START = 2;
    private const int MOUSE_TURN = 0, CAT_TURN = 1;
    private const int MOUSE_WIN = 1, CAT_WIN = 2, TIE = 0;

    public int CatMouseGame(int[][] graph) {
        n = graph.Length;
        g = graph;
        ans = new int[n, n, 2];
        degree = new int[n, n, 2];

        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                degree[i, j, MOUSE_TURN] = g[i].Length;
                degree[i, j, CAT_TURN] = g[j].Length;
            }
        }

        for (int i = 0; i < n; i++) {
            foreach (int j in g[HOLE]) {
                degree[i, j, CAT_TURN]--;
            }
        }

        Queue<int[]> q = new Queue<int[]>();

        for (int j = 1; j < n; j++) {
            ans[0, j, MOUSE_TURN] = MOUSE_WIN;
            ans[0, j, CAT_TURN] = MOUSE_WIN;
            q.Enqueue(new int[] { 0, j, MOUSE_TURN });
            q.Enqueue(new int[] { 0, j, CAT_TURN });
        }

        for (int i = 1; i < n; i++) {
            ans[i, i, MOUSE_TURN] = CAT_WIN;
            ans[i, i, CAT_TURN] = CAT_WIN;
            q.Enqueue(new int[] { i, i, MOUSE_TURN });
            q.Enqueue(new int[] { i, i, CAT_TURN });
        }

        while (q.Count > 0) {
            int[] state = q.Dequeue();
            int t = ans[state[0], state[1], state[2]];
            List<int[]> prevStates = GetPrevStates(state);

            foreach (var prevState in prevStates) {
                int pm = prevState[0], pc = prevState[1], pt = prevState[2];
                if (ans[pm, pc, pt] == TIE) {
                    bool win = (t == MOUSE_WIN && pt == MOUSE_TURN) || (t == CAT_WIN && pt == CAT_TURN);
                    if (win) {
                        ans[pm, pc, pt] = t;
                        q.Enqueue(prevState);
                    } else {
                        if (--degree[pm, pc, pt] == 0) {
                            ans[pm, pc, pt] = t;
                            q.Enqueue(prevState);
                        }
                    }
                }
            }
        }

        return ans[MOUSE_START, CAT_START, MOUSE_TURN];
    }

    private List<int[]> GetPrevStates(int[] state) {
        List<int[]> pre = new List<int[]>();
        int m = state[0], c = state[1], t = state[2];
        int pt = t ^ 1;

        if (pt == CAT_TURN) {
            foreach (int pc in g[c]) {
                if (pc != HOLE) {
                    pre.Add(new int[] { m, pc, pt });
                }
            }
        } else {
            foreach (int pm in g[m]) {
                pre.Add(new int[] { pm, c, pt });
            }
        }

        return pre;
    }
}
```

<!-- tabs:end -->

<!-- solution:end -->

<!-- problem:end -->



const int HOLE = 0;
const int MOUSE_START = 1;
const int CAT_START = 2;
const int MOUSE_TURN = 0;
const int CAT_TURN = 1;
const int MOUSE_WIN = 1;
const int CAT_WIN = 2;
const int TIE = 0;

class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();
        int ans[n][n][2];
        int degree[n][n][2];
        memset(ans, 0, sizeof ans);
        memset(degree, 0, sizeof degree);
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                degree[i][j][MOUSE_TURN] = graph[i].size();
                degree[i][j][CAT_TURN] = graph[j].size();
            }
            for (int j : graph[HOLE]) {
                --degree[i][j][CAT_TURN];
            }
        }
        auto getPrevStates = [&](int m, int c, int t) {
            int pt = t ^ 1;
            vector<tuple<int, int, int>> pre;
            if (pt == CAT_TURN) {
                for (int pc : graph[c]) {
                    if (pc != HOLE) {
                        pre.emplace_back(m, pc, pt);
                    }
                }
            } else {
                for (int pm : graph[m]) {
                    pre.emplace_back(pm, c, pt);
                }
            }
            return pre;
        };
        queue<tuple<int, int, int>> q;
        for (int j = 1; j < n; ++j) {
            ans[0][j][MOUSE_TURN] = ans[0][j][CAT_TURN] = MOUSE_WIN;
            q.emplace(0, j, MOUSE_TURN);
            q.emplace(0, j, CAT_TURN);
        }
        for (int i = 1; i < n; ++i) {
            ans[i][i][MOUSE_TURN] = ans[i][i][CAT_TURN] = CAT_WIN;
            q.emplace(i, i, MOUSE_TURN);
            q.emplace(i, i, CAT_TURN);
        }
        while (!q.empty()) {
            auto [m, c, t] = q.front();
            q.pop();
            int x = ans[m][c][t];
            for (auto [pm, pc, pt] : getPrevStates(m, c, t)) {
                if (ans[pm][pc][pt] == TIE) {
                    bool win = (x == MOUSE_WIN && pt == MOUSE_TURN) || (x == CAT_WIN && pt == CAT_TURN);
                    if (win) {
                        ans[pm][pc][pt] = x;
                        q.emplace(pm, pc, pt);
                    } else {
                        if (--degree[pm][pc][pt] == 0) {
                            ans[pm][pc][pt] = x;
                            q.emplace(pm, pc, pt);
                        }
                    }
                }
            }
        }
        return ans[MOUSE_START][CAT_START][MOUSE_TURN];
    }
};




int catMouseGame(vector<vector<int>>& graph) {
    int n = graph.size();
    
    const int DRAW = 0, MOUSE = 1, CAT = 2;

    // color[m][c][turn] -> 0=draw, 1=mouse wins, 2=cat wins
    vector<vector<vector<int>>> color(n, vector<vector<int>>(n, vector<int>(2, DRAW)));

    // degree[m][c][turn] = number of unexplored moves
    vector<vector<vector<int>>> degree(n, vector<vector<int>>(n, vector<int>(2, 0)));

    // Initialize degrees
    for (int m=0; m<n; m++){
        for (int c=0; c<n; c++){
            degree[m][c][0] = graph[m].size(); // mouse turn // graph[m].size() --> it is giving us the neighs the mouse can visit
            degree[m][c][1] = graph[c].size(); // cat turn
            // Loop through all neighbors of the cat
 
// Loop through all neighbors of the cat
for (int v = 0; v < graph[c].size(); v++) {
    // If the neighbor is the hole (node 0), cat cannot go there
    if (graph[c][v] == 0) {
        degree[m][c][1] = degree[m][c][1] - 1; // subtract 1 from cat's possible moves
    }
}  
 

        }
    }

    queue<tuple<int,int,int,int>> q;

    // Base cases
    for(int i=1;i<n;i++){
        color[0][i][0] = color[0][i][1] = MOUSE;//why we are setting both to mouse ans---> if the mouse is at the whole it has already won ,no matter whose turn it is.
        //samr for cat as well
        q.push({0,i,0,MOUSE});
        q.push({0,i,1,MOUSE});

        color[i][i][0] = color[i][i][1] = CAT;
        q.push({i,i,0,CAT});
        q.push({i,i,1,CAT});
    }

    // BFS
    while(!q.empty()){
        auto [m,c,turn,result] = q.front(); q.pop();

        for(auto [pm,pc,pt]: parents(graph, m,c,turn)){
            if(color[pm][pc][pt]!=DRAW) continue;

            // Can force a win
            if((pt==0 && result==MOUSE) || (pt==1 && result==CAT)){
                color[pm][pc][pt] = result;
                q.push({pm,pc,pt,result});
            }
            else{
                degree[pm][pc][pt]--;
                if(degree[pm][pc][pt]==0){ // all moves lost
                    color[pm][pc][pt] = (pt==0)?CAT:MOUSE;
                    q.push({pm,pc,pt,color[pm][pc][pt]});
                }
            }
        }
    }

    // Return result of initial state: mouse at 1, cat at 2, mouse turn
    return color[1][2][0];
}



int catMouseGame(vector<vector<int>>& graph) {
    int n = graph.size();
    
    const int DRAW = 0, MOUSE = 1, CAT = 2;

    // color[m][c][turn] -> 0=draw, 1=mouse wins, 2=cat wins
    vector<vector<vector<int>>> color(n, vector<vector<int>>(n, vector<int>(2, DRAW)));

    // degree[m][c][turn] = number of unexplored moves
    vector<vector<vector<int>>> degree(n, vector<vector<int>>(n, vector<int>(2, 0)));

    // Initialize degrees
    for (int m=0; m<n; m++){
        for (int c=0; c<n; c++){
            degree[m][c][0] = graph[m].size(); // mouse turn
            degree[m][c][1] = graph[c].size(); // cat turn
            for (int i = 0; i < graph[c].size(); i++){
                if (graph[c][i] == 0) degree[m][c][1]--; // cat cannot go to hole
            }
        }
    }

    queue<vector<int>> q;

    // Base cases
    
    // BFS
    while (!q.empty()){
        vector<int> state = q.front();
        q.pop();

        int m = state[0];
        int c = state[1];
        int turn = state[2];
        int result = state[3];

        vector<vector<int>> par = parents(graph, m, c, turn); // get parent states
        for (int i = 0; i < par.size(); i++){
            int pm = par[i][0];
            int pc = par[i][1];
            int pt = par[i][2];

            if (color[pm][pc][pt] != DRAW) continue;

            // Parent can force a win
            if ((pt == 0 && result == MOUSE) || (pt == 1 && result == CAT)){
                color[pm][pc][pt] = result;
                q.push({pm, pc, pt, result});
            }
            else {
                degree[pm][pc][pt]--;
                if (degree[pm][pc][pt] == 0){ // all moves lost
                    color[pm][pc][pt] = (pt == 0) ? CAT : MOUSE;
                    q.push({pm, pc, pt, color[pm][pc][pt]});
                }
            }
        }
    }

    // Return result of initial state: mouse at 1, cat at 2, mouse turn
    return color[1][2][0];
}
