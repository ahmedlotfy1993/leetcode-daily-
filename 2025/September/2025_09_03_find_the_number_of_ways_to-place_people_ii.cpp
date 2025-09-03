/*
Problem:
--------
We are given n points on a 2D plane. We must place Alice and Bob on two distinct points such that:
1. Alice is the **upper-left corner** of the fence (xA <= xB, yA >= yB).
2. Bob is the **lower-right corner** of the fence.
3. No other person lies **inside or on the boundary** of the rectangle defined by Alice and Bob.

We want to count all such valid (Alice, Bob) pairs.
--------------------------------------------------
Example:
--------
points = [[0,2], [1,1], [2,0]]

Sorted → [[0,2], [1,1], [2,0]]

- Alice = (0,2):
   Bob = (1,1) → valid → res++
   Bob = (2,0) → blocked by y=1 → skip
- Alice = (1,1):
   Bob = (2,0) → valid → res++

Answer = 2
*/
/*
--------------------------------------------------
Optimized Approach:
-------------------
1. **Sorting the points**:
   - Sort points by x ascending.
   - If x is equal, sort by y descending.
   This ensures that:
     - When scanning from left to right, any Bob candidate will always have xBob >= xAlice.
     - The y ordering ensures we don’t overcount or miss cases when x’s are equal.

2. **Checking pairs**:
   - Fix Alice at point[i].
   - Track `lowestYSoFar` (initialized to -∞).
   - For each later point Bob = point[j], check:
       - yBob <= yAlice (Bob is below Alice).
       - yBob > lowestYSoFar (no intermediate point blocked the rectangle).
     If true → valid pair (Alice, Bob).
     Update `lowestYSoFar = yBob`.

3. **Result**:
   - Count of all valid (Alice, Bob) pairs.

--------------------------------------------------
Complexity:
-----------
- Sorting: O(n log n)
- Nested scan: O(n^2)
- Total: O(n^2), which is significantly faster than brute force O(n^3).
*/

class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](const auto &lhs, const auto &rhs) { 
            return lhs[0] == rhs[0] ? lhs[1] > rhs[1] : lhs[0] < rhs[0]; 
        });

        int validPairs = 0;
        int totalPoints = points.size();
        for (int i = 0; i < totalPoints; i++) {
            int aliceY = points[i][1];     
            int lowestYSoFar = INT_MIN; 
            for (int j = i + 1; j < totalPoints; j++) {
                int bobY = points[j][1];
                if (bobY <= aliceY && bobY > lowestYSoFar) {
                    lowestYSoFar = bobY;
                    validPairs++;
                }
            }
        }
        return validPairs;
    }
};
