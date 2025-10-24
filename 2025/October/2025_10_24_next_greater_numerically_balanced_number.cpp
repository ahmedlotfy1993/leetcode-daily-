/*
Problem:
--------
An integer x is **numerically balanced** if for every digit `d` in `x`, 
there are exactly `d` occurrences of that digit in `x`.

Given an integer `n`, return the **smallest numerically balanced number** 
that is **strictly greater than** `n`.

Example:
---------
Input: n = 1  
Output: 22  
Explanation:  
22 is numerically balanced because digit 2 appears exactly twice.

---

Solution:
---------
We precompute all numerically balanced numbers up to a reasonable limit 
and return the smallest one greater than `n`.

### Key Idea
Each balanced number can be constructed from a combination of digits 1–9,  
where digit `d` appears exactly `d` times.  
For example:
- `{(1,1)}` → `1`
- `{(2,2)}` → `22`
- `{(1,1),(2,2)}` → numbers like `122`, `212`, `221`, etc.

We:
1. Generate all valid combinations of `(digit, count=digit)` pairs.
2. Skip combinations whose total digit count ≥ 10 (since they exceed 9-digit numbers).
3. For each combination, generate **all permutations** and convert them to integers.
4. Insert each into a sorted set `balancedNumbers`.
5. Finally, use binary search (`lower_bound`) to find the smallest number > `n`.

---

Underlying Technique:
---------------------
- **Bitmask enumeration** → to select which digits to include (1–9).  
- **Backtracking with permutation generation** → to construct all possible numbers.  
- **Precomputation and lookup** → ensures fast query for any given `n`.

---

Complexity Analysis:
--------------------
Let `MAX_DIGITS_NUM = 9`.

- **Time Complexity:**  
  Generating all combinations via bitmask = O(2⁹).  
  For each combination, generating permutations is bounded and small since totalDigits < 10.  
  → Practically **O(1)** for all test cases (precomputation-based).

- **Space Complexity:**  
  O(M), where M is the number of balanced numbers generated (bounded constant).

---

Code:
-----
*/
class Solution {
    static constexpr int MAX_DIGITS_NUM = 9;
    using Foundation = vector<pair<int, int>>;

    void generateBalancedNumbers(set<int>& balancedNumbers, const Foundation& foundation) {
        vector<int> digits;
        for (auto [digit, count] : foundation)
            for (int i = 0; i < count; ++i)
                digits.push_back(digit);

        sort(digits.begin(), digits.end());
        do {
            int num = 0;
            for (int d : digits) num = num * 10 + d;
            balancedNumbers.insert(num);
        } while (next_permutation(digits.begin(), digits.end()));
    }

public:
    int nextBeautifulNumber(int n) {
        set<int> balancedNumbers;

        int limit = 1 << MAX_DIGITS_NUM; 
        for (int mask = 1; mask < limit; ++mask) {
            Foundation foundation;
            int totalDigits = 0;

            for (int digit = 1; digit <= 9; ++digit) {
                if (mask & (1 << (digit - 1))) {
                    foundation.emplace_back(digit, digit);
                    totalDigits += digit;
                }
            }

            if (totalDigits < 10) 
                generateBalancedNumbers(balancedNumbers, foundation);
        }

        auto it = balancedNumbers.lower_bound(n + 1);
        return *it;
    }
};
