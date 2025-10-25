#include <iostream>

using namespace std;

/*
Problem: https://leetcode.com/problems/distinct-subsequences/description/

Solution
---------
State space
-----------
S = {(i, j) | 0 <= i < m, 0 <= j < n}
f(i, j) denotes the num of distinct susequences of the string s0, s1...s_(i - 1)
that are equal to t0, t1...t_(j - 1)

Base case
----------
f(0, 0) = 1
f(0, j) = 0 for j > 0

f(i, 0) = 1 for i > 0

End state: f(m, n)

Recursion
---------
f(i, j) = s[i] == t[j] ? f(i - 1, j - 1) + f(i - 1, j) : f(i - 1, j)

Interpretation:
--------------
In either case, we have atleast f(i - 1, j) distinct subsequences i.e.
those of s which are equal to t0,...t_(j - 1) without considering s[i - 1].

But in the case where s[i - 1] == t[j - 1], we have a few extra as well i.e.
those formed this way:

all of s0...s_(i - 2) matching t0...t_(i - 2) and then concatenate the char s[i - 1] to them.

So for each of f(i - 1, j - 1) we create one which satisifes f(i, j) by concatenating the common
equal character.
*/


int numDistinct(string s, string t) {
    int m = s.size(), n = t.size();
    vector<vector<int>>dp(m + 1, vector<int>(n + 1));
    for(int i = 0; i <= m; i++){
        dp[i][0] = 1;
    }
    for(int j = 1; j <= n; j++){
        dp[0][j] = 0;
    }
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            int res = dp[i - 1][j];
            if(s[i - 1] == t[j - 1]){
                res += dp[i - 1][j - 1];
            }
            dp[i][j] = res;
        }
    }
    return dp[m][n];
}

int space_optimised_bottom_up(string s, string t){
    int m = s.size(), n = t.size();
    vector<unsigned long>curr(n + 1, 0);
    curr[0] = 1;
    for(int j = 1; j <= n; j++){
        curr[j] = 0;
    }

    for(int i = 1; i <= m; i++){
        vector<unsigned long>temp(n + 1);
        temp[0] = 1;
        for(int j = 1; j <= n; j++){
            int res = curr[j];
            if(s[i - 1] == t[j - 1]){
                res += curr[j - 1];
            }
            temp[j] = res;
        }
        curr = temp;
    }
    
    return curr.back();

}

int main(){
    string s = "rabbbit", t = "rabbit";
    cout << space_optimised_bottom_up(s, t);
}