/*
    Problem Summary:
    ----------------
    You are given an n x n matrix initially filled with zeros.
    You must process Q submatrix-addition queries:
        For each query [r1, c1, r2, c2]:
            Add 1 to all cells mat[x][y] such that:
                r1 <= x <= r2
                c1 <= y <= c2

    Naive solution:
        For each query, iterate over all (r2-r1+1)*(c2-c1+1) cells and add 1.
        Worst case: O(Q * n^2) → too slow.

    Optimal Approach:
    -----------------
    Use a 2D difference array (a.k.a. 2D prefix-difference technique).
    This transforms each submatrix update into O(1) modifications:
        diff[r1][c1]           += 1
        diff[r1][c2 + 1]       -= 1
        diff[r2 + 1][c1]       -= 1
        diff[r2 + 1][c2 + 1]   += 1

    After processing all queries, compute:
        1. Row-wise prefix sums.
        2. Column-wise prefix sums.

    The result becomes the final matrix.

    Why it works:
    -------------
    The difference matrix encodes how values change when moving horizontally or vertically.
    A 2D prefix-sum reconstruction yields the actual values after all rectangular updates.

    Time Complexity:
        • Building diff using all queries: O(Q)
        • Row-wise prefix sum:   O(n^2)
        • Column prefix sum:     O(n^2)
        Total: O(n^2 + Q)

    Space Complexity:
        O(n^2) for the matrix.

*/

class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> result(n, vector<int>(n, 0));

        for (const auto& q : queries) {
            int r1 = q[0], c1 = q[1];
            int r2 = q[2], c2 = q[3];

            result[r1][c1] += 1;
            if (c2 + 1 < n) result[r1][c2 + 1] -= 1;
            if (r2 + 1 < n) result[r2 + 1][c1] -= 1;
            if (r2 + 1 < n && c2 + 1 < n) result[r2 + 1][c2 + 1] += 1;
        }

        // Row-wise prefix sum
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                result[i][j] += result[i][j - 1];
            }
        }

        // Column-wise prefix sum
        for (int j = 0; j < n; j++) {
            for (int i = 1; i < n; i++) {
                result[i][j] += result[i - 1][j];
            }
        }

        return result;
    }
};
