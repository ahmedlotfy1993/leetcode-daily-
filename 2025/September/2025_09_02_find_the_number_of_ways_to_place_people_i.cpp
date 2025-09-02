/*
Problem:
--------
We are given n points in 2D space, points[i] = [xi, yi].

We need to count the number of pairs of points (A, B) such that:
1. A is on the **upper-left** side of B, i.e.,
      Ax <= Bx  AND  Ay >= By
2. There is **no third point** C that lies inside or on the rectangle formed by A (top-left corner) and B (bottom-right corner).

Return the total count of such valid pairs (A, B).

------------------------------------------------
Example:
--------
points = [[0,2], [2,0], [1,1]]

- Pair (0,2) & (2,0) → rectangle includes (1,1), so invalid.
- Pair (0,2) & (1,1) → valid.
- Pair (1,1) & (2,0) → valid.

Answer = 2
*/
/*
------------------------------------------------
Approach (Brute Force with Validation):
---------------------------------------
1. Iterate over all pairs of points (i, j):
   - Treat point[i] as A (candidate top-left)
   - Treat point[j] as B (candidate bottom-right)
   - Check if A is upper-left of B:
        x1 <= x2  &&  y1 >= y2
   - If not, skip.

2. If A is upper-left of B:
   - Iterate over all other points k:
       - Check if point[k] lies inside the rectangle (inclusive) defined by A and B:
         x1 <= x3 <= x2  &&  y2 <= y3 <= y1
       - If yes, then pair (A, B) is invalid → break.

3. If no blocking point is found → count (A, B) as a valid pair.

4. Return the count.

------------------------------------------------
Complexity:
-----------
- Outer loops over all pairs: O(n^2)
- Inner loop to check rectangle containment: O(n)
- Overall Time Complexity = O(n^3)
- Space Complexity = O(1)
*/

class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        int n = points.size();
        int result = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                bool isX1UpperLeftx2 = x1 <= x2 && y1 >= y2;
                if (!isX1UpperLeftx2) continue;

                bool valid_pair = true;
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) continue;
                    int x3 = points[k][0], y3 = points[k][1];
                    bool isX3insRectangle = x1 <= x3 && x3 <= x2 && y2 <= y3 && y3 <= y1;
                    if (isX3insRectangle) {
                        valid_pair = false;
                        break;
                    }
                }

                if (valid_pair) result++;
            }
        }
        return result;
    }
};
