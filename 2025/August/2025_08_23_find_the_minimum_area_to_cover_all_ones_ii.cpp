#include <vector>
#include <tuple>
using namespace std;
/*
Problem:
Given a 2D binary grid (with values 0 or 1), you are to divide all the cells containing 1s 
into exactly 3 non-empty groups. For each group, form the smallest axis-aligned rectangle 
that can contain all the points in the group, and compute its area. 
The goal is to minimize the sum of the areas of these three rectangles.

Your Solution:
1. Traverse the entire grid and collect the coordinates of all cells with value 1 into a vector.
2. Generate all possible groupings of the collected 1s into 3 non-empty groups. 
   You simulate this by assigning each point into one of the three groups in a brute-force manner.
   This is done by treating each group assignment as a base-3 number (from 0 to 3^k - 1), 
   where k is the number of 1s.
3. For each valid grouping (i.e., none of the 3 groups is empty):
   - Compute the bounding rectangle for each group by finding the minimum and maximum row and column indices.
   - Calculate the area of each rectangle as (max_row - min_row + 1) * (max_col - min_col + 1).
4. Track the minimum sum of areas across all valid groupings and return it.
*/
class Solution {
public:
    int minimumSum(vector<vector<int>>& grid) {

        /* Group all ones in a vector */
        int n = grid.size();
        int m = grid[0].size(); 
        vector<pair<int, int>> ones;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j])ones.emplace_back(i, j);
            }
        }

        /* Try all combination of grouping ones */
        int num_ones = ones.size();
        int num_total_assignements = pow(3, num_ones);
        int min_total_area = INT_MAX; 
        for(int mask = 0; mask < num_total_assignements; mask++){
            vector<vector<pair<int, int>>>groups(3);
            int temp = mask;
            for(int index = 0; index < num_ones; index++){
                groups[temp % 3].emplace_back(ones[index]);
                temp = temp / 3;
            }

            /* Avoid empty group combination */
            if(groups[0].size() == 0 || groups[1].size() == 0 || groups[2].size() == 0)continue;

            /* Get top left and bottom right for every rectangle */
            vector<tuple<int, int, int, int>> boxes;

            for (int g = 0; g < 3; ++g) {
                int min_row = INT_MAX, max_row = INT_MIN;
                int min_col = INT_MAX, max_col = INT_MIN;

                for (auto& [r, c] : groups[g]) {
                    min_row = min(min_row, r);
                    max_row = max(max_row, r);
                    min_col = min(min_col, c);
                    max_col = max(max_col, c);
                }

                boxes.emplace_back(min_row, max_row, min_col, max_col);
            }

            /* Check pairwise overlap between 3 rectangles*/
            auto isOverlap = [](const tuple<int, int, int, int>& g1 ,const tuple<int, int, int, int>& g2) {
                return !(get<1>(g1) < get<0>(g2) || get<1>(g2) < get<0>(g1) || get<3>(g1) < get<2>(g2) || get<3>(g2) < get<2>(g1));
                };

            bool group0_overlap_group1 = isOverlap(boxes[0], boxes[1]);
            bool group0_overlap_group2 = isOverlap(boxes[0], boxes[2]);
            bool group1_overlap_group2 = isOverlap(boxes[1], boxes[2]);

            if(group0_overlap_group1 || group0_overlap_group2 || group1_overlap_group2)continue;

            /* Calculate area of 3 groups & update the minimum total area*/
            auto group0_area = (get<1>(boxes[0]) - get<0>(boxes[0]) +  1) * (get<3>(boxes[0]) - get<2>(boxes[0]) +  1);
            auto group1_area = (get<1>(boxes[1]) - get<0>(boxes[1]) +  1) * (get<3>(boxes[1]) - get<2>(boxes[1]) +  1);
            auto group2_area = (get<1>(boxes[2]) - get<0>(boxes[2]) +  1) * (get<3>(boxes[2]) - get<2>(boxes[2]) +  1);
            min_total_area = min(min_total_area, group0_area + group1_area + group2_area);
        } 
        return min_total_area;
    }
};
