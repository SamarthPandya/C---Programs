#include <iostream>
#include <vector>

using namespace std;

/*

Problem
-------
We are looking for an O(n^2) algorithm to find the longest increasing subsequence in a sequence of n integers.

Solution
--------
State Space
-----------
S = {i | 0 <= i < n}
where s(i) deontes the length of the longest increasing subsequence ending at ai

Base state: s(0) = 1 since there is only one element

end state: there is no end state, we take max of all states's optimal values

Recurrence:
res = INT_MIN
for j in range 0,1..i-1:
    if nums[j] < nums[i]: dp[i]= max(dp[i], 1 + dp[j])
*/

int lis_val(vector<int>nums){
    int n = nums.size();
    vector<int>dp(n, 1);
    int ans = 1;

    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(nums[j] < nums[i]){
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
        ans = max(ans, dp[i]);
    }

    return ans;
    
}

vector<int>list_sol(vector<int>&nums){
    int n = nums.size();
    vector<int>prev(n, -1);
    vector<int>dp(n, 1);

    int ind_of_max = 0;
    int max_val = 1;

    for(int i = 1; i < n; i++){
        int temp = 1;
        for(int j = 0; j < i; j++){
            if(nums[i] > nums[j]){
                temp = 1 + dp[j];
            }
            if(temp > dp[i]){
                prev[i] = j;
                dp[i] = temp;
            }
        }
        if(max_val < dp[i]){
            max_val = dp[i];
            ind_of_max = i;
        }
    }
    
    vector<int>s;

    int i = ind_of_max;
    while(i != -1){
        s.insert(s.begin(), nums[i]);
        i = prev[i];
    }

    return s;
}


int main(){
    vector<int>nums = {1, 4, 2, 5, -3, 3, 4, 5, 10};
    cout << lis_val(nums) << endl;
    vector<int>s = list_sol(nums);
    for(int i : s){
        cout << i << ' '; 
    }
}