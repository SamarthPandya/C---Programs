#include <iostream>

/*
This code calculates the actual optimal solution and not just the length

For every point where take 1 + f(i - 1, j - 1) it means we are going diagonally up left in the grid,
after including text1[i] or text2[j] (both are equal)
else if the max is f(i - 1, j) we are going up without finding an element
else: the max would be f(i, j - 1) so we go left
consider this notation:
d : diagonal up left
l: left
u: up
We maintain a grid of chars to save this info at each cell

We fill this grid with the rules above and then back track from the bottom right cell
to build the solution.
*/

using namespace std;

string lcs(string text1, string text2){
    int m = text1.size(), n = text2.size();
    vector<vector<pair<int, char>>>dp(m, vector<pair<int, char>>(n, {-1, ' '}));
    int flag = 0;
    for(int j = 0; j < n; j++){
        if(text1[0] == text2[j]){
            flag = 1;
            dp[0][j].second = 'd';
        }
        else{
            dp[0][j].second = 'l'; // always go left on the first row to hit a possible d
        }
        dp[0][j].first = flag;
    }
    flag = 0;
    for(int i = 1; i < m; i++){
        if(text1[i] == text2[0]){
            flag = 1;
            dp[i][0].second = 'd';
        }
        else{
            dp[i][0].second = 'u'; // always go up on the first col to hit a possible u
        }
        dp[i][0].first = flag;
    }

    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            if(text1[i] == text2[j]){
                dp[i][j] = {1 + dp[i - 1][j - 1].first, 'd'};
            }
            else{
                if(dp[i - 1][j].first > dp[i][j - 1].first){
                    dp[i][j] = {dp[i - 1][j].first, 'u'};
                }
                else{
                    dp[i][j] = {dp[i][j - 1].first, 'l'};
                }
            }
        }
    }


    // building the result
    string res;
    int i = m - 1, j = n - 1;
    while(i >= 0 && j >= 0){
        int dir = dp[i][j].second;
        if(dir == 'd'){
            res.insert(res.begin(), text1[i]);
            i--;
            j--;
        }
        else if(dir == 'u'){
            i--;
        }
        else if(dir == 'l'){
            j--;
        }
        else{
            break;
        }
    }
    return res;
}

int main(){
    string text1 = "asedasasadece", text2 = "aesdassadece";
    cout << lcs(text1, text2);
}
