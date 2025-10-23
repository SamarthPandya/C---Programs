#include <iostream>

using namespace std;

/*
Problem: https://leetcode.com/problems/partition-equal-subset-sum/

Solution
-------
trying raw recursive first : bullshit, good for recursive thinking practice though

Actual Solution: If the array sum is odd, it can be partitioned because odd nums are not div by 2.
If it is even, run the subarray_target_sum with (s/2) where s is the sum of all elements
*/

bool helper(int i, int curr, int total, vector<int>&arr){
    if(i == arr.size()){
        return false;
    }
    if(curr == total){
        return true;
    }
    bool taken = helper(i + 1, curr + arr[i], total - arr[i], arr);
    if(taken){
        return true;
    }
    bool not_taken = helper(i + 1, curr, total, arr);
    return not_taken;
}

bool exists(vector<int>&arr){
    int s = 0;
    for(int i : arr){
        s += i;
    }
    return helper(0, 0, s, arr);
}

int main(){
    vector<int>arr = {1, 5, 11, 5};
    cout << exists(arr);
}