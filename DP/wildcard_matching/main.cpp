#include <iostream>

using namespace std;

/*
Problem: https://leetcode.com/problems/wildcard-matching/

Constraints:
---------------------------------------------------------
0 <= s.length, p.length <= 2000
s contains only lowercase English letters.
p contains only lowercase English letters, '?' or '*'.
---------------------------------------------------------

Solution
---------------------------------------------------------
m = s.size(), n = p.size()
State space
---------------------------------------------------------
S = {(i, j) | 0 <= i <= m, 0 <= j <= n}
s(i, j) denotes the first i chars from s and j from p
f(i, j) = (s[0...i-1] matches p[0...j-1]) ? true : false

Base state:
f(0, 0) = true since an empty string matches an empty pattern.

f(i, 0) = false if i > 0 since a non-empty string cannot match 
an empty pattern.

-- f(0, j) is only true if the pattern p[0...j-1] consists entirely of '*':
    f(0, j) = (p[j - 1] == '*') AND (f(0, j - 1) is true)
This simplifies to: f(0, j) is true if p's prefix of length j is just "*, *, ..., *"

End state: f(m, n)

Recursion
---------------------------------------------------------
To calculate f(i, j) we look at s[i - 1] and p[j - 1]

If p[j - 1] is a lowercase English letter OR p[j - 1] = '?':
    // Must match the current characters; solution depends on the previous diagonal state.
    if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
        return f(i - 1, j - 1)

If p[j - 1] = '*':
    REFINEMENT: Use the O(1) transition to maintain O(m*n) complexity.
    '*' can match an empty string OR match one or more characters.
    
    Case 1: '*' matches an empty string. Solution depends on matching s[i] with p[j-1].
     = f(i, j - 1) 

    Case 2: '*' matches s[i - 1] and potentially more. Solution depends on matching s[i-1] with p[j].
     = f(i - 1, j)

    return f(i, j - 1) OR f(i - 1, j)

If none of the above conditions are met (i.e., p[j-1] is a character and s[i-1] doesn't match):
    return false

*/

bool isMatch(string s, string p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>>dp(m + 1, vector<bool>(n + 1, 0));

    // base cases

    dp[0][0] = 1; // an empty string matches an empty string

    for(int i = 1; i <= m; i++){
        dp[i][0] = 0; // an empty string never matches a non empty string
    }

    // an empty string matches a string of all *'s and nothing otherwise
    for(int j = 1; j <= n; j++){
        dp[0][j] = (p[j - 1] == '*' && dp[0][j - 1] == 1) ? 1 : 0;
    }

    // iteration
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            bool res;
            if(p[j - 1] == '?'){
                res = dp[i - 1][j - 1];
            }
            else if(p[j - 1] == '*'){
                res = dp[i - 1][j] || dp[i][j - 1];
            }
            else{
                if(s[i - 1] == p[j - 1]){
                    res = dp[i - 1][j - 1];
                }
                else{
                    res = false;
                }
            }
            dp[i][j] = res;
        }
    }

    return dp[m][n];

}

int main(){
    string s = "aerdsfc", t = "a*?c";
    cout << isMatch(s, t);
}