/********************************************************************************************
 * Problem:
 * You are given:
 *   - nums: an array of integers
 *   - k:   the subarray window size
 *   - x:   the number of "most frequent" elements to consider
 *
 * Definition of x-sum for a given array A:
 *   1. Count the frequency of every element in A.
 *   2. Keep only the top x most frequent elements.
 *      - If two elements have the same frequency, the one with the larger numeric value
 *        is considered more frequent.
 *   3. The x-sum = sum of (element_value * frequency) for those kept elements.
 *
 * For every subarray nums[i..i+k-1], compute and store its x-sum.
 *
 * Return:
 *   vector<int> answer of size (n - k + 1), where answer[i] is the x-sum of nums[i..i+k-1].
 *
 * -----------------------------------------------------------------------------------------
 * Approach:
 *  For every sliding window of size k:
 *      - Count element frequencies using unordered_map
 *      - Build a max-heap sorted by:
 *            (frequency DESC, element value DESC)
 *      - Extract the top x items and accumulate value * frequency
 *
 * -----------------------------------------------------------------------------------------
 * Time Complexity:
 *   O((n - k + 1) * (k + d * log d))
 *      - k to count frequency per window
 *      - d = number of distinct values in the window
 *      - log d due to priority_queue (max heap)
 *
 * Space Complexity:
 *   O(d) -- frequency hashmap + heap
 *
 ********************************************************************************************/

class Solution {
public:
    vector<int> findXSum(vector<int>& nums, int k, int x) {
        auto findXSumHelper = [&numsRef = nums, k, x](int start) -> int{
            unordered_map<int, int> numToFreq;
            priority_queue<pair<int, int>> mostFrequentElement;

            int ans = 0;
            int TopElementCounter = 0;

            for (int index = start; index < numsRef.size() && index < start + k; index++)
                numToFreq[numsRef[index]]++;

            for (const auto& [num, freq] : numToFreq)
                mostFrequentElement.emplace(freq, num);

            while (!mostFrequentElement.empty() && TopElementCounter < x) {
                auto topElement = mostFrequentElement.top();
                mostFrequentElement.pop();
                ans += topElement.second * topElement.first;
                TopElementCounter++;
            }
            return ans;
        };

        int n = nums.size();
        vector<int> result;

        for (int i = 0; i <= n - k; i++) {
            int sum = findXSumHelper(i);
            result.push_back(sum);
        }

        return result;
    }
};
