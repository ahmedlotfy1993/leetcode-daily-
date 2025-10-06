/*
Problem: Swim in Rising Water
-----------------------------
You are given an n x n grid where grid[i][j] represents the elevation of that cell.
At time `t`, the water level rises to height `t`, submerging all cells with elevation ≤ t.

You can swim from one cell to any of its 4-directionally adjacent cells
only if **both** cells have elevation ≤ t.

Goal:
Return the **minimum time t** required to reach the bottom-right corner (n-1, n-1)
starting from the top-left corner (0, 0).

--------------------------------------------------
Approach #1: Dijkstra’s Algorithm (Min-Heap)
--------------------------------------------------
Underlying technique: **Shortest Path on Weighted Grid**

Idea:
- Treat the grid as a graph:
  - Each cell is a node.
  - Edge weight = max(current water level, neighbor elevation).
- You want to minimize the *maximum elevation* encountered on the path.
- This is analogous to Dijkstra’s algorithm where:
  - The “distance” of a cell = minimum time needed to reach it.
  - We always expand the cell with the smallest current “time”.

Algorithm:
1. Use a **min-heap** (`priority_queue` with `greater<>`).
2. Start from (0,0) with initial time = grid[0][0].
3. Always expand the lowest-time cell.
4. For each neighbor, the new time = max(current_time, neighbor_height).
5. Stop when reaching (n-1, n-1).

Time Complexity:  O(n² log n²) ≈ O(n² log n)
Space Complexity: O(n²)
--------------------------------------------------
Approach #2: Binary Search + BFS
--------------------------------------------------
Underlying technique: **Binary Search over Time + Reachability Check**

Idea:
- The time `t` must be between `max(grid[0][0], grid[n-1][n-1])` and `max elevation`.
- Use **binary search** to find the smallest `t` such that
  you can reach (n-1, n-1) using BFS where all visited cells have elevation ≤ t.

Algorithm:
1. Define helper `canReach(grid, t)` that uses BFS to check if the end is reachable.
2. Binary search over time `t`:
   - If `canReach` returns true, move left (try smaller time).
   - Else, move right.

Time Complexity:  O(n² log(max_height))
Space Complexity: O(n²)
--------------------------------------------------
*/

#if USE_DIJKSTRA
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
        pq.emplace(grid[0][0], 0, 0);
        int result = 0;
        vector<vector<int>> dirs{{1,0},{-1,0},{0,1},{0,-1}};

        while(!pq.empty()) {
            auto [time, x, y] = pq.top();
            pq.pop();
            if (visited[x][y]) continue;
            visited[x][y] = true;
            if (x == n-1 && y == n-1) {
                result = time;
                break;
            }
            for (const auto& dir : dirs) {
                int nx = x + dir[0], ny = y + dir[1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny]) {
                    int n_time = max(time, grid[nx][ny]);
                    pq.emplace(n_time, nx, ny);
                }
            }
        }
        return result;
    }
};
#endif


#if USE_BINARY_SEARCH_BFS
class Solution {
    bool canReach(vector<vector<int>>& grid, int t) {
        int n = grid.size();
        if (grid[0][0] > t) return false;
        queue<pair<int,int>> q;
        vector<vector<bool>> vis(n, vector<bool>(n,false));
        q.push({0,0});
        vis[0][0] = true;
        vector<vector<int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

        while(!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            if (x == n-1 && y == n-1) return true;
            for (auto &d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx>=0 && nx<n && ny>=0 && ny<n && !vis[nx][ny] && grid[nx][ny] <= t) {
                    vis[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
        return false;
    }
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int left = max(grid[0][0], grid[n-1][n-1]);
        int right = n*n - 1;
        int ans = right;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (canReach(grid, mid)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
};
#endif
