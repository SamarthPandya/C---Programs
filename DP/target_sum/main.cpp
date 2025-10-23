    #include <iostream>

    using namespace std;

    /*
    Problem: https://leetcode.com/problems/target-sum/

    Solution: Done with memoisation, where the memo is a vector of maps

    */

    int helper(int t, int i, vector<unordered_map<int, int>>& dp,
               vector<int>& nums) {
        if(i < 0){
            if(t == 0){
                return 1;
            }
            else{
                return 0;
            }
        }
        if (dp[i].find(t) != dp[i].end()) {
            return dp[i][t];
        } else {
            int ways_with_plus = helper(t - nums[i], i - 1, dp, nums);
            int ways_with_minus = helper(t + nums[i], i - 1, dp, nums);
            dp[i][t] = ways_with_minus + ways_with_plus;
            return dp[i][t];
        }
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        vector<unordered_map<int, int>> dp(n);
        return helper(target, n - 1, dp, nums);
    }

    int findTargetSumWays_bottom_up(vector<int>&nums, int target){
        int n = nums.size();
        if(n == 0) return 0;
        vector<int>curr = {-1 * nums[0], nums[0]};
        for(int i = 1; i < n; i++){
            vector<int>temp;
            for(int j : curr){
                temp.push_back(j - nums[i]);
                temp.push_back(j + nums[i]);
            }
            curr = temp;
        }
        int res = 0;
        for(int i : curr){
            if(i == target){
                res++;
            }
        }
        return res;
    }

    int main(){
        vector<int>nums = {1, 1, 1, 1, 1};
        cout << findTargetSumWays_bottom_up(nums, 3);
    }