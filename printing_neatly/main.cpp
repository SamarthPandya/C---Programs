#include <iostream>
#include <vector>

using namespace std;

long long inf = numeric_limits<long long>::infinity();

/*

Problem
--------
Consider the problem of neatly printing a paragraph with a monospaced font (all
characters having the same width) on a printer. The input text is a sequence of n
words of lengths l1; l2; : : : ; ln, measured in characters. We want to print this para-
graph neatly on a number of lines that hold a maximum of M characters each. Our
criterion of “neatness” is as follows. If a given line contains words i through j,
where i j , and we leave exactly one space between words, the number of extra
space characters at the end of the line is M j Ci Pj
kDi lk, which must be
nonnegative so that the words fit on the line. We wish to minimize the sum, over
all lines except the last, of the cubes of the numbers of extra space characters at the
ends of lines. Give a dynamic-programming algorithm to print a paragraph of n
words neatly on a printer. Analyze the running time and space requirements of
your algorithm.

Solution
--------

State Space
------------
S = {i| 1 <= i <= n - 1}

where s(i) denotes the optimal way of printing li, l_(i + 1)....l_n

Base states: all k's where sum_{i = k}^{n}{l_(i)} + (n - k) < M

then dp[k] = 0

End state: s(1)

Recursion
_________

for k = n to 1
    ans = inf
    for j = 1 to n - k:
        cost = sum{i = 1}^{j}{l_{k + i}} + j - 1
        if cost < M and (M - cost)^3 + dp[k + j + 1] < ans
            ans = cost(M - cost)^3 + dp[k + j + 1]
    dp[k] = ans
*/

long long print_neatly(vector<int>lens, int M){
    int n = lens.size();
    vector<long long>dp(lens.size(), inf);
    for(int k = n - 1; k >= 0; k--){
        long long s = 0;
        for(int i = k; i <= n - 1; i++){
            s+=lens[i];
        }
        if(s + n - k <= M){
            dp[k] = 0;
        }
        else{
            long long ans = INT_MAX;
            for(int j = k; j <= n; j++){
                int cost = inf;
                for(int i = k; i <= j; i++){
                    cost += lens[i];
                }
                cost += j - k;
                if(cost <= M){
                    ans = min((long long)ans, (long long)pow(M- cost, 3) + dp[j + 1]);
                }
            }
            dp[k] = ans;
        }
    }
    for(auto l : dp){
        cout << l << ' ';
    }
    cout << endl;
    return dp[0];
}

int main(){
    vector<int>word_lens = {1, 4, 2, 3, 4, 1};
    int M = 6;
    cout << print_neatly(word_lens, M);
}