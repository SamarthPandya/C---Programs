#include <iostream>

using namespace std;

/*
Problem: odeforces.com/blog/entry/63384

Solution
--------

*/

bool isPredecessor(string a, string b)
{
    int m = a.size(), n = b.size();
    if (m + 1 != n)
    {
        return false;
    }
    int i = 0;
    while (i < m && a[i] == b[i])
    {
        i++;
    }
    if (i == m)
    {
        return true;
    }
    else
    {
        while (i < m)
        {
            if (a[i] != b[i + 1])
            {
                return false;
            }
            i++;
        }
        return true;
    }
}

int longestStrChain(vector<string> &words)
{
    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
    });
    for(string word : words){
        cout << word << ' ';
    }
    cout << endl;
    int n = words.size();
    vector<int> dp(n, 1);
    int ans = 1;
    for (int i = 1; i < n; i++)
    {
        int res = 1;
        for (int j = 0; j < i; j++)
        {
            if (isPredecessor(words[j], words[i]))
            {
                res = max(res, 1 + dp[j]);
            }
        }
        dp[i] = res;
        ans = max(ans, res);
    }
    for(int i : dp){
        cout << i << ' ';
    }
    return ans;
}

int main()
{
    vector<string> words = {"xbc","pcxbcf","xb","cxbc","pcxbc"};
    longestStrChain(words);
}