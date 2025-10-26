/*
Problem:
--------
Hercy wants to save money for his first car.  
He deposits money in the Leetcode bank according to the following rules:

- On the **first Monday**, he deposits $1.
- From **Tuesday to Sunday**, he deposits $1 more than the previous day.
- On every **subsequent Monday**, he deposits $1 more than the previous Monday’s amount.
  (and again increases daily by $1 through the week)

Given an integer `n`, return the total amount of money he will have after `n` days.

Example:
---------
Input: n = 10  
Output: 37  
Explanation:
- Week 1 deposits: 1, 2, 3, 4, 5, 6, 7 → sum = 28  
- Week 2 (3 days): 2, 3, 4 → sum = 9  
Total = 28 + 9 = 37

---

Approach (Simulation):
----------------------
We simulate the process week by week.

1. Maintain:
   - `weekStart`: amount to deposit on the first day (Monday) of the current week.
   - `money`: total money accumulated.
   - `day`: day counter.

2. For each week:
   - Deposit `weekStart + d` for each day `d` in `[0, 6]` (until n days are done).
   - After each week, increment `weekStart` by 1.

3. Stop when `day == n`.

---

Complexity Analysis:
--------------------
- **Time Complexity:** O(n)  
  We iterate through all days once.
- **Space Complexity:** O(1)  
  Only a few integer variables are used.

---

Code:
-----
*/
class Solution {
public:
    int totalMoney(int n) {
        int money = 0;
        int weekStart = 1;
        int day = 0;

        while (day < n) {
            for (int d = 0; d < 7 && day < n; ++d) {
                money += weekStart + d;
                ++day;
            }
            ++weekStart;
        }

        return money;
    }
};
