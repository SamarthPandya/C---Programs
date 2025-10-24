#include <iostream>

using namespace std;

/*
Problem: https://leetcode.com/problems/longest-common-subsequence/description/

Solution:

State space
-----------
S = {(i, j) | 0 <= i < m, 0 <= j < n}
s(i, j) denotes all subsequences of text1 upto the index i and similarly upto the index j for text2
f(i, j) denotes the l.c.s ot text1 upto index i and text2 upto index j

Base states:
f(0, j) for 0 <= j < n
f(i, 0) for 0 <= i < m
We would have to determine these values by iteration

End state: f(m - 1, n - 1)

Recursion
--------
f(i, j) = text1[i] == text2[j] ? 1 + f(i - 1, j - 1) : max(f(i - 1, j), f(i, j - 1))

This is to say that if both text1[i] and text2[j] are equal then this char would be a
part of the l.c.s or else one of them can be of which we take the max
*/

int helper(int i, int j, vector<vector<int>>&dp, string text1, string text2){
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    else{
        int res;
        if(text1[i] == text2[j]){
            res =  1 + helper(i - 1, j - 1, dp, text1, text2);
        }
        else{
            res = max(helper(i - 1, j, dp, text1, text2), helper(i, j - 1, dp, text1, text2));
        }
        dp[i][j] = res;
        return dp[i][j];
    }
}

int top_down(string text1, string text2){
    int m = text1.size(), n = text2.size();
    vector<vector<int>>dp(m, vector<int>(n, -1));
    int flag = 0;
    for(int j = 0; j < n; j++){
        if(text1[0] == text2[j]) flag = 1;
        dp[0][j] = flag;
    }
    flag = 0;
    for(int i = 0; i < m; i++){
        if(text1[i] == text2[0]) flag = 1;
        dp[i][0] = flag;
    }
    return helper(m - 1, n - 1, dp, text1, text2);
}

int bottom_up(string text1, string text2){
    int m = text1.size(), n = text2.size();
    vector<int>curr(n, -1);
    int flag = 0;
    for(int j = 0; j < n; j++){
        if(text1[0] == text2[j]){
            flag = 1;
        }
        curr[j] = flag;
    }
    flag = 0;
    for(int i = 1; i < m; i++){
        if(text1[i] == text2[0]) flag = 0;
        vector<int>temp(n, -1);
        temp[0] = flag;
        for(int j = 1; j < n; j++){
            int res;
            if(text1[i] == text2[j]){
                res = 1 + curr[j - 1];
            }
            else{
                res = max(curr[j], temp[j - 1]);
            }
            temp[j] = res;
        }
        curr = temp;
    }
    return curr.back();
}

int main(){
    string text1 = "avsd", text2 = "vsdavd";
    cout << bottom_up(text1, text2);
}
