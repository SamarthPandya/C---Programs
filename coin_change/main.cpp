#include <iostream>

using namespace std;

/*
Problem: https://leetcode.com/problems/coin-change/

Solution:

State Space
-----------
S = {r | 0 <= r <= amount}
s(r) denotes the minimum coins required to create an amount r

Base state : f(0) = 0 no coins needed

End state: f(amount)

Recursion
---------
f(r) = min({f(r - c) | c in coins array}) + 1
*/

int helper(int amount, vector<int>&coins, unordered_map<int, int>&dp){
    if(dp.find(amount) != dp.end()){
        return dp[amount];
    }
    int excluding = INT_MAX;
    for(int c : coins){
        if(c <= amount){
            excluding = min(excluding, helper(amount - c, coins, dp));
        }
    }
    dp[amount] = excluding == INT_MAX ? INT_MAX : 1 + excluding;
    return dp[amount];
}

int top_down(vector<int>&coins, int amount){
    unordered_map<int, int>dp;
    dp[0] = 0;
    int ans = helper(amount, coins, dp);
    ans == INT_MAX ? -1 : ans;
}

int bottom_up(vector<int>&coins, int amount){
    vector<int>dp(amount + 1);
    dp[0] = 0;
    for(int k = 1; k <= amount; k++){
        int ans = INT_MAX;
        for(int c : coins){
            if(c <= k){
                ans = min(ans, dp[k - c]);
            }
        }
        dp[k] = ans == INT_MAX ? INT_MAX : 1 + ans;
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int main(){
    vector<int>coins = {1, 2, 5};
    return 0;
}