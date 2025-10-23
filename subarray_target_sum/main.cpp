#include <iostream>

using namespace std;

/*
Problem: https://www.naukri.com/code360/problems/ninja-and-his-friends_3125885?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=0

Solution
--------
Inlcuding or excluding an element is a choice, and this choice affects our future choices
of including or excluding other elements.

State space
-----------
S = {(i, j) | 0 <= i <= n, 0 <= j <= target}

s(i, j) is true if there is a subarray in a1,a1...ai such that the sum of that subarray is j
and false otherwise

Note that we are there are (n + 1) possibiltities for the first element in the s(i, j):

i = 0 means taking no element
i = 1 means taking a0
i = 2 means taking a0, a1
.
.
i = n means taking a0, a1...a_(n-1)

Similarly j varies from 0 to target

Base states
-----------
s(0, j) = true if j = 0, false otherwise

End state
---------
s(n-1, target)

Recursion
---------
f(i, j) = f(i - 1, j) || f(i, j - a_(i - 1))

Here f(i - 1, j) means whether the target is possible exluding element i - 1
and f(i - 1, j - a_i) means we have considered a_(i-1) in the subset and now we are
looking for the target j - a_(i-1) in the range {}, a0, a1...a_(i-2)

*/

int helper(int i, int j, vector<vector<int>>&dp, vector<int>&arr){

    if(j == 0){
        dp[i][j] = 1;
        return dp[i][j];
    }

    if(i == 0){
        dp[i][j] = 0;
        return dp[i][j];
    }

    if(dp[i][j] != -1){
        return dp[i][j];
        return dp[i][j];
    }

    else{
        int not_taken = helper(i - 1, j, dp, arr);
        int taken = 0;
        if(arr[i - 1] <= j){
            taken = helper(i - 1, j - arr[i - 1], dp, arr);
        }
        dp[i][j] = not_taken || taken;
        return dp[i][j];
    }
}

bool top_down(vector<int>arr, int target){
    int n = arr.size();
    vector<vector<int>>dp(n + 1, vector<int>(target + 1, -1));
    return helper(n, target, dp, arr);
}

bool bottom_up(vector<int>arr, int target){
    int n = arr.size();
    vector<vector<int>>dp(n + 1, vector<int>(target + 1, -1));

    // base cases: if j is 0, and if i is 0
    for(int i = 0; i < n + 1; i++){
        dp[i][0] = 1;
    }
    for(int j = 1; j < target + 1; j++){
        dp[0][j] = 0;
    }

    for(int i = 1; i < n + 1; i++){
        for(int j = 1; j < target + 1; j++){
            int not_taken = dp[i - 1][j];
            if(not_taken == 1){
                dp[i][j] = 1;
            }
            else{
                int taken = 0;
                if(arr[i - 1] <= j){
                    taken = dp[i - 1][j - arr[i-1]];
                }
                dp[i][j] = taken;
            }
        }
    }

    for(auto l : dp){
        for(int i : l){
            cout << i << ' ';
        }
        cout << endl;
    }

    return dp[n][target];
}

int main(){
    vector<int>arr = {1, 8, 9, 5};
    cout << bottom_up(arr, 11);
    cout << top_down(arr, 11);
}