#include <iostream>
#include <unordered_set>

using namespace std;

/*
For each index i, the plan is to save two vals, 
1) Length of the longest increasing subsequence ending at i : inc(i)
2) Length of the longest decreasing subsequence starting at i : dec(i)

these two can be found using the lis algorithm

start with res = 1
res = max({dec(i) + inc(i) - 1} | 0 <= i < n})
*/

int longestBitonicSubsequence(vector<int>& arr, int n)
{
	vector<pair<int, int>>dp(n, {1, 1});
    
    // for inc
    for(int i = 1; i < n; i++){
        int res = 1;
        for(int j = 0; j < i; j++){
            if(arr[j] < arr[i]){
                res = max(res, 1 + dp[j].first);
            }
        }
        dp[i].first = res;
    }

    int ans = 1;

    // for dec
    for(int i = n - 1; i >= 0; i--){
        int res = 1;
        for(int j = n - 1; j > i; j--){
            if(arr[j] < arr[i]){
                res = max(res, 1 + dp[j].second);
            }
        }
        dp[i].second = res;
        ans = max(ans, dp[i].first + dp[i].second - 1);
    }

    return ans;
}

int main() {
    vector<int>arr = {1, 2, 1, 2, 1};
    cout << longestBitonicSubsequence(arr, arr.size());
}