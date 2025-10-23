#include <iostream>
#include <thread>
#include<limits>

using namespace std;

//const double neg_inf = numeric_limits<double>::infinity() * -1;

/*

Solution
--------

State Space
-----------
S = {(i, j) | 0 <= i < n, i <= j < n}

s(i, j) means the sequence ai, a_i+1....a_j

f(i, j) is the longest palindronic subsequence in s(i, j)

Base state: i = j => f(i, j) = 1
Also, j < i => f(i, j) = 0

End state: s(0, n-1)

Recursion
---------
if(a[i] = a[j]) then f(i, j) = 2 + f(i + 1, j - 1)
else f(i, j) = max(f(i, j - 1), f(i + 1, j))

Interpretation: If a[i] = a[j] then they contribute 2 to the palindromic subsequence
else atleast one of them is omitted
*/

int helper(int i, int j, string s, vector<vector<int>>&dp){
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    if(i > j){
        return 0;
    }
    else if(i == j){
        return 1;
    }
    else{
        if(s[i] == s[j]){
            dp[i][j] = 2 + helper(i + 1, j - 1, s, dp);
        }
        else{
            dp[i][j] = max(helper(i + 1, j, s, dp), helper(i, j - 1, s, dp));
        }
        return dp[i][j];
    }
}

int mps(string s){
    int n = s.length();
    vector<vector<int>>dp(n, vector<int>(n, -1));
    return helper(0, n - 1, s, dp);
}

int mps_bottom_up(string s){
    int n = s.size();
    vector<vector<int>>dp(n, vector<int>(n, 0));
    // pending
    for(int i = 0; i < n; i++){
        dp[i][i] = 1;
    }
    for(int k = 1; k < n; k++){
        for(int i = 0; i <= n - k - 1; i++){
            // calculate dp[i][i + k]
            int ans;
            int j = i + k;
            if(s[i] == s[j]){
                ans = max(ans, 2 + dp[i + 1][j - 1]);
            }
            else{
                ans = max(dp[i + 1][j], dp[i][j - 1]);
            }
            dp[i][j] = ans;
        }
    }
    cout << endl;
    for(auto l : dp){
        for(int i : l){
            cout << i << ' '; 
        }
        cout << endl;
    }
    return dp[0].back();
}

int main(){
    string s = "racecar";
    mps_bottom_up(s);
}