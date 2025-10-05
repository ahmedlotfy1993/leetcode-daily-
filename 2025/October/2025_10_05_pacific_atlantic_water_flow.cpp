/*
Problem: Pacific Atlantic Water Flow
-----------------------------------
You are given an m x n matrix `heights` representing the height of each cell on an island.
- The Pacific Ocean touches the **top** and **left** edges.
- The Atlantic Ocean touches the **bottom** and **right** edges.

Rainwater can flow **from a cell to neighboring cells (up, down, left, right)**
if the neighbor's height is **less than or equal** to the current cell's height.

Return all coordinates `[r, c]` from which water can flow to **both** oceans.

-----------------------------------
Example:
Input:
heights = [
  [1,2,2,3,5],
  [3,2,3,4,4],
  [2,4,5,3,1],
  [6,7,1,4,5],
  [5,1,1,2,4]
]
Output:
[[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]

-----------------------------------
Approach : Multi-Source BFS (Reverse Flow)
-----------------------------------
Idea:
- Instead of starting from every cell and checking if it can reach both oceans,
  we reverse the logic:
  - Start **from both oceans simultaneously**.
  - Perform BFS/DFS *in reverse*: move from lower/equal neighbors to higher cells.
- Mark all cells reachable **from the Pacific**.
- Mark all cells reachable **from the Atlantic**.
- Cells reachable from both sets are part of the result.

Algorithm:
1. Initialize two boolean matrices: `pacific_visited` and `atlantic_visited`.
2. Start BFS from all Pacific-border and Atlantic-border cells.
3. From each BFS queue, traverse only to cells with height >= current cell.
4. After both BFS runs, collect cells marked reachable by both oceans.

Underlying technique:
→ **Graph traversal (BFS)** with reverse reachability logic (from oceans inward).

-----------------------------------
Time Complexity:
O(m * n)
- Each cell is visited at most twice (once for each ocean BFS).

Space Complexity:
O(m * n)
- For visited matrices and BFS queues.
-----------------------------------
*/

class Solution {
    struct cell {
        int x, y, height;
        cell(int x_, int y_, int h) : x(x_), y(y_), height(h) {}
    };
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pacific_visited(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic_visited(m, vector<bool>(n, false));

        queue<cell> qP, qA;
        // Pacific: top row + left column
        for (int j = 0; j < n; j++) {
            qP.emplace(0, j, heights[0][j]);
            pacific_visited[0][j] = true;
            qA.emplace(m - 1, j, heights[m - 1][j]);
            atlantic_visited[m - 1][j] = true;
        }
        for (int i = 0; i < m; i++) {
            qP.emplace(i, 0, heights[i][0]);
            pacific_visited[i][0] = true;
            qA.emplace(i, n - 1, heights[i][n - 1]);
            atlantic_visited[i][n - 1] = true;
        }

        vector<vector<int>> dirs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        auto bfs = [&](queue<cell>& q, vector<vector<bool>>& visited) {
            while (!q.empty()) {
                auto cur = q.front();
                q.pop();
                for (auto& dir : dirs) {
                    int nx = cur.x + dir[0];
                    int ny = cur.y + dir[1];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                        !visited[nx][ny] && heights[nx][ny] >= cur.height) {
                        visited[nx][ny] = true;
                        q.emplace(nx, ny, heights[nx][ny]);
                    }
                }
            }
        };

        bfs(qP, pacific_visited);
        bfs(qA, atlantic_visited);

        vector<vector<int>> result;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (pacific_visited[i][j] && atlantic_visited[i][j])
                    result.push_back({i, j});

        return result;
    }
};
