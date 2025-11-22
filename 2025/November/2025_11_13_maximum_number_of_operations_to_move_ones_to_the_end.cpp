/*
    Problem Summary:
    ----------------
    You are given a binary string `s`. You may repeatedly perform the following operation:

      • Choose an index i such that:
            s[i]   == '1'
            s[i+1] == '0'
      • Move this '1' to the right until it either:
            - reaches the end of the string, OR
            - bumps into another '1'

    The effect of an operation:
        A '10' pattern becomes '01', potentially sliding the '1' over a run of zeros.

    The task:
        Return the maximum number of operations that can be performed.

    Key Insight:
    ------------
    A "10" transition means that every zero segment to the right absorbs all previously seen '1's.
    
    Let:
        countOne = number of '1's seen so far (left → right)
        When we encounter a block of zeros, each zero-block enables `countOne` operations.
        This is because each preceding '1' can be paired with that zero-block in an operation.

    Example:
        s =  1 0 0 1 0
             ↑   ↑
        When scanning the zero-block "00", all earlier 1's contribute operations.

    Algorithm:
    ----------
    • Scan the string from left to right.
    • Count '1's.
    • Each time you hit a block of '0's, add countOne to the answer.
    • Continue.

    Time Complexity:  O(n)
        Single pass over the string.

    Space Complexity: O(1)
        Only counters are used.
*/

class Solution {
public:
    int maxOperations(string s) {
        int countOne = 0;
        int ans = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '0') {
                // Skip consecutive zeros as a single block
                while ((i + 1) < s.length() && s[i + 1] == '0') {
                    i++;
                }
                // Each prior '1' contributes one operation
                ans += countOne;
            } else {
                countOne++;
            }
        }
        return ans;
    }
};
