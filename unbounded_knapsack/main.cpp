#include <iostream>

using namespace std;

/*
Problem: https://www.naukri.com/code360/problems/unbounded-knapsack_1215029?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos

Solution
--------
State space
-----------
S = {i | 0 <= i <= w}
s(i) denots the max profit if we were allowed a capacity of i

Base state: f(0) = 0
End state: f(w)

Recursion
---------
f(i) = max({p + f(w - p) | p in profits array and p <= w })
*/

int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight){
    vector<int>dp(w + 1, 0);
    for(int i = 0; i <= w; i++){
        int res = 0;
        for(int j = 0; j < n; j++){
            if(weight[j] <= i){
                res = max(res, profit[j] + dp[i - weight[j]]);
            }
        }
        dp[i] = res;
    }
    return dp[w];
}