/*
Problem:
--------
Given an integer `numRows`, return the first `numRows` of Pascal's Triangle.

Pascal's Triangle is constructed such that:
- The first and last elements of each row are 1.
- Each inner element is the sum of the two elements directly above it.

Example:
Input: numRows = 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/

/*
Approach:
---------
Recursive Approach:
  - Base cases: return `{}` for 0 and `{{1}}` for 1.
  - For other values, recursively generate the triangle for (numRows - 1),
     then compute the next row based on the last row.
  - The new row is initialized with all 1s, and internal elements are computed
     using the sum of the two elements above it in the previous row.
  - The new row is appended to the result and returned.

Pros:
  - Simple and elegant.
  - Easy to understand recursively.

Cons:
  - Inefficient due to repeated recomputation (no memoization).
  - May lead to stack overflow for large `numRows`.
*/

#define RECURSIVE_APPROACH
#ifdef RECURSIVE_APPROACH
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows == 0) return {};
        if (numRows == 1) return {{1}};
        
        vector<vector<int>> prevRows = generate(numRows - 1);
        vector<int> newRow(numRows, 1);
        
        for (int i = 1; i < numRows - 1; i++) {
            newRow[i] = prevRows.back()[i - 1] + prevRows.back()[i];
        }
        
        prevRows.push_back(newRow);
        return prevRows;
    }
};
#endif

/*
Approach:
---------
Iterative Approach:
  - Starts with an empty result vector.
  - For each row from 0 to (numRows - 1):
      - Create a row of size (i + 1) with all elements initialized to 1.
      - For each internal column (1 to i-1), set current_row[col] =
         result[i-1][col-1] + result[i-1][col].
      - Append the current_row to the result.
  - This efficiently builds the triangle row by row without recursion.

Pros:
  - Time-efficient (O(numRows^2)).
  - Avoids recursion overhead.
  - Suitable for large inputs.

*/
#define ITERATIVE_APPROACH
#ifdef ITERATIVE_APPROACH
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>>result;
        for(int i = 0; i< numRows; i++){
            vector<int>current_row(i + 1,1);
            for(int col = 1; col < i ; col++)
                current_row[col] = result.back()[col - 1] + result.back()[col];
            result.emplace_back(current_row);
        }
        return result;
    }
};
#endif
