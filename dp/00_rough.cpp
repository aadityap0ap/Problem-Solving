
#include<bits/stdc++.h>
using namespace std;

vector<int> weight;
vector<int> value;
vector<vector<int>> dp01, dpINF;

// ---------------- 0/1 Knapsack ----------------
int knapsack01(int index , int w_left ){
    if(index >= value.size()) return 0;
    if(w_left <= 0) return 0;
    if(dp01[index][w_left] != -1) return dp01[index][w_left];
    
    int not_taken = knapsack01(index+1, w_left);
    int taken = 0;
    if(w_left >= weight[index]){
        taken = value[index] + knapsack01(index+1, w_left - weight[index]);
    }
    
    return dp01[index][w_left] = max(taken, not_taken);
}

void generate01(int index , int w_left, vector<int>& solution){
    if (index >= value.size() || w_left <= 0) return;

    int not_taken = knapsack01(index+1, w_left);
    int taken = -1;
    if(w_left >= weight[index]){
        taken = value[index] + knapsack01(index+1,w_left-weight[index]);
    }
    
    if(taken > not_taken){
        solution.push_back(index);
        generate01(index+1, w_left-weight[index], solution);
    } else {
        generate01(index+1, w_left, solution);
    }
}

// ---------------- Unbounded Knapsack ----------------
int knapsack0INF(int index , int w_left ){
    if(index >= value.size()) return 0;
    if(w_left <= 0) return 0;
    if(dpINF[index][w_left] != -1) return dpINF[index][w_left];
    
    int not_taken = knapsack0INF(index+1, w_left);
    int taken = 0;
    if(w_left >= weight[index]){
        taken = value[index] + knapsack0INF(index, w_left - weight[index]); 
    }
    
    return dpINF[index][w_left] = max(taken, not_taken);
}

void generateINF(int index , int w_left, unordered_map<int,int>& solution){
    if (index >= value.size() || w_left <= 0) return;

    int not_taken = knapsack0INF(index+1, w_left);
    int taken = -1;
    if(w_left >= weight[index]){
        taken = value[index] + knapsack0INF(index, w_left-weight[index]);
    }
    
    if(taken > not_taken){
        solution[index]++; // count this item
        generateINF(index, w_left-weight[index], solution); // stay at same index
    } else {
        generateINF(index+1, w_left, solution);
    }
}

// ---------------- Main ----------------
int main(){
    int capacity, n;
    cin >> capacity >> n;
    
    weight.resize(n);
    value.resize(n);
    dp01.assign(n, vector<int>(capacity+1, -1));  
    dpINF.assign(n, vector<int>(capacity+1, -1));  
    
    for(int i = 0; i < n; i++){
        int v, w;
        cin >> v >> w;   // input: value then weight
        value[i] = v;
        weight[i] = w;
    }
    
    // ---------- 0/1 Knapsack ----------
    int max_value01 = knapsack01(0, capacity);
    cout << "0/1 Knapsack Max Value: " << max_value01 << endl;
    vector<int> solution01;
    generate01(0, capacity, solution01);
    for(int i : solution01){
        cout << "Item index " << i << " -> weight: " << weight[i] << ", value: " << value[i] << endl;
    }
    
    // ---------- Unbounded Knapsack ----------
    int max_valueINF = knapsack0INF(0, capacity);
    cout << "\nUnbounded Knapsack Max Value: " << max_valueINF << endl;
    unordered_map<int,int> solutionINF;
    generateINF(0, capacity, solutionINF);
    for(auto &p : solutionINF){
        cout << "Item index " << p.first << " -> weight: " << weight[p.first] 
             << ", value: " << value[p.first] << " taken " << p.second << " times\n";
    }
    
    return 0;
}

class Solution {
public:
    int n;                    // size of the input array
    vector<int> parent;        // stores the index of previous element in the LIS
    vector<int> dp;            // dp[i] = length of LIS ending at index i

    // Recursive function to calculate LIS ending at 'index'
    int solve(int index, vector<int>& arr) {
        // If we already calculated LIS for this index, return it
        if (dp[index] != -1) return dp[index];

        int count = 1;                 // Minimum LIS ending at index is 1 (just the element itself)
        parent[index] = -1;            // By default, no previous element in the LIS

        // Check all elements before current index
        for (int prev = 0; prev < index; prev++) {
            // If previous element is smaller, it can be part of LIS
            if (arr[prev] < arr[index]) {
                int temp = 1 + solve(prev, arr); // LIS if we include arr[prev] before arr[index]
                // Update count and parent if this gives a longer LIS
                if (temp > count) {
                    count = temp;
                    parent[index] = prev;  // Track that prev element comes before current in LIS
                }
            }
        }

        return dp[index] = count;  // Save and return LIS length ending at this index
    }

    // Function to get the actual LIS sequence
    vector<int> getLIS(vector<int>& arr) {
        n = arr.size();                // Get size of array
        dp.assign(n, -1);              // Initialize dp with -1 (means not calculated)
        parent.assign(n, -1);          // Initialize parent with -1 (no previous element)

        int best_len = 0;              // Length of the longest LIS found so far
        int best_index = -1;           // Index where the longest LIS ends

        // Try to calculate LIS ending at each index
        for (int i = 0; i < n; i++) {
            int len = solve(i, arr);   // Compute LIS ending at index i
            if (len > best_len) {      // If this LIS is longer than previous best
                best_len = len;        // Update best length
                best_index = i;        // Update ending index of longest LIS
            }
        }

        // Reconstruct LIS using parent array
        vector<int> lis;               // To store the LIS sequence
        while (best_index != -1) {     // Follow parent pointers from best_index
            lis.push_back(arr[best_index]); // Add current element to LIS
            best_index = parent[best_index]; // Move to previous element in LIS
        }

        reverse(lis.begin(), lis.end()); // Reverse to get LIS in correct order
        return lis;                      // Return the final LIS
    }
};
