#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip> 

using namespace std;

void get_all_subsets_of_size_helper(int i, int curr_size, unsigned long &curr_mask, int k, int n, vector<unsigned long> &res)
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
		curr_mask = curr_mask + (1UL << (i - 1));
		get_all_subsets_of_size_helper(i + 1, curr_size + 1, curr_mask, k, n, res);
		curr_mask = curr_mask - (1UL << (i - 1));
	}
}

vector<unsigned long> get_all_masks_of_size(int k, int n)
{
	vector<unsigned long> res;
	int curr_size = 0;
	unsigned long curr_mask = 0;
	get_all_subsets_of_size_helper(1, curr_size, curr_mask, k, n, res);
	return res;
}

vector<unsigned long> get_all_masks_of_size_one_less(unsigned long masked_subset, int n)
{
	vector<unsigned long> res;
	for (int i = 1; i <= n; i++)
	{
		if (masked_subset & (1UL << (i - 1)))
		{
			res.push_back(masked_subset - (1UL << (i - 1)));
		}
	}
	return res;
}

double expected_optimal_reward_if_hit(unsigned long mask, int size_of_mask, unordered_map<unsigned long, double> &value, int n)
{
	auto masks_of_one_less = get_all_masks_of_size_one_less(mask, n);
	double res = 0;
	for (auto mask_of_one_less : masks_of_one_less)
	{
		res += value[mask_of_one_less];
	}
	res = res / (double)size_of_mask;
	return res;
}

double expected_optimal_reward_if_settle(unsigned long mask, int size_of_mask, int n)
{
	if (size_of_mask == n)
	{
		return 0;
	}
	double tot = (n * (n + 1)) / 2;
	for (int i = 1; i <= n; i++)
	{
		if (mask & (1UL << (i - 1)))
		{
			tot -= i;
		}
	}
	tot = tot / (double)(n - size_of_mask);
	return tot;
}

void generate_decision_table(int n, unordered_map<unsigned long, double> &value, unordered_map<unsigned long, bool> &decision)
{

	// precompute for subsets of size 1
	double baseline_average = (n + 1) / 2;
	for (double i = 1; i <= n; i++)
	{
		unsigned long masked_value = (1UL << (int)(i - 1));
		if (i > baseline_average)
		{
			decision[masked_value] = true;
			value[masked_value] = baseline_average;
		}
		else
		{
			decision[masked_value] = false;
			value[masked_value] = (((n * (n + 1) / 2.0)) - i) / (double)(n - 1);
		}
	}

	for (int k = 2; k <= n; k++)
	{
		auto masks = get_all_masks_of_size(k, n);
		for (auto mask : masks)
		{
			auto hit_reward = expected_optimal_reward_if_hit(mask, k, value, n);
			auto settle_reward = expected_optimal_reward_if_settle(mask, k, n);
			decision[mask] = hit_reward > settle_reward ? true : false;
			value[mask] = max(hit_reward, settle_reward);
		}
	}
}

double play_dp(int n, vector<int> deck)
{

	unordered_map<unsigned long, double> value;
	unordered_map<unsigned long, bool> decision;
	generate_decision_table(n, value, decision);

	unsigned long curr_remaining = (1UL << (n)) - 1;
	int i = 0;
	double reward = 0;
	while (i < n && decision[curr_remaining])
	{
		//cout << "hit : " << deck[i] << endl;
		reward += (double)deck[i];
		curr_remaining = curr_remaining - (1UL << (deck[i] - 1));
		i++;
	}
	reward /= (double)(i);
	// cout << "-------" << "\nreward: " << reward << endl;
	return reward;
}

double play_baseline(int n, vector<int> deck)
{
	double curr_sum = 0;
	double curr_reward = 0;
	double baseline = (n + 1) / (2.0);
	int i = 0;
	while (i < n)
	{
		if (curr_reward >= baseline)
		{
			break;
		}
		else
		{
			//cout << "hit : " << deck[i] << endl;
			curr_sum += deck[i];
			curr_reward = curr_sum / (double)(i + 1);
			i++;
		}
	}
	return curr_reward;
}

vector<vector<int>> get_all_permutations(int n) {
    // 1. Initialize the starting sequence: {1, 2, ..., n}
    vector<int> current_deck(n);
    // std::iota fills the vector with sequential values starting from 1.
    iota(current_deck.begin(), current_deck.end(), 1);

    // This vector will store all the generated permutations.
    vector<vector<int>> all_permutations;

    // 2. Use std::next_permutation to generate subsequent permutations
    // The loop continues until std::next_permutation returns false, 
    // indicating that the sequence is in the final (descending) order.
    // NOTE: The initial, ascending sequence is added before the loop starts.
    do {
        // Add the current state of the deck (a permutation) to the result list.
        all_permutations.push_back(current_deck);
        
    } while (next_permutation(current_deck.begin(), current_deck.end()));

    return all_permutations;
}

void stress_test_driver() {
    cout << "N\tTime(s)\tStates(2^N)\tEst. RAM(Map)" << endl;
    cout << "------------------------------------------------" << endl;

    for (int n = 1; n <= 32; n++) { // 32 is typically the theoretical limit for 'unsigned long' masks
        auto start = chrono::high_resolution_clock::now();

        try {
            unordered_map<unsigned long, double> value;
            unordered_map<unsigned long, bool> decision;
            
            // Only call the generation logic, don't play the game
            generate_decision_table(n, value, decision);

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            
            // Rough estimation of map overhead: ~64 bytes per entry
            double est_mem_gb = (pow(2, n) * 64) / (1024.0 * 1024.0 * 1024.0);
            
            cout << n << "\t" 
                 << fixed << setprecision(4) << diff.count() << "\t" 
                 << (1UL << n) << "\t\t" 
                 << setprecision(2) << est_mem_gb << " GB" << endl;

        } catch (const std::bad_alloc& e) {
            cout << "\n[CRASH] Memory limit reached at N=" << n << " (std::bad_alloc)" << endl;
            break;
        }
    }
}

int main() {
    stress_test_driver();
    return 0;
}