/*
    Problem Summary:
    ----------------
    We seek the length of the smallest positive integer N such that:
        - N consists only of digit '1' (e.g., 1, 11, 111, 1111, ...)
        - N is divisible by k

    Observations:
    -------------
    - N can be extremely large (beyond 64-bit), so we must work with remainders.
    - Let rem be the remainder of the current repunit modulo k.
      Start with:
          rem = 1 % k   for "1"
      Next repunit:
          "11"    →  (rem * 10 + 1) % k
          "111"   →  (rem * 10 + 1) % k
          ...
    - If at any point rem == 0, the repunit is divisible by k.

    Detecting impossibility:
    ------------------------
    - There are at most k possible remainders (0 to k-1).
    - If we see the same remainder again, we are in a cycle → no solution.
      (This is detected using a set of visited remainders.)

    Special Case:
    -------------
    - If k is divisible by 2 or 5, no repunit is divisible by k.
      But the loop will naturally detect and return -1 via cycle detection.

    Time Complexity:
    ----------------
    O(k) — at most k different remainders.

    Space Complexity:
    -----------------
    O(k) for storing visited remainders.

*/

class Solution {
public:
    int smallestRepunitDivByK(int k) {
        int length = 1;
        int rem = 1 % k;
        unordered_set<int> seen; // stores visited remainders

        while (rem != 0 && seen.insert(rem).second) {
            length++;
            rem = (rem * 10 + 1) % k;
        }

        return (rem == 0) ? length : -1;
    }
};
