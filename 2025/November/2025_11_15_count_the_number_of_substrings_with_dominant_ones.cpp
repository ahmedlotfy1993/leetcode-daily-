/*
    Problem Summary:
    ----------------
    You are given a binary string s (consisting of '0' and '1').
    Count the number of substrings where:

        (# of ones)  >=  (# of zeros)^2

    Such a substring is called "dominant in ones".

    Constraints make the classic O(n^2) brute force too slow.
    We need an optimized counting strategy.


    Core Insight:
    -------------
    Let zeros = z, ones = o.
    Condition:     o >= z^2

    For each right endpoint i, we try to find all valid substrings ending at i.

    Key trick:
      • Track nearest positions of previous zeros using an array `pre[]`
        where pre[i] gives the index of the previous '0' before (i - 1).

      • This enables jumping between zero positions instead of checking all substrings.

      • For a fixed right end i:
            z = number of zeros in substring
            We find ranges of j (left endpoints) where the condition holds.

        This reduces the inner loop to run only O(sqrt(n)) times because
        if z grows too large, z^2 > n → impossible.


    Time Complexity:
    ----------------
    Let n = length of string.

      • Building `pre` array: O(n)
      • Outer loop over i: O(n)
      • Inner while-loop jumps between zero positions.
        z*z <= n  → z <= sqrt(n)
      → Each i repeats ≤ sqrt(n) iterations.

    Total: O(n * sqrt(n))

    Space Complexity:
        O(n) for the `pre` array.


    Notes:
    ------
    This is the official intended optimized solution using square-root bounding
    on zero count + prefix “previous-zero” jumps.

*/

class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();

        // pre[i] = index of most recent zero before position i-1
        vector<int> pre(n + 1);
        pre[0] = -1;

        for (int i = 0; i < n; i++) {
            if (i == 0 || s[i - 1] == '0')
                pre[i + 1] = i;
            else
                pre[i + 1] = pre[i];
        }

        long long res = 0;

        // iterate over all right-end positions i
        for (int i = 1; i <= n; i++) {
            int cnt0 = (s[i - 1] == '0');
            int j = i;

            while (j > 0 && cnt0 * cnt0 <= n) {
                int cnt1 = (i - pre[j]) - cnt0;
                if (cnt0 * cnt0 <= cnt1) {
                    res += min(j - pre[j], cnt1 - cnt0 * cnt0 + 1);
                }
                j = pre[j];
                cnt0++;
            }
        }

        return res;
    }
};
