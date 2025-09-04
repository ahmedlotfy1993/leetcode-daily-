/*
Problem:
--------
We are given three integer positions on a number line:
- Person 1 is at position person1Pos.
- Person 2 is at position person2Pos.
- Person 3 is at position targetPos (fixed position).

Both Person 1 and Person 2 move toward Person 3 at the same speed.
We need to determine which person reaches Person 3 first.

Return:
- 1 → if Person 1 reaches first
- 2 → if Person 2 reaches first
- 0 → if both reach at the same time

--------------------------------------------------
*/
/*
Approach:
---------
- Compute |person1Pos - targetPos| and |person2Pos - targetPos|.
- Compare the two distances directly in a ternary expression.

--------------------------------------------------
Complexity:
-----------
- Time: O(1) → constant time.
- Space: O(1).
*/

class Solution {
public:
    int findClosest(int person1Pos, int person2Pos, int targetPos) {
        return abs(person1Pos - targetPos) != abs(person2Pos - targetPos)
                   ? (abs(person1Pos - targetPos) < abs(person2Pos - targetPos) ? 1 : 2)
                   : 0;
    }
};
