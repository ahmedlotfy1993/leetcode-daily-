/*
Problem:
---------
Given an integer n, determine whether it is a power of four.

Definition:
-----------
An integer is a power of four if there exists an integer x such that:
    n == 4^x
*/
/*
Bitwise Approach:
-----------------
1. A number is a power of four if:
   - It is greater than 0.
   - It is a power of two (i.e., it has exactly one bit set in its binary representation).
   - Its single set bit is located at an even-numbered bit position (0-based index).

2. Check if it's a power of two using:
   (n & (n - 1)) == 0

3. To ensure the set bit is in the correct position for powers of 4, we use:
   (n & 0x55555555) != 0
   This hexadecimal mask has 1s in all even positions (binary: 0101...).

Advantages:
-----------
- Time Complexity: O(1) (constant time)
- Space Complexity: O(1) (no extra memory)

*/
class Solution {
public:
    bool isPowerOfFour(int n) {
        return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555);   
    }
};
