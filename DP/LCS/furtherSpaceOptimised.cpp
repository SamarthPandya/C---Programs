#include <iostream>
#include <vector>

using namespace std;

/*
now that we are able to calculate lcs using 2 * min(m, n) + o(1) space, let us do so using only
min(m, n) + o(1) space.

In the "two-row" design of of the previous algorithm, we can optimise it by overwriting r0 itself, but
we need keep track of the r0[j - 1] and r0[j] which would be used in calculating r1[j]
*/

int optimised_lcs(string a, string b){
    int n = a.size();
    int flag = 0, prev, curr;
    vector<int>r0(n, -1);
    
    
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

        r0[0] = flag;
        int ans;
        
        prev = r0[0], curr = r0[1];
        for(int j = 1; j < n; j++){
            if(b[r] == a[j]){
                ans = 1 + r0[j - 1];
            }
            else{
                ans = max(prev, curr);
            }

            // save prev and curr before they get overwritten
            prev = r0[j];
            curr = r0[j + 1];

            // overwrite
            r0[j] = ans;
        }
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
    string a = "acbcas", b = "axxbas";
    cout << lcs(a, b);
}