#include <iostream>

using namespace std;

/*
Problem: https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/

Solution: recursive
*/

void helper(int i, int&s, int curr_s, vector<int>&arr, int&res, int currSize){
    if(currSize == arr.size() / 2){
        res = min(res, abs(curr_s - (s - curr_s)));
    }
    if(i == arr.size()){
        return;
    }
    
    //call for taken
    helper(i + 1, s, curr_s + arr[i], arr, res, currSize + 1);

    //call for not taken
    helper(i + 1, s, curr_s, arr, res, currSize);
}

int minimumDifference(vector<int>& nums) {
    int res = INT_MAX;
    int s = 0;
    for(int i : nums){
        s += i;
    }
    int curr_s = 0;
    helper(0, s, curr_s, nums, res, 0);
    return res;
}

int main(){
    vector<int>arr = {-36, 36};
    cout << minimumDifference(arr);
}