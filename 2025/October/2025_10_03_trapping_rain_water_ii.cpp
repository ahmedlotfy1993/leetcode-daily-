/*
  * Problem:
  * --------
  * - You are given a 2D elevation map (m x n grid).
  * - Each cell has a height (heightMap[i][j]).
  * - After raining, water can be trapped inside the low-lying cells.
  * - The amount of water trapped in a cell is limited by the minimum boundary height 
  *   around it compared to the cell's height.
  * - Goal: Compute the total water volume trapped.
  *
  * Approach (Priority Queue / BFS):
  * -------------------------------------------------------------------
  * 1. Any water trapped must be bounded by the "lowest boundary wall".
  *    Therefore, we start from the outer boundary cells (which cannot trap water), and treat them as the initial "walls".
  * 2. Use a min-heap (priority_queue with greater<>) to always expand from the current lowest-height boundary cell.
  * 3. Process:
  *      - Pop the lowest cell from the heap.
  *      - Visit its unvisited neighbors.
  *      - If a neighbor is lower, water can be trapped  lowest_cell.height - neighbor.height.
  *      - Push the neighbor into the heap, but with height updated to max(lowest_cell.height, neighbor.height)
  *        ensures the "effective boundary" is maintained.
  * 4. Continue until all cells are processed.
         * Complexity:
         * -----------
         * - Each cell is pushed/popped from the priority queue once.
         * - Heap operations cost O(log(m*n)).
         * - Time: O(m*n * log(m*n)).
         * - Space: O(m*n) for visited matrix + heap.
*/
class Solution {
    struct cell {
        int x;
        int y;
        int height;
        cell(int x_, int y_, int h) : x(x_), y(y_), height(h) {}
        bool operator > (const cell& rhs) const {
            return height > rhs.height;
        }
    };

public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        int n = heightMap[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        priority_queue<cell, vector<cell>, greater<cell>> cells;

        // Push all boundary cells into the heap
        for (int i = 0; i < m; i++) {
            cells.emplace(i, 0, heightMap[i][0]);
            cells.emplace(i, n - 1, heightMap[i][n - 1]);
            visited[i][0] = visited[i][n - 1] = true;
        }
        for (int j = 0; j < n; j++) {
            cells.emplace(0, j, heightMap[0][j]);
            cells.emplace(m - 1, j, heightMap[m - 1][j]);
            visited[0][j] = visited[m - 1][j] = true;
        }

        int waterVolumeTrapped = 0;
        while (!cells.empty()) {
            auto lowest_cell = cells.top();
            cells.pop();

            vector<vector<int>> dirs {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            for (const auto& dir : dirs) {
                int new_x = lowest_cell.x + dir[0];
                int new_y = lowest_cell.y + dir[1];
                bool is_valid_neighbor = new_x >= 0 && new_x < m && new_y >= 0 && new_y < n;

                if (is_valid_neighbor && !visited[new_x][new_y]) {
                    // Trap water if neighbor is lower than boundary
                    waterVolumeTrapped += max(0, lowest_cell.height - heightMap[new_x][new_y]);
                    // Update effective boundary height
                    cells.emplace(new_x, new_y, max(lowest_cell.height, heightMap[new_x][new_y]));
                    visited[new_x][new_y] = true;
                }
            }
        }
        return waterVolumeTrapped;
    }
};
