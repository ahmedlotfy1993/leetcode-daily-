/**************************************************************************************
 * Problem:
 * You are given:
 *    - Two integers m and n representing a 0-indexed m x n grid.
 *    - A list of guard positions: guards[i] = {row_i, col_i}
 *    - A list of wall positions : walls[j]  = {row_j, col_j}
 *
 * Rules:
 *    - Guards can see in the four directions (N, S, E, W).
 *    - Guard vision is blocked by:
 *          • A wall
 *          • Another guard
 *    - Any cell that a guard can see is marked as guarded.
 *
 * Goal:
 *    Return the number of unoccupied cells that are *not guarded*.
 *
 * ------------------------------------------------------------------------------------
 * Approach (Simulation — Sweep in 4 directions per guard):
 *    1. Create a 2D grid initialized to 0 (meaning unoccupied & unguarded).
 *    2. Mark walls as 1 and guards as 2.
 *    3. For every guard, sweep in the 4 cardinal directions:
 *         - Stop when encountering either a wall (1) or a guard (2).
 *         - Mark the path cells as guarded (3).
 *    4. Count all cells that remain 0.
 *
 * ------------------------------------------------------------------------------------
 * Time Complexity:
 *    O(m*n + G*4*max(m, n))
 *    (In worst case, each guard may scan across a full row/column)
 *
 * Space Complexity:
 *    O(m*n) — for the grid representation
 *
 **************************************************************************************/

class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        /*!
         * Create 2D grid as 0.
         * Iterate over the gaurds one by one and mark thier cells with 1.
         * Iterate over the walls one by one nd mark thier cells with 2.
         * For each gaurd, all cells in thier sights can be marked 3 if it was 0 unless reach to cell with 1 or 2.
         * Count cells with 0 value.
        */
        vector<vector<int>> grid(m, vector<int>(n, 0));

        for (auto& w : walls)
            grid[w[0]][w[1]] = 1;

        for (auto& g : guards)
            grid[g[0]][g[1]] = 2;

        int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        for (auto& g : guards) {
            for (auto& d : dirs) {
                int r = g[0] + d[0];
                int c = g[1] + d[1];

                while (r >= 0 && r < m && c >= 0 && c < n && grid[r][c] != 1 && grid[r][c] != 2) {
                    if (grid[r][c] == 0)
                        grid[r][c] = 3;

                    r += d[0];
                    c += d[1];
                }
            }
        }

        int count = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (grid[i][j] == 0)
                    count++;

        return count;
    }
};
