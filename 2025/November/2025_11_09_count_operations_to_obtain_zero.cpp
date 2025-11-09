/*
---------------------------------------------------------------------------------------------------
PROBLEM STATEMENT:

You are given two non-negative integers num1 and num2.

In one operation:
    - If num1 >= num2 → subtract num2 from num1
    - Else            → subtract num1 from num2

Example:
    num1 = 5, num2 = 4  →  num1 becomes 1 (because 5 - 4)
    num1 = 4, num2 = 5  →  num2 becomes 1 (because 5 - 4)

You must continue performing these operations until either num1 == 0 or num2 == 0.

Return the number of operations performed.

---------------------------------------------------------------------------------------------------
OBSERVATION:

This is equivalent to repeatedly applying the Euclidean algorithm (like GCD) but counting each
subtraction operation. However, instead of one subtraction at a time, we can perform:
    operations += larger / smaller
and reduce larger %= smaller to optimize,
but here we stick to the straightforward implementation.

---------------------------------------------------------------------------------------------------
TIME & SPACE COMPLEXITY:

Time Complexity:  O(max(num1, num2))     -- worst case subtracting 1 repeatedly
Space Complexity: O(1)                   -- constant memory

---------------------------------------------------------------------------------------------------
*/

class Solution {
public:
    int countOperations(int num1, int num2) {
        int ans = 0;

        while (num1 > 0 && num2 > 0) {
            if (num1 >= num2)
                num1 -= num2;
            else
                num2 -= num1;

            ans++;
        }

        return ans;
    }
};
