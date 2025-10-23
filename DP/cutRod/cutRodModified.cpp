#include <iostream>
#include <vector>

using namespace std;

int cutRod_bottomUp(vector<int>prices, int cutting_cost){
    int n = prices.size();
    vector<int>dp(n + 1, 0);
    
    // max revenue from a rod of length 0 is 0 and from 1 is prices[1 - 0]
    dp[0] = 0;
    dp[1] = prices[0];

    for(int l = 2; l <= n; l++){
        int curr = INT_MIN;
        for(int k = 1; k <= l; k++){
            curr = max(curr, prices[k - 1] + dp[l - k] - cutting_cost);
        }
        dp[l] = curr;
    }
    return dp[n];
}

int main(){
    vector<int>prices = {1, 4, 2, 5};
    cout << cutRod_bottomUp(prices, 2);
}