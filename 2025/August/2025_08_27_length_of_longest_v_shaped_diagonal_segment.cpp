/*
Problem:
--------
You are given a 2D integer matrix `grid` of size n x m, where each cell contains either 0, 1, or 2.

A **V-shaped diagonal segment** is defined by:
1. The segment starts with the value `1`.
2. The sequence must then follow the infinite repeating pattern: [2, 0, 2, 0, ...].
   - Example valid segment: [1, 2, 0, 2, 0].
3. The segment travels along a diagonal direction:
   - top-left to bottom-right  (↘)
   - bottom-right to top-left  (↖)
   - top-right to bottom-left  (↙)
   - bottom-left to top-right  (↗)
4. The path may make **at most one clockwise 90° turn** to another diagonal direction, but must still follow the sequence.
5. The task: return the maximum possible length of such a V-shaped segment, or `0` if none exist.

*/

/*
Approach (BFS-based search):
----------------------------
1. **Initialization**:
   - Iterate through all cells in the grid.
   - If a cell contains `1`, it can serve as the starting point of a V-segment.
   - For each starting point, explore all 4 diagonal directions.
   - If the immediate next diagonal cell contains `2` (the next expected number), enqueue it for BFS.

2. **BFS State**:
   Each BFS node/state stores:
   - Current cell `(row, col)`
   - Current direction `dirIndex`
   - Whether a turn has already been made (`hasTurned`)
   - Current segment length `lengthSoFar`
   - The expected next value in the sequence (`expectedValue`)

3. **BFS Expansion**:
   - Move one step further in the current diagonal direction.
   - If the next cell matches the expected value, continue extending the segment.
   - If a turn has not yet been made:
     - Try making a clockwise 90° turn to the next diagonal.
     - If the next cell in the turned direction matches the expected value, continue BFS with `hasTurned = true`.

4. **Tracking Result**:
   - Update `maxLength` whenever a longer valid segment is found.
   - Continue BFS until all possible paths are explored.

-------------------------------------------------------------------

Complexity Analysis:
--------------------
- Let n = rows, m = cols.
- Each cell can be enqueued multiple times with different directions and states.
- Time Complexity: O(n * m * 4) ≈ O(n*m), since each state expansion is bounded by constant directions.
- Space Complexity: O(n * m * 4), due to BFS queue and visited states.

-------------------------------------------------------------------
*/

#define USING_BFS
#ifdef USING_BFS
class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int numRows = grid.size();
        int numCols = grid[0].size();

        vector<vector<int>> diagonalDirs{ {1,1}, {1,-1}, {-1,-1}, {-1,1} };
        int numDirections = diagonalDirs.size();
    
        // State in BFS: (row, col, dirIndex, turnUsed, lengthSoFar, expectedValue)
        queue<tuple<int,int,int,bool,int,int>> bfsQueue;

        int maxLength = 0;

        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                if (grid[row][col] == 1) {
                    maxLength = 1;
                    for (int dirIndex = 0; dirIndex < numDirections; dirIndex++) {
                        int nextRow = row + diagonalDirs[dirIndex][0];
                        int nextCol = col + diagonalDirs[dirIndex][1];
                        bool valid_point = nextRow >= 0 && nextRow < numRows && nextCol >= 0 && nextCol < numCols;
                        if (valid_point && grid[nextRow][nextCol] == 2) {
                            bfsQueue.emplace(nextRow, nextCol, dirIndex, false, maxLength + 1, 0);
                        }
                    }
                }
            }
        }

        while (!bfsQueue.empty()) {
            auto [row, col, dirIndex, hasTurned, lengthSoFar, expectedValue] = bfsQueue.front();
            bfsQueue.pop();

            maxLength = max(maxLength, lengthSoFar);
            int nextRow = row + diagonalDirs[dirIndex][0];
            int nextCol = col + diagonalDirs[dirIndex][1];
            bool valid_point = nextRow >= 0 && nextRow < numRows && nextCol >= 0 && nextCol < numCols;
            if (valid_point &&grid[nextRow][nextCol] == expectedValue) {
                bfsQueue.emplace(nextRow, nextCol, dirIndex, hasTurned, lengthSoFar + 1, grid[row][col]);
            }
            if (!hasTurned) {
                int newDirIndex = (dirIndex + 1) % numDirections;
                int turnRow = row + diagonalDirs[newDirIndex][0];
                int turnCol = col + diagonalDirs[newDirIndex][1];
                bool valid_turn_point = turnRow >= 0 && turnRow < numRows && turnCol >= 0 && turnCol < numCols;
                if (valid_turn_point && grid[turnRow][turnCol] == expectedValue) {
                    bfsQueue.emplace(turnRow, turnCol, newDirIndex, true, lengthSoFar + 1, grid[row][col]);
                }
            }
        }
        return maxLength;
    }
};
#endif
/*
Approach:
---------
1. **DFS Traversal**:
   - Starting from every cell that contains `1` (the required starting value),
     explore all 4 possible diagonal directions.
   - At each step, check the next diagonal cell:
     - If it matches the expected value in the sequence (2 → 0 → 2 → 0 → ...),
       continue the DFS.
   - The sequence alternates between `2` and `0`, so we pass the next expected
     value recursively (`target = 2 - target`).

2. **Turn Handling**:
   - Each path is allowed **at most one clockwise 90° turn**.
   - The DFS carries a boolean flag `turn` that indicates whether a turn is still available.
   - If `turn == true`, we can either:
     - Continue in the same diagonal direction, OR
     - Try turning clockwise once and continue DFS in the new direction.
   - After using the turn, `turn` becomes `false`.

3. **Memoization (DP table)**:
   - To avoid recomputation, results are cached in a 4D DP table:
     `dp[row][col][direction][turnUsed]`
   - This stores the longest possible segment length starting from `(row, col)`
     when moving in `direction` with/without turn available.
   - DP ensures each state is solved once, improving efficiency.

4. **Result Computation**:
   - For each starting cell with value `1`, run DFS in all 4 directions
     with the turn initially available (`turn = true`).
   - Add 1 for the starting cell.
   - Track the maximum length across all possible paths.

Complexity:
-----------
- Let n = rows, m = cols.
- Each state `(row, col, direction, turn)` is visited at most once.
- Time Complexity: O(n * m * 4 * 2) → O(n*m).
- Space Complexity: O(n * m * 4 * 2) for memoization table + recursion stack.
*/
#ddefine USING_DFS_WITH_MEMORIZATION
#ifdef USING_DFS_WITH_MEMORIZATION

class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int dirs[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
        vector<vector<vector<vector<int>>>> dp(m, vector<vector<vector<int>>>(n, vector<vector<int>>(4, vector<int>(2, -1))));

        function<int(int, int, int, bool, int)> dfs =
            [&](int cx, int cy, int direction, bool turn, int target) -> int {
            int nx = cx + dirs[direction][0];
            int ny = cy + dirs[direction][1];

            if (nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] != target) return 0;

            if (dp[nx][ny][direction][turn] != -1) return dp[nx][ny][direction][turn];

            int maxStep = dfs(nx, ny, direction, turn, 2 - target);
            if (turn) maxStep = max(maxStep, dfs(nx, ny, (direction + 1) % 4, false, 2 - target));

            dp[nx][ny][direction][turn] = maxStep + 1;
            return maxStep + 1;
        };

        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    for (int direction = 0; direction < 4; ++direction) {
                        res = max(res, dfs(i, j, direction, true, 2) + 1);
                    }
                }
            }
        }

        return res;
    }
};
#endif
