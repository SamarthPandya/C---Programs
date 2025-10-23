#include <iostream>

using namespace std;

/*

Problem
--------
Given a vector of pairs, P = {p0, p1, p2....p_(n-1)}, each pair denoting the dimensions of a matrix, find the the most
optimal way to multiply the matrices.

Observations
-----------
-   The cost of multiplying two matrixes whose dimensions are (x1, x2) and (x2, x3) is x1 * x2 * x3, assuming
    the cost of a single mutliplication is 1.
-   A chain can may be parenthesized in multiple ways, each resulting in a different overall cost.
-   Let P(i) denote the number of difference parenthisizations of a chain of length i, then P(1) = 1,
    P(n) = P(1) * P(n - 1) + P(2) * P(n - 2) .... + P(n - 1) * P(1)

State Space
-----------
S = {(i, j) | 0 <= i < n, i <= j < n}

A state s = (i, j) denotes the chain of matrix dim pairs {pi, p_(i + 1), ...., pj}

f(i, j): optimal way to evaluate the chain of matrix dim pairs  given by the state (i, j).

Base and End states
-------------------
Base states: {(i, i) | 0 <= i < n}

end state: (0, n - 1)

Recursive definiton
-------------------
f(i, j) = min{f(i, k) + f(k + 1, j) + P[i][0] * P[i][1] * P[j][1] | 1 <= k <= j - 1}

Here we are taking the minimum cost among the cost of all parenthisizations; f(i, k) is the optimal
cost of evaluating the chain from i upto k, f(k + 1, j) is for evalutation of the matrix chain from k + 1
upto j and finally, once both of them have been evaluated, we have to account for the cost of evaluating the
pair of final two matrices thus obtained which is the third term.

There is optimal substructure and overlapping subproblems
*/

long long min_cost(vector<pair<int, int>> dims)
{
    int n = dims.size();


    // table for bottom up evaluation
    vector<vector<long long>> dp(n, vector<long long>(n, INT_MAX));
    vector<vector<int>>s(n, vector<int>(n, 0));

    // base cases
    for(int i = 0; i < n; i++){
        dp[i][i] = 0;
        s[i][i] = i;
    }

    for(int k = 1; k < n; k++){
        for(int j = k; j < n; j++){
            for(int t = j - k; t < j; t++){
                dp[j - k][j] = min(dp[j - k][j],dp[j - k][t] + dp[t + 1][j] + dims[j - k].first * dims[t].second * dims[j].second);
            }
        }
    }
    return dp[0][n - 1];
}

long long helper(int i,  int j, vector<pair<int, int>>&dims, vector<vector<long long>>&dp){
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    else{
        long long curr = INT_MAX;
        for(int k = i; k < j; k++){
            curr = min(curr, helper(i, k, dims, dp) + helper(k + 1, j, dims, dp) + dims[i].first * dims[k].second * dims[j].second);
        }
        dp[i][j] = curr;
        return curr;
    }
}

int min_cost_top_down(vector<pair<int, int>>dims){
    int n = dims.size();
    vector<vector<long long>>dp(n, vector<long long>(n, -1));
    for(int i = 0; i < n; i++){
        dp[i][i] = 0;
    }
    return helper(0, n - 1, dims, dp);
}

int main()
{
    vector<pair<int, int>> dims = {{1, 2}, {2, 4}, {4, 6}};
    cout << min_cost(dims) << endl;
    cout << min_cost_top_down(dims);
}