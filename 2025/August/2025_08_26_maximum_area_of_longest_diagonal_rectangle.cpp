/*
Problem:
---------
You are given a 2D 0-indexed integer array `dimensions`, where:
- dimensions[i][0] is the length of the i-th rectangle
- dimensions[i][1] is the width of the i-th rectangle

You need to:
1. Compute the diagonal length for each rectangle using the Pythagorean theorem:
     diagonal = sqrt(length² + width²)
2. Find the rectangle(s) with the **longest diagonal**
3. If multiple rectangles share the same longest diagonal, return the one with the **largest area**
4. Return the **area** of the selected rectangle

Note:
- To avoid floating-point inaccuracies, we compare diagonal lengths using their squared values:
     diagonal² = length² + width²
*/

/*
Approach #1:
----------------------------------------
- Iterate over all rectangles
- For each rectangle:
  - Compute squared diagonal: `length² + width²`
  - Compute area: `length * width`
- Maintain:
  - `max_diagonal`: largest diagonal seen so far (squared)
  - `max_area`: corresponding area for the max diagonal
- If a new longer diagonal is found, update both
- If the diagonal is equal to the current max, update area only if it’s larger
- Return the area with the longest diagonal

Time Complexity: O(n), Space Complexity: O(1)
*/
#define BRUTE_FORCE
#ifdef BRUTE_FORCE
class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        int n = dimensions.size();
        if(n == 0)return 0;
        if(n == 1)return dimensions[0][0] * dimensions[0][1];
        int max_diagonal = 0;
        int max_area = 0;
        for(int i = 0; i < n; i++){
           int current_diagonal =  dimensions[i][0] * dimensions[i][0] + dimensions[i][1] * dimensions[i][1];
           int current_area = dimensions[i][0] * dimensions[i][1];
           if(current_diagonal > max_diagonal){
                max_diagonal = current_diagonal;
                max_area = current_area;
           }else if (current_diagonal == max_diagonal){
                max_area = max(max_area, current_area);
           }
        }
        return max_area;
    }
};
#endif
/*
Approach #2:
----------------------------------------------------
- Use a `map<int, set<int>>` to group rectangles by their squared diagonal length
  - Keys: squared diagonal lengths, sorted in descending order
  - Values: set of corresponding rectangle areas, also sorted in descending order
- Return the largest area from the first entry in the map (longest diagonal)

Time Complexity: O(n log n) due to map and set insertion
Space Complexity: O(n)

Both approaches yield the correct result. The first is more space and time efficient, while the second offers cleaner grouping at the cost of additional overhead.
*/
#define USING_ORDERED_CONTAINERS
#ifdef USING_ORDERED_CONTAINERS
class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        int n = dimensions.size();
        if(n == 0)return 0;
        if(n == 1)return dimensions[0][0] * dimensions[0][1];
        map<int, set<int, greater<int>>, greater<int>> diagonal_to_areas;
        for(int i = 0; i < n; i++){
            int current_diagonal =  dimensions[i][0] * dimensions[i][0] + dimensions[i][1] * dimensions[i][1];
            int current_area = dimensions[i][0] * dimensions[i][1];
            diagonal_to_areas[current_diagonal].insert(current_area);
        }
        return *(diagonal_to_areas.begin()->second.begin());
    }
};
#endif
