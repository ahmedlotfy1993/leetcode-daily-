/*
Problem:
--------
You are given an n x n integer matrix `grid`.  
The task is to return a new matrix such that:
1. All diagonals in the **bottom-left triangle** (including the main diagonal)
   are sorted in **non-increasing order** (descending).
2. All diagonals in the **top-right triangle** are sorted in **non-decreasing order** (ascending).
*/
/*
Approach (Top left constrcution):
---------
1. Traverse the matrix and group elements into a map<int, vector<int>>  
   using the diagonal key `i - j`.
2. For each diagonal:
   - Sort the values based on whether the diagonal belongs to the bottom-left
     (descending) or top-right (ascending).

3. Traverse the matrix from top-left to bottom-right
    -Use an auxiliary `map<int, int> index` to keep track of how many elements of each diagonal have already been placed.


Complexity:
-----------
- Let n = matrix dimension.
- Collecting diagonals → O(n^2).
- Sorting each diagonal → O(n log n) per diagonal, total still O(n^2 log n).
- Reconstructing the result matrix → O(n^2).
- Overall Time Complexity: O(n^2 log n).
- Space Complexity: O(n^2) for storing diagonals.
*/
#define ITERATE_FROM_TOP_LEFT_CORNER_FORWARD
#ifdef ITERATE_FROM_TOP_LEFT_CORNER_FORWARD
class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>>result (n, vector<int>(n));
        map<int, vector<int>> diagonals;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                diagonals[i - j].push_back(grid[i][j]);
            }
        }
        for (auto &d : diagonals) {
            if(d.first < 0)
                sort(d.second.begin(), d.second.end(), less<int>());
            else 
                sort(d.second.begin(), d.second.end(), greater<int>());
        }
        map<int, int> index; 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int key = i - j;
                result[i][j] = diagonals[key][index[key]++];
            }
        }
};
#endif


/*
Approach  (Right bottom constrcution):
---------
1. Traverse the matrix and group elements into a map<int, vector<int>>  
   using the diagonal key `i - j`.
2. For each diagonal:
   - Sort the values based on whether the diagonal belongs to the bottom-left
     (descending) or top-right (ascending).

3.  Traverse the matrix from bottom-right to top-left.
      - For each cell `(i, j)` add the last element in the vector crosponded to key `(i, j)` and then pop the element from the vector.

Complexity:
-----------
- Let n = matrix dimension.
- Collecting diagonals → O(n^2).
- Sorting each diagonal → O(n log n) per diagonal, total still O(n^2 log n).
- Reconstructing the result matrix → O(n^2).
- Overall Time Complexity: O(n^2 log n).
- Space Complexity: O(n^2) for storing diagonals.
*/

#define ITERATE_FROM_BOTTOM_RIGHT_CORNER_BACKWARD
#ifdef ITERATE_FROM_BOTTOM_RIGHT_CORNER_BACKWARD
class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>>result (n, vector<int>(n));
        map<int, vector<int>> diagonals;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                diagonals[i - j].push_back(grid[i][j]);
            }
        }
        for (auto &d : diagonals) {
            if(d.first < 0)
                sort(d.second.begin(), d.second.end(), less<int>());
            else 
                sort(d.second.begin(), d.second.end(), greater<int>());
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int key = i - j;
                result[i][j] = diagonals[key].back();
                diagonals[key].pop_back();
            }
        }
        return result;
    }
};
#endif
