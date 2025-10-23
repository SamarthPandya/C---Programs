#include <iostream>

using namespace std;

int bottom_up_count_ways(vector<int>coins, int amount){
    /*This function count the number of diff combinations leading up to amount

    State space
    ----------
    S = {(i, j) | 0 <= i <= n, 0 <= j <= amount}
    s(i, j) represents number of ways to create j using the first i coins

    Base states: 
    - s(0, j) = 0 for j > 0 (we cannot make a non zero amount using no coins so 0 ways)
    - s(i, 0) = 1 for all i (wwe can always make 0 amount using any coins by taking none so 1 way)

    End state: s(n, amount)
    */
   int n = coins.size();
   vector<vector<long long>>dp(n + 1, vector<int>(amount + 1, 0));
   for(int i = 0; i <= n; i++){
    dp[i][0] = 1;
   }
   for(int j = 1; j <= amount; j++){
    dp[0][j] = 0;
   }
   for(int i = 1; i <= n; i++){
    int curr_coin = coins[i - 1];
    for(int j = 1; j <= amount; j++){
        long long ways_excluding = (long long)dp[i - 1][j];
        long long ways_including = (long long)0;
        if(curr_coin <= j){
            ways_including = (long long)dp[i][j - curr_coin];
        }
        dp[i][j] = ways_excluding + ways_including;
    }
   }
   return dp[n][amount];
}

int main(){
    vector<int>coins = {1, 2, 5};
    cout << bottom_up_count_ways(coins, 5);
}