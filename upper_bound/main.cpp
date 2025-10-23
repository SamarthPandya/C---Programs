#include <iostream>

using namespace std;

/*
Given a sorted array and int k, we find the minimum integer in the array that is greater than
or equal to k
*/

int upper_bound(vector<int>arr, int k){
    int l = 0, r = arr.size();
    while(l < r){
        int mid = l + (r - l) / 2;
        if(arr[mid] < k){
            l = mid + 1;
        }
        else{
            r = mid;
        }
        cout << l << '-' << r << endl;
    }
    return r;
}

int main(){
    vector<int>arr = {1, 2, 4, 5, 6};
    cout << upper_bound(arr, 7);
}

