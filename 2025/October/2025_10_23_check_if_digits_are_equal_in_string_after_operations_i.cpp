/*
Problem:
--------
You are given a string `s` consisting of digits.  
Perform the following operation repeatedly until the string has exactly two digits:

    - For each pair of consecutive digits in `s`, starting from the first digit, 
      calculate a new digit as the sum of the two digits modulo 10.
    - Replace `s` with the sequence of newly calculated digits, maintaining the same order.

Return `true` if the final two digits in `s` are the same; otherwise, return `false`.


Solution:
---------
We simulate the process step by step:

1. As long as the string length `n > 2`, we:
   - Create a new string `result`.
   - For each consecutive pair `(s[i], s[i+1])`, compute:
        new_digit = ( (s[i] - '0') + (s[i+1] - '0') ) % 10
   - Append this new digit (as a character) to `result`.

2. Replace `s` with `result` and continue until its size becomes 2.

3. Finally, compare the two digits — return `true` if they are equal.

Underlying Technique:
---------------------
Iterative string transformation using pairwise modulo addition.

Complexity Analysis:
--------------------
Let `n` be the initial length of the string.

Time Complexity: O(n²)
    - Each iteration reduces the string length by 1, and each iteration processes O(n) elements.

Space Complexity: O(n)
    - For temporary storage of intermediate strings.


Code:
-----
*/
class Solution {
public:
    bool hasSameDigits(string s) {
        int n = s.size();
        while (n > 2) {
            string result;
            for (int i = 0; i < n - 1; i++) {
                char num = ((s[i] - '0' + s[i + 1] - '0') % 10) + '0';
                result.push_back(num);
            }
            s = result;
            n = s.size();
        }
        return s[0] == s[1];
    }
};
