/*
--------------------------------------------------------------------------------
Problem:
Given an array of points on the 2D plane, return the area of the largest 
triangle that can be formed using any three different points.

The answer is accepted if it is within 1e-5 of the actual result.

--------------------------------------------------------------------------------
Approach:
  Brute Force Enumeration (O(n^3)):
   - Iterate over all possible triplets of points (i, j, k).
   - Compute the area of the triangle formed by these three points.
   - Keep track of the maximum area found.
   - For three points (x1, y1), (x2, y2), (x3, y3), the triangle area can be computed using the shoelace formula (determinant method):
       Area = 0.5 * | x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2) |
   - This avoids floating-point trigonometry and is robust for integer inputs.

--------------------------------------------------------------------------------
Time Complexity:
- There are C(n, 3) = O(n^3) triplets.
- For each triplet, area is computed in O(1).
Overall: O(n^3)

Space Complexity:
- O(1), only storing max area.

--------------------------------------------------------------------------------
*/

class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        double result = 0;
        int n = points.size();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    int x1 = points[i][0], y1 = points[i][1];
                    int x2 = points[j][0], y2 = points[j][1];
                    int x3 = points[k][0], y3 = points[k][1];
                    // Shoelace formula for triangle area
                    double area = 0.5 * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
                    result = max(result, area);
                }
            }
        }
        return result;
    }
};
