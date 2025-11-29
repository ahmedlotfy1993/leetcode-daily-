        /*!
         * PROBLEM:
         * --------
         * Return the maximum subarray sum such that
         *      (subarray length) % k == 0.
         *
         * APPROACH:
         * ---------
         * Let prefix_sum[i] = sum(nums[0..i])   // size = n
         *
         * A subarray nums[l..r] has:
         *      sum = prefix_sum[r] - prefix_sum[l-1]
         *      length = (r - l + 1)
         *
         * Condition:
         *      (r - l + 1) % k == 0
         * ⇒    (r + 1) % k == l % k
         *
         * So we group prefix sums by index % k.
         *
         * For each r, find the smallest prefix_sum[l-1] that belongs to
         * the same bucket = (r + 1) % k.
         *
         * best[b] = smallest prefix_sum[x] seen so far with index_bucket = (x+1)%k
         *
         * TIME COMPLEXITY:  O(n)
         * SPACE COMPLEXITY: O(k)
         */
class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {

        int n = nums.size();

        // Build prefix sums of size n
        vector<long long> prefix_sum(n);
        prefix_sum[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefix_sum[i] = prefix_sum[i - 1] + nums[i];
        }

        vector<long long> best(k, LLONG_MAX);  
        long long ans = LLONG_MIN;

        // prefix_sum[-1] = 0 belongs to bucket 0
        best[0] = 0;

        for (int r = 0; r < n; r++) {

            int bucket = (r + 1) % k;

            // Case 1: Use best[bucket] to get valid subarray
            if (best[bucket] != LLONG_MAX) {
                ans = max(ans, prefix_sum[r] - best[bucket]);
            }

            // Update best for future subarrays
            best[bucket] = min(best[bucket], prefix_sum[r]);
        }

        return ans;
    }
};
