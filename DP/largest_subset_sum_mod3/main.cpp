#include <vector>
#include <iostream>

using namespace std;

/*
Problem: Given an array of n positive integers, find the value of the largest subset-sum
which is divisible by 3.

State space
============
S = {(i, m) | 0 <= i < n, m = 0, 1, 2}
dp(i, m) denotes the largest subset-sum of the array a0,...,ai whose modulo 3 is m

Base bases
---------
dp[0][0] = (a0 % 3 == 0) ? a0 : 0
dp[0][1] = (a0 % 3 == 1) ? a0 : -1
dp[0][2] = (a0 % 3 == 2) ? a0 : -1

Recursive definition
=====================
Calculating dp[i][m]
We will tackle with 2 cases:

Case 1: include ai
-------------------
let r = (m - (ai % 3) + 3) % 3
if dp[i-1][r] = -1 then res1 = -1
else res1 = dp[i-1][r] + ai

Case 2: exclude ai
-------------------
res2 = dp[i - 1][m]

Finally, dp[i][m] = max(res1, res2)
*/

int maximalSubsetSum(vector<int> arr)
{
    int n = arr.size();
    if (n == 0)
    {
        return 0;
    }
    vector<vector<int>> dp(n, vector<int>(3, -1));

    // base cases
    dp[0][0] = (arr[0] % 3 == 0) ? arr[0] : 0;
    dp[0][1] = (arr[0] % 3 == 1) ? arr[0] : -1;
    dp[0][2] = (arr[0] % 3 == 2) ? arr[0] : -1;

    for (int i = 1; i < n; i++)
    {
        for (int m = 0; m < 3; m++)
        {

            // include ai
            int res1;
            int r = (m - (arr[i] % 3) + 3) % 3;
            if (dp[i - 1][r] == -1)
            {
                res1 = -1;
            }
            else
            {
                res1 = dp[i - 1][r] + arr[i];
            }

            // exclude ai
            int res2 = dp[i - 1][m];

            dp[i][m] = max(res1, res2);
        }
    }

    return dp[n - 1][0];
}

int main()
{
    vector<int> arr = {1, 2, 5, 3};
    cout << maximalSubsetSum(arr);
}