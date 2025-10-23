#include <iostream>

using namespace std;

bool isValid(int i, int j, int c){
    return i >= 0 && i < c && j >= 0 && j < c;
}
int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    vector<int>dirs{-1, 0, 1};
    vector<vector<vector<int>>>dp(r, vector<vector<int>>(c, vector<int>(c, INT_MIX)));
    dp[0][c-1][0] = grid[0][0] + grid[0][c-1];
    for(int k = 1; k < r; k++){
        for(int i = 0; i < c; i++){
            for(int j = 0; j < c; j++){

                //calculating dp[i][j][k]
                for(int d1 : dirs){
                    for(int d2 : dirs){
                        int x = i + d1, y = j + d2;
                        if(isValid(x, y, c)){
                            int curr = dp[x][y][k-1] == INT_MIX ? INT_MIX: dp[x][y][k-1] + grid[k-1][x] + grid[k-1][y];
                            dp[i][j][k] = max(dp[i][j][k], curr);
                        }
                    }
                }
            }
        }
    }
    int res = INT_MIN;
    for(int i = 0; i < c; i++){
        for(int j = 0; j < c; j++){
            res = max(res, dp[i][j][r-1]);
        }
    }
    return res;
}