#include <iostream>
#include <vector>

using namespace std;

void get_all_subsets_of_size_helper(int i, int curr_size, int &curr_mask, int &k, int &n, vector<int> &res)
{
	
	if (curr_size == k)
	{
		res.push_back(curr_mask);
		return;
	}

	if (i == n + 1)
	{
		return;
	}

	// exclude
	get_all_subsets_of_size_helper(i + 1, curr_size, curr_mask, k, n, res);

	// include
	if (curr_size + 1 <= k)
	{
		curr_mask = curr_mask + (1 << (i - 1));
		get_all_subsets_of_size_helper(i + 1, curr_size + 1, curr_mask, k, n, res);
		curr_mask = curr_mask - (1 << (i - 1));
	}
}

vector<int> get_all_masks_of_size(int k, int n)
{
	vector<int> res;
	int curr_size = 0;
	int curr_mask = 0;
	get_all_subsets_of_size_helper(1, curr_size, curr_mask, k, n, res);
	return res;
}

vector<int> get_all_subsets_of_size_one_less(int masked_subset, int n){
	vector<int>res;
	for(int i = 1; i <= n; i++){
		if(masked_subset & (1 << (i - 1))){
			res.push_back(masked_subset - (1 << (i - 1)));
		}
	}
	return res;
}

int main()
{
	vector<int>res = get_all_subsets_of_size_one_less(6, 3);
	for(int i : res){
		cout << i << endl;
	}
    return 0;
}