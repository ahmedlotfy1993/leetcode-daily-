/*
    Problem Summary:
    ----------------
    Given a binary string s, count the number of substrings that consist entirely of '1's.
    Return the answer modulo 1e9 + 7.

    Observation:
    ------------
    • Consecutive '1's form segments. For a segment of length L, the number of substrings
      that can be formed entirely of '1's is sum(1..L) = L*(L+1)/2.

    • We just iterate through the string, count consecutive '1's, and accumulate the
      counts modulo 1e9 + 7.

    Time Complexity:
    ----------------
    O(n), where n = s.size().
    • Each character is processed exactly once.

    Space Complexity:
    -----------------
    O(1) extra space.

*/

class Solution {
    static const int MOD = 1e9 + 7;
public:
    int numSub(string s) {
        int i = 0;
        int n = s.size();
        long long ans = 0;  // Use long long to avoid intermediate overflow

        while (i < n) {
            if (s[i] == '1') {
                int j = i;
                while (j < n && s[j] == '1') j++;  // find consecutive '1's segment

                long long len = j - i;
                ans = (ans + (len * (len + 1) / 2) % MOD) % MOD;  // sum of 1..len

                i = j;
            } else {
                i++;
            }
        }

        return (int)ans;
    }
};
