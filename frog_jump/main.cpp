#include <iostream>
#include <cmath>

using namespace std;

/* 

Problem: https://takeuforward.org/plus/dsa/problems/frog-jump

Solution
--------
We maintain a vector dp where dp[i] denotes the min energy needed to reach that step. dp[0] = 0 since
the frog is already standing there.

Base states
----------
dp[0] = 0;
dp[1] = abs(h[1] - h[0])


End state: dp[n - 1];

Recursion
---------
dp[i] = min(dp[i - 1] + abs(h[i] - h[i - 1]), dp[i - 2] + abs(h[i] - h[i - 2]))
*/

int frogJump(vector<int>h){
    int n = h.size();
    vector<int>dp(n, INT_MAX);
    dp[0] = 0;
    dp[1] = abs(h[1] - h[0]);
    for(int i = 2; i < n; i++){
        dp[i] = min(dp[i - 1] + abs(h[i] - h[i - 1]), dp[i - 2] + abs(h[i] - h[i - 2]));
    }
    return dp.back();
}

int main(){
    vector<int>h = {3, 2, 4, 1, 2, 1, 4};
    cout << frogJump(h);
}