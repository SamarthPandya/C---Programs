#include <iostream>
#include <unordered_set>

using namespace std;

/*
Problem: https://leetcode.com/problems/largest-divisible-subset/

Solution
--------
State space
------------
S = {i | i in nums}
f(i) is the largest div subset that ends with i i.e i is the largest element of it

Base state
----------
if nums is sorted then f(nums[0]) = {nums[0]} since we cannot include anything smaller than it

End state
----------
There is no end state: we go through each f(i) and take the maximum

Recursion
---------
f(nums[i]) = max({{nums[i]} U f(k) |  for k = nums[0], nums[1]...nums[i - 1]})
*/

vector<int> largestDivisibleSubset(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    unordered_map<int, vector<int>>dp;
    dp[nums[0]] = {nums[0]};
    int res_key = nums[0];
    for(int i = 1; i < n; i++){
        int temp_key = nums[i];
        dp[temp_key] = {nums[i]};
        for(int j = 0; j < i; j++){
            if(nums[i] % nums[j] == 0){
                if(dp[nums[j]].size() + 1 > dp[temp_key].size()){
                temp_key = nums[j];
                }
            }
        }
        dp[nums[i]] = dp[temp_key];
        dp[nums[i]].push_back(nums[i]);
        if(dp[res_key].size() < dp[nums[i]].size()){
            res_key = nums[i];
        }
    }
    return dp[res_key];
}

int main() {
    vector<int>nums = {1, 2, 3};
    vector<int>sol = largestDivisibleSubset(nums);
    for(int i : sol){
        cout << i << ' ';
    }
}