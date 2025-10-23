#include <vector>
#include <iostream>

using namespace std;

int helper(int i, int j, vector<vector<int>>&dp, vector<int>&a, vector<int>&b){
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    int ans;
    if(a[i] == b[j]){
        ans =  1 + helper(i - 1, j - 1, dp, a, b);
    }
    else{
        ans = max(helper(i, j - 1, dp, a, b), helper(i - 1, j, dp, a, b));
    }
    dp[i][j] = ans;
    return ans;
}

int lcs_top_down(vector<int>&a, vector<int>&b){
    vector<vector<int>>dp(a.size(), vector<int>(b.size(), -1));
    int flag = 0;
    for(int j = 0; j < b.size(); j++){
        flag = a[0] == b[j] ? 1 : 0;
        dp[0][j] = flag;
    }
    flag = 0;
    for(int i = 0; i < a.size(); i++){
        flag = b[0] == a[i] ? 1 : 0;
        dp[i][0] = flag;
    }
    return helper(a.size() - 1, b.size() - 1, dp, a, b);
}

int lcs_bottom_up(vector<int>&a, vector<int>&b){
    int m = a.size(), n = b.size();
    vector<vector<int>>dp(m, vector<int>(n, -1));
    int flag = 0;
    for(int j = 0; j < b.size(); j++){
        flag = a[0] == b[j] ? 1 : 0;
        dp[0][j] = flag;
    }
    flag = 0;
    for(int i = 0; i < a.size(); i++){
        flag = b[0] == a[i] ? 1 : 0;
        dp[i][0] = flag;
    }
    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            if(a[i] == b[j]){
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else{
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }
    vector<int>lcs;
    int i = m - 1, j = n - 1;
    while(i >= 0 && j >= 0){
        if(a[i] == b[j]){
            lcs.insert(lcs.begin(), a[i]);
            i--;
            j--;
        }
        else if(dp[i - 1][j] > dp[i][j - 1]){
            i--;
        }
        else{
            j--;
        }
    }
    cout << endl;
    for(int i : lcs){
        cout << i << ' ';
    }
    cout << endl;
    return dp.back().back();
}
int main(){
    vector<int>a = {1, 4, 3, 2}, b = {1, 2, 3, 1, 4, 3, 2};
    cout << lcs_top_down(a, b) << endl;
    cout << lcs_bottom_up(a, b);
}