#include <iostream>

using namespace std;

/*
Problem: https://www.naukri.com/code360/problems/number-of-subsets_3952532?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos

Solution
--------
Given an array and am int target, we wish to count the number of subsets of arr that sum up to target

Ref to build the solution from: subarray_target_sum/main.cpp
State space
-----------
S = {(i, j) | 0 <= i <= n, 0 <= j <= starget}

s(i, j) denotes the number of subsets of {a1, a2...ai} summing up to j

Base cases
----------
s(0, 0) = 1 and s(0, j) = 0 for j > 0

End state: s(n - 1, target)

Recursion
---------
f(i,j) = f(i - 1,j - arr[i - 1) + f(i - 1, j)
where the first term is for inclusion and the second for exclusion of arr[i-1]
*/

int helper(int i, int j, vector<int>&arr, vector<vector<int>>&dp){
    if(j < 0){
        return 0;
    }
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    else{
        int excl = helper(i - 1, j, arr, dp);
        
        int incl = 0;
        if(arr[i - 1] <= j){
            incl = helper(i - 1, j - arr[i - 1], arr, dp);
        }
        dp[i][j] = incl + excl;
        return dp[i][j];
    }
}

int findWays(vector<int>& arr, int k)
{
	int n = arr.size();
    vector<vector<int>>dp(n + 1, vector<int>(k + 1, -1));
    dp[0][0] = 1;
    for(int j = 1; j < k + 1; j++){
        dp[0][j] = 0;
    }

    int res =  helper(n, k, arr, dp);
    return res;
}

int bottom_up(vector<int>& arr, int k){
    int n = arr.size();
    vector<vector<int>>dp(n + 1, vector<int>(k + 1, -1));
    dp[0][0] = 1;
    for(int j = 1; j < k + 1; j++){
        dp[0][j] = 0;
    }
    for(int i = 1; i < n + 1; i++){
        for(int j = 0; j <= k; j++){
            int excl = dp[i-1][j];
        int incl = 0;
        if(arr[i - 1] <= j){
            incl = dp[i-1][j - arr[i - 1]];
        }
        dp[i][j] = incl + excl;
        }
    }
    return dp[n][k];
}

int bottom_up_space_opt(vector<int>& arr, int k){
    int mod = 1e9 + 7;
    vector<int>curr(k + 1, 0);
    curr[0] = 1;
    for(int i = 1; i <= arr.size(); i++){
        vector<int>temp(k + 1);
        for(int j = 0; j < k + 1; j++){
            int excl = curr[j];
            int incl = 0;
            if(arr[i - 1] <= j){
                incl = curr[j - arr[i -  1]];
            }
            temp[j] = (incl % mod + excl % mod) % mod;
        }
        curr = temp;
    }
    return curr.back();
}

int main(){
    vector<int>arr = {2, 1, 3, 4};
    cout << bottom_up_space_opt(arr, 5);
}

