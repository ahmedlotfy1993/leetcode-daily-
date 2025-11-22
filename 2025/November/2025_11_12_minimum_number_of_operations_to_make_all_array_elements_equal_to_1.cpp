/*
    Problem Summary:
    You are given a 0-indexed array `nums` of positive integers.
    You can repeatedly pick an index i and replace nums[i] or nums[i+1] with gcd(nums[i], nums[i+1]).
    The goal is to make all elements equal to 1 using the minimum number of operations.
    If impossible, return -1.

    Key Observations:
    1. If the array contains at least one `1`, the answer is:
           (n - count(1))
       Because each non-1 element can be turned into 1 by pairing it with an existing 1 (cost = 1 per element).

    2. If the gcd of the entire array > 1:
           Impossible → return -1.
       Because gcd shrinking operations can never create a 1.

    3. Otherwise:
       We need to find the shortest subarray whose gcd becomes 1.
       Suppose the shortest such subarray has length L.
       Turning this window into a single `1` costs:
            (L - 1) operations
       Then turning the rest of the array into 1 costs:
            (n - 1) extra operations
       Total = (L - 1) + (n - 1) = n + L - 2.

       The code computes L as the minimum window where gcd(...) = 1.

    Time Complexity:
        Worst case O(n^2 * logA)
        - We attempt gcd on all subarrays (n^2)
        - Each gcd is log(max(nums[i]))

    Space Complexity:
        O(1)
*/

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int num1 = 0;
        int g = 0;

        // Count existing ones, and compute total gcd
        for (int x : nums) {
            if (x == 1) num1++;
            g = gcd(g, x);
        }

        // Case 1: Already have some 1's
        if (num1 > 0) {
            return n - num1;
        }

        // Case 2: Impossible if overall gcd > 1
        if (g > 1) {
            return -1;
        }

        // Case 3: Find shortest subarray with gcd = 1
        int min_len = n;
        for (int i = 0; i < n; i++) {
            int g = 0;
            for (int j = i; j < n; j++) {
                g = gcd(g, nums[j]);
                if (g == 1) {
                    min_len = min(min_len, j - i + 1);
                    break;
                }
            }
        }

        // Transform window to a single 1, then fill the rest
        return min_len + n - 2;
    }
};
