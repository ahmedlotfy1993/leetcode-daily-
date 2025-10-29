/*
Problem:
--------
You are given a positive number `n`.

Return the smallest number `x` such that:
    - x >= n
    - The binary representation of x contains only '1's.

Observation:
------------
Numbers whose binary representation consists only of '1's are of the form:
    1, 3, 7, 15, 31, 63, ... (i.e., 2^k - 1)

Approach:
---------
1. Start with x = 1.
2. Shift x left (multiply by 2) until x > n.
3. Return (x - 1), which yields a number like:
       1     -> 1   (binary: 1)
       3     -> 11
       7     -> 111
       15    -> 1111
   All bits become '1'.

Time Complexity:  O(log n)
Space Complexity: O(1)
*/

class Solution {
public:
    int smallestNumber(int n) {
        int x = 1;
        while(x <= n) x = x << 1;
        return x - 1;
    }
};
