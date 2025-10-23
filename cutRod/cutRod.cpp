#include <iostream>
#include <vector>

using namespace std;

int helper(int l, vector<int>&prices, vector<int>&dp, vector<int>&res){
    if(dp[l] != -1){
        return dp[l];
    }
    else{
        dp[l] = INT_MIN;
        int cut;
        for(int i = 1; i <= l; i++){
            int temp = prices[i -1] + helper(l - i, prices, dp, res);
            if(temp > dp[l]){
                dp[l] = temp;
                res[l] = i;
            }
        }
        return dp[l];
    }
}

vector<int> curRod_topDown(int n, vector<int>prices){
    vector<int>dp(n + 1, -1);
    dp[0] = 0;
    vector<int>res(n + 1, -1);
    dp[1] = prices[0];
    res[0] = 0;
    res[1] = 1;
    int ans = helper(n, prices, dp, res);
    cout << endl << ans << endl;
    return res;
}

vector<int> cutRod_bottomUp(vector<int>prices){
    int n = prices.size();
    vector<int>res(n + 1, -1);
    vector<int>dp(n + 1, -1);
    int ans;
    dp[0] = 0;
    dp[1] = prices[0];
    res[1] = 1;
    res[0] = 0;
    int curr = INT_MIN;
    for(int l = 2; l <= n; l++){
        for(int i = 1; i <= l; i++){
            int temp = prices[i - 1] + dp[l - i];
            if(temp > curr){
                curr = temp;
                res[l] = i;
                dp[l] = temp;
            }
        }
    }
    cout << endl << dp[n] << endl;
    return res;
}

int main()
{
    vector<int>prices = {1, 2, 7, 8, 13, 14, 19, 20};
    vector<int>res = cutRod_bottomUp(prices);
    vector<int>res2 = curRod_topDown(prices.size(), prices);
    int n = prices.size();
    while(n > 0){
        cout << res[n] << ' ';
        n = n - res[n];
    }
}
