#include <iostream>

using namespace std;

/*
Problem: https://www.naukri.com/code360/problems/ninja-and-his-friends_3125885?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=0

Solution
--------

State space
-----------
S = {(k, j1, j2) | 0 <= k < r, 0 <= r1 < c, 0 <= r2 < c}
s(k, j1, j2) describes the maximum points achievable when:
alice is at (k, j1)
bob is at (k, j2)

Base state: (0, 0, c-1) = grid[0][0] + grid[0][c-1]

End state: we need maximum of all values from dp[r-1][i][j] where i and j range freely

Recursion
---------
too long to write here see the code
*/

bool isValid(int i, int j, int c){
    return i >= 0 && i < c && j >= 0 && j < c;
}
int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    vector<int>dirs{-1, 0, 1};
    vector<vector<vector<int>>>dp(r, vector<vector<int>>(c, vector<int>(c, INT_MIN)));
    dp[0][0][c-1] = grid[0][0] + grid[0][c-1];
    for(int k = 1; k < r; k++){
        for(int i = 0; i < c; i++){
            for(int j = 0; j < c; j++){

                //calculating dp[k][i][j]
                int curr = INT_MIN;
                for(int d1 : dirs){
                    for(int d2 : dirs){
                        int x = i + d1, y = j + d2;
                        if(isValid(x, y, c)){
                            curr = max(dp[k-1][x][y], curr);
                        }
                    }
                }

                if(curr != INT_MIN){
                    if(i != j){
                        dp[k][i][j] = curr + grid[k][i] + grid[k][j];
                    }
                    else {
                        dp[k][i][j] = curr + grid[k][i];
                    }
                }

            }
        }
    }
    int res = INT_MIN;
    for(int i = 0; i < c; i++){
        for(int j = 0; j < c; j++){
            res = max(res, dp[r-1][i][j]);
        }
    }
    return res;
}