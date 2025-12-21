#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <unordered_map>
#include <cmath>

using namespace std;

// ============== GOSPER'S HACK VERSION ==============
void GospersHack(int k, int n, vector<unsigned long>&res)
{
    unsigned long set = (1 << k) - 1;
    unsigned limit = (1 << n);
    while (set < limit)
    {
        res.push_back(set);
        unsigned long c = set & - set;
        unsigned long r = set + c;
        set = (((r ^ set) >> 2) / c) | r;
    }
}

vector<unsigned long> get_all_masks_of_size_gosper(int k, int n)
{
    vector<unsigned long> res;
    GospersHack(k, n, res);
    return res;
}

vector<unsigned long> get_all_masks_of_size_one_less_gosper(unsigned long masked_subset, int n)
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

double expected_optimal_reward_if_hit_gosper(unsigned long mask, int size_of_mask, vector<double> &value, int n)
{
    auto masks_of_one_less = get_all_masks_of_size_one_less_gosper(mask, n);
    double res = 0;
    for (auto mask_of_one_less : masks_of_one_less)
    {
        res += value[mask_of_one_less];
    }
    res = res / (double)size_of_mask;
    return res;
}

double expected_optimal_reward_if_settle_gosper(unsigned long mask, int size_of_mask, int n)
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

void generate_decision_table_gosper(int n, vector<double> &value, vector<bool> &decision)
{
    double baseline_average = (n + 1) / 2.0;
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
        auto masks = get_all_masks_of_size_gosper(k, n);
        for (auto mask : masks)
        {
            auto hit_reward = expected_optimal_reward_if_hit_gosper(mask, k, value, n);
            auto settle_reward = expected_optimal_reward_if_settle_gosper(mask, k, n);
            decision[mask] = hit_reward > settle_reward ? true : false;
            value[mask] = max(hit_reward, settle_reward);
        }
    }
}

double play_dp_gosper(int n, vector<int> deck)
{
    unsigned long size = (1UL << (n)) + 1;
    vector<double> value(size);
    vector<bool> decision(size);
    generate_decision_table_gosper(n, value, decision);

    unsigned long curr_remaining = (1UL << (n)) - 1;
    int i = 0;
    double reward = 0;
    while (i < n && decision[curr_remaining])
    {
        reward += (double)deck[i];
        curr_remaining = curr_remaining - (1UL << (deck[i] - 1));
        i++;
    }
    if (i > 0) reward /= (double)(i);
    return reward;
}

// ============== RECURSIVE VERSION ==============
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

vector<unsigned long> get_all_masks_of_size_recursive(int k, int n)
{
    vector<unsigned long> res;
    int curr_size = 0;
    unsigned long curr_mask = 0;
    get_all_subsets_of_size_helper(1, curr_size, curr_mask, k, n, res);
    return res;
}

vector<unsigned long> get_all_masks_of_size_one_less_recursive(unsigned long masked_subset, int n)
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

double expected_optimal_reward_if_hit_recursive(unsigned long mask, int size_of_mask, unordered_map<unsigned long, double> &value, int n)
{
    auto masks_of_one_less = get_all_masks_of_size_one_less_recursive(mask, n);
    double res = 0;
    for (auto mask_of_one_less : masks_of_one_less)
    {
        res += value[mask_of_one_less];
    }
    res = res / (double)size_of_mask;
    return res;
}

double expected_optimal_reward_if_settle_recursive(unsigned long mask, int size_of_mask, int n)
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

void generate_decision_table_recursive(int n, unordered_map<unsigned long, double> &value, unordered_map<unsigned long, bool> &decision)
{
    double baseline_average = (n + 1) / 2.0;
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
        auto masks = get_all_masks_of_size_recursive(k, n);
        for (auto mask : masks)
        {
            auto hit_reward = expected_optimal_reward_if_hit_recursive(mask, k, value, n);
            auto settle_reward = expected_optimal_reward_if_settle_recursive(mask, k, n);
            decision[mask] = hit_reward > settle_reward ? true : false;
            value[mask] = max(hit_reward, settle_reward);
        }
    }
}

double play_dp_recursive(int n, vector<int> deck)
{
    unordered_map<unsigned long, double> value;
    unordered_map<unsigned long, bool> decision;
    generate_decision_table_recursive(n, value, decision);

    unsigned long curr_remaining = (1UL << (n)) - 1;
    int i = 0;
    double reward = 0;
    while (i < n && decision[curr_remaining])
    {
        reward += (double)deck[i];
        curr_remaining = curr_remaining - (1UL << (deck[i] - 1));
        i++;
    }
    if (i > 0) reward /= (double)(i);
    return reward;
}

// ============== PERFORMANCE COMPARISON ==============
struct PerformanceResult {
    double gosper_avg_reward;
    double recursive_avg_reward;
    double gosper_time_ms;
    double recursive_time_ms;
    long long permutation_count;
    double reward_difference;
    double speedup;
};

PerformanceResult compare_performance(int n) {
    vector<int> deck(n);
    iota(deck.begin(), deck.end(), 1);
    
    double gosper_total_reward = 0;
    double recursive_total_reward = 0;
    long long perm_count = 0;
    
    auto start_gosper = chrono::high_resolution_clock::now();
    do {
        gosper_total_reward += play_dp_gosper(n, deck);
        perm_count++;
    } while (next_permutation(deck.begin(), deck.end()));
    auto end_gosper = chrono::high_resolution_clock::now();
    
    // Reset deck for recursive version
    iota(deck.begin(), deck.end(), 1);
    
    auto start_recursive = chrono::high_resolution_clock::now();
    do {
        recursive_total_reward += play_dp_recursive(n, deck);
    } while (next_permutation(deck.begin(), deck.end()));
    auto end_recursive = chrono::high_resolution_clock::now();
    
    PerformanceResult result;
    result.permutation_count = perm_count;
    result.gosper_avg_reward = gosper_total_reward / perm_count;
    result.recursive_avg_reward = recursive_total_reward / perm_count;
    result.gosper_time_ms = chrono::duration<double, milli>(end_gosper - start_gosper).count();
    result.recursive_time_ms = chrono::duration<double, milli>(end_recursive - start_recursive).count();
    result.reward_difference = abs(result.gosper_avg_reward - result.recursive_avg_reward);
    result.speedup = result.recursive_time_ms / result.gosper_time_ms;
    
    return result;
}

int main()
{
    cout << fixed << setprecision(6);
    cout << "Performance Comparison: Gosper's Hack vs Recursive Approach\n";
    cout << "============================================================\n\n";
    
    cout << setw(4) << "n" 
         << setw(15) << "Perms" 
         << setw(15) << "Gosper(ms)"
         << setw(15) << "Recursive(ms)"
         << setw(12) << "Speedup"
         << setw(18) << "Gosper Reward"
         << setw(18) << "Recursive Reward"
         << setw(15) << "Reward Diff" << endl;
    cout << string(120, '-') << endl;
    
    for (int n = 10; n <= 25; n++) {
        if (n > 12) {
            cout << "\nNote: n > 12 may take significant time due to factorial growth.\n";
            cout << "Skipping n = " << n << " and above. Adjust if you have sufficient time.\n";
            break;
        }
        
        PerformanceResult result = compare_performance(n);
        
        cout << setw(4) << n 
             << setw(15) << result.permutation_count
             << setw(15) << result.gosper_time_ms
             << setw(15) << result.recursive_time_ms
             << setw(12) << result.speedup << "x"
             << setw(18) << result.gosper_avg_reward
             << setw(18) << result.recursive_avg_reward
             << setw(15) << result.reward_difference << endl;
    }
    
    return 0;
}
