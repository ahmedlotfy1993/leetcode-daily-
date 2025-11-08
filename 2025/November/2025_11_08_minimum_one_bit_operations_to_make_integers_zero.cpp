/*
---------------------------------------------------------------------------------------
PROBLEM STATEMENT:

Given an integer n, you must transform it into 0 using the following operations:

1. Change (flip) the rightmost bit (0th bit).
2. Change (flip) bit i if:
      - bit (i - 1) == 1
      - and bits (i - 2) to bit 0 are all 0

Return the **minimum number of operations** required to transform n into 0.

---------------------------------------------------------------------------------------
INSIGHT / OBSERVATION:

This problem maps to the *binary Gray code* transformation pattern.

A known property:
    The minimum operations to reduce `n` to zero equals the XOR of progressively
    right-shifted values of n:

        operations = n ^ (n >> 1) ^ (n >> 2) ^ ... until n becomes 0

Which can be computed iteratively:
    while (n > 0):
        operations ^= n
        n >>= 1

---------------------------------------------------------------------------------------
TIME & SPACE COMPLEXITY:

Time Complexity:   O(log n)       -- one iteration per bit
Space Complexity:  O(1)           -- constant extra space

---------------------------------------------------------------------------------------
*/

class Solution {
public:
    int minimumOneBitOperations(int n) {
        int operations = 0;

        // XOR all progressively right-shifted values
        while (n > 0) {
            operations ^= n;
            n >>= 1;
        }

        return operations;
    }
};
