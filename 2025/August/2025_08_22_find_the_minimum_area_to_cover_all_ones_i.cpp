/*!
 * Problem:
 * --------
 * Given a 2D binary grid (only 0s and 1s), find the smallest possible
 * axis-aligned rectangle (i.e., with vertical and horizontal sides)
 * that contains all the cells with value '1'.
 *
 * Return the area of that rectangle.
 *
 */

/*
 * Solution:
 * ---------
 * To solve this problem, we need to identify the bounding rectangle that
 * encloses all the 1's in the grid.
 *
 * - Start by initializing 4 variables to track the min and max rows (heights)
 *   and columns (widths) where 1's appear:
 *     - min_height = INT_MAX
 *     - max_height = INT_MIN
 *     - min_width  = INT_MAX
 *     - max_width  = INT_MIN
 *
 * - Traverse each cell in the grid:
 *     - If a cell contains a 1:
 *         - Update min_height and max_height using the current row index.
 *         - Update min_width and max_width using the current column index.
 *
 * - After scanning the whole grid, the rectangle that includes all the 1s
 *   spans from:
 *     - row: min_height to max_height
 *     - column: min_width to max_width
 *
 * - The area of this rectangle is calculated as:
 *     (max_width - min_width + 1) * (max_height - min_height + 1)
 *
 * - If no 1's are found in the grid, return area = 0.
 *
 * Time Complexity: O(N * M) — where N is number of rows, M is number of columns.
 * Space Complexity: O(1) — only scalar variables are used.
 */
class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int min_width = INT_MAX;
        int max_width = INT_MIN;
        int min_height = INT_MAX;
        int max_height = INT_MIN;
        for(int height = 0; height < n ; height++){
            for(int width = 0; width < m; width++){
                if(grid[height][width]){
                    min_width = min(min_width, width);
                    max_width = max(max_width, width);
                    min_height = min(min_height, height);
                    max_height = max(max_height, height);
                }
            }
        }
        return min_width == INT_MAX ? 0 : (max_width - min_width +  1) * (max_height -  min_height + 1);
    }
};
