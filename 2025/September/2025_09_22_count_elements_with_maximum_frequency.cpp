/**
 * Problem:
 * --------
 * You are given an array `nums` consisting of positive integers.
 * Your task is to return the total frequencies of elements that have the maximum frequency.
 *
 * Example:
 * --------
 * Input:  nums = [1,2,2,3,1,4]
 * Step 1: Frequencies = {1:2, 2:2, 3:1, 4:1}
 * Step 2: Maximum frequency = 2
 * Step 3: Elements with max frequency = {1, 2}
 * Result = frequency(1) + frequency(2) = 2 + 2 = 4
 *
 * Goal:
 * -----
 * Count how many occurrences belong to elements that are tied for highest frequency.
 *
 * Approaches:
 * -----------
 * 1. USE_FIXED_SIZE_VECTOR (optimized for bounded input domain)
 *    - Use a fixed-size `vector<int>` of size 101 (since problem constraints guarantee nums[i] ≤ 100).
 *    - Provides O(1) indexing for counting frequencies.
 *
 * 2. USE_UNORDERED_MAP (generic approach)
 *    - Use `unordered_map<int,int>` to store element -> frequency mapping.
 *    - Works for arbitrary integer ranges but has slightly higher overhead due to hashing.
 *
 * Time Complexity:
 * ----------------
 * Both approaches:
 *   - Building frequency map: O(n)
 *   - Finding max frequency: O(k), where k = number of distinct elements
 *   - Counting total frequencies: O(k)
 * Overall: O(n + k) ≈ O(n)
 *
 * Space Complexity:
 * -----------------
 * - Vector-based: O(1) (fixed size, independent of input size)
 * - Map-based: O(k) (depends on number of distinct elements)
 *
 * Trade-off:
 * ----------
 * - Prefer vector-based solution when input domain is small and fixed (better performance).
 * - Use unordered_map when element range is unknown or very large.
 */

#define USE_FIXED_SIZE_VECTOR 1
#define USE_UNORDERED_MAP     0

class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
#if USE_FIXED_SIZE_VECTOR
        vector<int> num_to_freq(101, 0);
#endif
#if USE_UNORDERED_MAP
        unordered_map<int, int> num_to_freq;
#endif
        int max_freq = 0;
        for (auto num : nums) {
            num_to_freq[num]++;
            max_freq = max(max_freq, num_to_freq[num]);
        }
        int result = 0;

#if USE_FIXED_SIZE_VECTOR
        for (const auto& freq : num_to_freq) {
            if (max_freq == freq) result += freq;
        }
#endif
#if USE_UNORDERED_MAP
        for (const auto& [num, freq] : num_to_freq) {
            if (max_freq == freq) result += freq;
        }
#endif
        return result;
    }
};
