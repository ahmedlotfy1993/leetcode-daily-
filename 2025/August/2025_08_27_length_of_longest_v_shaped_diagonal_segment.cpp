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
