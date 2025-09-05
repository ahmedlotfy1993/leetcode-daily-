/*
Problem:
--------
We are given two integers: num1 and num2.

Operation rule:
- In one operation, choose an integer i ∈ [0, 60].
- Subtract (2^i + num2) from num1.

Goal:
- Find the minimum number of operations to make num1 exactly 0.
- If it’s impossible, return -1.

--------------------------------------------------
Key Insight:
------------
Each operation always subtracts `num2` plus some power of two (2^i).
So after `k` operations:
    num1 - k*num2 = sum of k powers of two
That means:
- Remaining = num1 - k*num2 must be non-negative.
- Remaining must be representable as a sum of exactly `k` powers of two.

--------------------------------------------------
*/

/*
Approach:
---------
1. Iterate over possible number of operations (k = 1 to 60).
   (60 is enough since 2^60 > 1e18, covers any reasonable input range).
2. Compute:
   remaining = num1 - k*num2
   - If remaining < 0 → not possible, stop further search.
3. Compute:
   minPowersOfTwo = popcount(remaining)  
   (the minimum number of powers of two required to represent `remaining`).
4. Validity conditions:
   - remaining >= k → enough value to split into k terms.
   - minPowersOfTwo <= k → possible to split into exactly k terms.
5. Return the first valid k (minimum operations).
6. If no valid k found → return -1.

--------------------------------------------------
Complexity:
-----------
- Time: O(60) = O(1) → since we only check up to 60 operations.
- Space: O(1).

--------------------------------------------------
*/

class Solution {
public:
    int makeTheIntegerZero(int num1, int num2) {
        for (int operations = 1; operations <= 60; operations++) {
            long long remaining = num1 - (operations * (long long)num2);

            if (remaining < 0) return -1;  // cannot reduce below zero

            int minPowersOfTwo = popcount((unsigned long long)remaining);

            if (remaining >= operations && minPowersOfTwo <= operations)
                return operations;  // found the minimum number of operations
        }
        return -1;  // not possible at all
    }
};
