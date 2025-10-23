#include <iostream>

using namespace std;

/*

Problem: https://takeuforward.org/data-structure/dynamic-programming-ninjas-training-dp-7/

Solution
--------

We maintain a 2D memo of dimension n * 3

dp[i][t] represents the max points achievable by ending the training at day i with activity t where,
0 <= t < 3 and 0 <= i < n

Base Cases
----------
dp[0] = max(points[0][0], points[0][1], points[0][2])

End state
---------
We take maximum of dp[n - 1][0], dp[n - 1][1], dp[n - 1][2] and return the answer

Recursion
---------
dp[i][t] = points[i][t] + max({dp[i - 1][l] | l != t && 0 <= l < 3}) 

*/

int maxMerits(vector<vector<int>>points){
    int n = points.size();
    vector<int>prevDay = points[0];
    for(int i = 1; i < n; i++){
        vector<int>temp(3);
        temp[0] = points[i][0] + max(prevDay[1], prevDay[2]);
        temp[1] = points[i][1] + max(prevDay[0], prevDay[2]);
        temp[2] = points[i][2] + max(prevDay[0], prevDay[1]);
        prevDay = temp;
    }
    return max(max(prevDay[0], prevDay[1]), prevDay[2]);
}

int main(){
    return 0;
}