/***************************************************************************************************
💠 Problem: Magical Sum (LeetCode-style)
----------------------------------------------------------------------------------------------------
You are given two integers, m and k, and an integer array nums.

A sequence of integers `seq` is called **magical** if:
    • seq has a size of m.
    • 0 <= seq[i] < nums.length
    • The binary representation of 2^seq[0] + 2^seq[1] + ... + 2^seq[m - 1] has exactly k set bits.

The **array product** of this sequence is defined as:
    prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]]).

You need to return the **sum of array products** for all valid magical sequences.

Since the answer may be large, return it modulo (10^9 + 7).

A set bit refers to a bit in the binary representation of a number that has a value of 1.

----------------------------------------------------------------------------------------------------
🔹 Example:
Input:
    m = 2, k = 1, nums = [2, 3]
Output:
    13

Explanation:
    Possible sequences of indices of size 2:
        [0, 0] → sum = 2^0 + 2^0 = 2 → binary 10 → 1 set bit ✅ → product = 2*2 = 4
        [0, 1] → sum = 2^0 + 2^1 = 3 → binary 11 → 2 set bits ❌
        [1, 0] → sum = 2^1 + 2^0 = 3 → binary 11 → 2 set bits ❌
        [1, 1] → sum = 2^1 + 2^1 = 4 → binary 100 → 1 set bit ✅ → product = 3*3 = 9
    Result = (4 + 9) % (1e9+7) = 13

----------------------------------------------------------------------------------------------------
💡 Approach (Brute Force + Backtracking):
    1️⃣ Generate all possible sequences `seq` of length m.
    2️⃣ For each sequence:
         - Compute S = sum of (2^seq[i]) for all i.
         - Compute product = product of nums[seq[i]] (mod 1e9+7).
    3️⃣ If the number of set bits in S equals k → add product to result.
    4️⃣ Return total sum % (1e9+7).

We use recursion/backtracking to build all possible sequences.
At each recursive call, we choose one index (0 to n-1) and go deeper until we form a sequence of size m.

----------------------------------------------------------------------------------------------------
⏱️ Time Complexity:
    O(n^m)
    - For each of the m positions, we can pick any of n indices.
    - Each generated sequence requires O(m) work to compute sum and product.

🧠 Space Complexity:
    O(m)
    - Depth of recursion stack and sequence vector.

----------------------------------------------------------------------------------------------------
⚙️ Optimization Note:
    - For small n, m, this brute-force approach works fine.
    - For larger constraints, we can use **dynamic programming** with bitmask states
      or precompute contributions grouped by popcount.

----------------------------------------------------------------------------------------------------
✅ Implementation:
***************************************************************************************************/
class Solution {
    static constexpr int MOD = 1e9 + 7;
public:
    int magicalSum(int m, int k, vector<int>& nums) {
        vector<int> seq;
        int result = 0;
        int n = nums.size();
        vector<long long> pow2(n);
        for (int i = 0; i < n; ++i)
            pow2[i] = (1LL << i); // Precompute powers of 2

        function<void(int)> generate = [&](int depth) {
            if (depth == m) {
                long long S = 0, prod = 1;
                for (int idx : seq) {
                    S += pow2[idx];
                    prod = (prod * nums[idx]) % MOD;
                }
                if (__builtin_popcountll(S) == k)
                    result = (result + prod) % MOD;
                return;
            }

            for (int i = 0; i < n; ++i) {
                seq.push_back(i);
                generate(depth + 1);
                seq.pop_back();
            }
        };

        generate(0);
        return result;
    }
};
