#include <iostream>

using namespace std;

/*
Problem: https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

Solution
--------
State space
-----------
S = {(i, j) | 0 <= i < n; i <= j < n}
s(i, j) denotes the string si, s_(i + 1).....sj
f(i, j) denotes the minimum insertions to make s(i, j) a palindrome

Base state: f(i, i) = 0 since already a palindrome
End state: f(0, n - 1)

Recurrrence
-----------
f(i, j) = (s[i] == s[j]) ? f(i + 1, j - 1) : 1 + min(f(i + 1, j), f(i, j - 1))

What it means? if we find the characters at both end to be equal, 
we only need to worry about the remainng string without them i.e. s(i + 1, j - 1)
Else we need to look at two string s(i, j - 1) and s(i + 1, j):
we can make the original string a palindrome:
1) by adding si to the end in which case, the total would be 1 + f(i + 1, j)
2) by adding sj to the start in which case, the total would be 1 + f(i, j - 1)

But since we are looking at the minimum, we look the minimum of both the above options
*/

int minInsertions(string s) {
    int n = s.size();
    vector<vector<int>>dp(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        dp[i][i] = 0;
    }

    for(int k = 1; k < n; k++){
        for(int j = k; j < n; j++){
            int i = j - k;
            dp[i][j] = (s[i] == s[j]) ? dp[i + 1][j - 1] : 1 + min(dp[i][j - 1], dp[i + 1][j]);
        }
    }

    return dp[0].back();
}

int main(){
    string s = "asdcx";
    cout << minInsertions(s);
}