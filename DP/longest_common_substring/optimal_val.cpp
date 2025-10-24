#include <iostream>

using namespace std;

/*
Problem
--------
A substring of a string is a subsequence in which all the characters are consecutive. 
Given two strings, 
1) we need to find the longest common substring.
2) We need to print the length of the longest common substring.

Solution
--------
State space
-----------
S = {(i, j) | 0 <= i < m, 0 <= j < n}
f(i, j) denotes the maximal common subsequence that ends at index i in text1 and j in text2

Base cases: 
f(0, j) = text1[0] == text2[j] ? 1 : 0
f(i, 0) = text1[i] == text2[0] ? 1 : 0

Ends state: There is no ends state, the final result is the max of all cells

Recursion
----------
f(i, i) = (text1[i] == text2[j]) ? 1 + f(i - 1, j - 1) : 0
this is to mean that if the two chars are equal they are a part of the l.c.substring and then
we add the length of the l.c.substring for the previous indices in both

If both are unequal then there is no common substring ending at i in s1 and j in s2
*/

int bottom_up(string text1, string text2){
    int m = text1.size(), n = text2.size();
    vector<vector<int>>dp(m, vector<int>(n, 0));
    int res = 0;
    for(int i = 0; i < m; i++){
        if(text1[i] == text2[0]) {
            dp[i][0] = 1;
            res = 1;
        }
    }
    for(int j = 0; j < n; j++){
        if(text1[0] == text2[j]) {
            dp[0][j] = 1;
            res = 1;
        }
    }
    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            if(text1[i] == text2[j]){
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else{
                dp[i][j] = 0;
            }
            res = max(res, dp[i][j]);
        }
    }
    return res;
}

int main(){
    string s1 = "abace", s2 = "eabae";
    cout << bottom_up(s1, s2);
}
