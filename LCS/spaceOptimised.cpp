#include <iostream>
#include <vector>

using namespace std;

/*

Problem
-------
We have to solve the same problem using 2 * min(m, n) of space, given that m and are the lengths of
the strings under consideration.

Solution
--------
In the bottom up approach, if we have all values of row i and we have the value dp[i+1][0] then all values
of the row i + 1 can be computed. Once we have all values of row i + 1, we no longer need the values of row i,
this space can be used to store the values of row i + 2.

We compute all values of row i + 2 in a similar fashion and this way 
we get the final answer which would be the last element of the last row.

The trick here is choosing the shorter string to be indexed horizontally so that the row length remains
min(m, n).

The total space complexity becomes 2 * min(m, n) + o(1) where this o(1) corresponds to the flag variable
that we maintain to determine the value of the element dp[i + 1][0]
*/


int optimised_lcs(string a, string b){
    int n = a.size();
    int flag = 0;
    vector<int>r0(n, -1), r1(n, -1);
    
    
    for(int j = 0; j < n; j++){
        if(a[j] == b[0]){
            flag = 1;
        }
        r0[j] = flag;
    }


    for(int r = 1; r <= b.size() - 1; r++){
        if(b[r] == a[0]){
            flag = 1;
        }
        r1[0] = flag;
        for(int j = 1; j < n; j++){
            if(b[r] == a[j]){
                r1[j] = 1 + r0[j - 1];
            }
            else{
                r1[j] = max(r1[j - 1], r0[j]);
            }
        }
        r0 = r1;
        r1 = vector<int>(n, -1);
    }
    return r0.back();
}

/*
this wrapper retains the memory of which string is shorter and passes
the shorter string first. This avoids unnecessary if/else blocks in the orignal computation
*/
int lcs(string a, string b){
    if(a.size() > b.size()){
        return optimised_lcs(b, a);
    }
    else{
        return optimised_lcs(a, b);
    }
}

int main(){
    string a = "avdsaxf", b = "eadlxf";
    cout << lcs(a, b);
}