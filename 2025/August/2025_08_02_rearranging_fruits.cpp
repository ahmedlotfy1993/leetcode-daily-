/*
Problem:
--------
You are given two fruit baskets, each containing 'n' fruits. The cost of each fruit in the baskets is given by two integer arrays: `basket1` and `basket2`.

Your goal is to make both baskets equal (i.e., they contain the same multiset of fruit costs) using the minimum possible cost.

You are allowed to perform the following operation any number of times:
- Choose an index `i` in `basket1` and an index `j` in `basket2`, then swap the elements.
- The cost of each swap is `min(basket1[i], basket2[j])`.

Two baskets are considered equal when their contents, after sorting, are exactly the same.

Return the **minimum total cost** to make the baskets equal, or **-1** if it's impossible.
*/

/*
Approach:
---------
1. Frequency Counting:
   - Use an unordered_map<int, array<int, 2>> to count the frequency of each fruit cost in both baskets.
   - The first element in the array tracks frequency in `basket1`, the second in `basket2`.

2. Validity Check:
   - For each fruit cost, the sum of its frequency in both baskets must be even.
   - If any fruit appears an odd number of times overall, it's impossible to split it evenly — return -1.

3. Finding Swaps:
   - For each fruit cost, determine how many **extra copies** are in one of the baskets beyond half its total frequency.
   - These extras represent the fruits that must be swapped to the other basket.
   - Push these excess elements into a `swap_elements` vector.

4. Sorting and Cost Calculation:
   - Sort `swap_elements`.
   - Find the **minimum fruit cost** across both baskets.
   - For the first half of the `swap_elements`, calculate the minimum cost to swap:
     - Either **directly**, using the value itself.
     - Or **indirectly**, by doing two swaps with the minimum element (`2 * minElement`), which can be cheaper.

5. Sum up the swap costs for the required swaps (only half of the total extras need to be swapped).

Time Complexity:
----------------
- O(n + k log k), where `n` is the size of each basket and `k` is the number of excess elements.
- Efficient and handles large inputs well.
*/

class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        unordered_map<int, array<int, 2>>elements_frquency;
        int n = min(basket1.size(), basket2.size());
        for(int i = 0; i < n; i++){
            elements_frquency[basket1[i]][0]++;
            elements_frquency[basket2[i]][1]++;
        }

        vector<long long int>swap_elements;
        for(const auto& element_frquency: elements_frquency){
            int total_freq = element_frquency.second[0] + element_frquency.second[1];
            if (total_freq % 2) return -1; 
            int max_freq = max(element_frquency.second[0], element_frquency.second[1]);
            int extra = max_freq - total_freq / 2;
            fill_n(back_inserter(swap_elements), extra, element_frquency.first);
        }
        
        long long int minElement = min(*min_element(basket1.begin(), basket1.end()), *min_element(basket2.begin(), basket2.end()));
        sort(swap_elements.begin(), swap_elements.end());
        int extra_size = swap_elements.size();
        long long int result  = 0;
        for(int start_index = 0; start_index < extra_size / 2; start_index++){
            result += min(swap_elements[start_index], 2* minElement);
        }
        return result;
    }
};
