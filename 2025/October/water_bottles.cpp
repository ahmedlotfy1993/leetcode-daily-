/*
--------------------------------------------------------------------------------
Problem:
You start with `numBottles` full water bottles. Each time you drink one, it 
becomes an empty bottle. You can exchange `numExchange` empty bottles for one 
full bottle from the market. The task is to calculate the maximum number of 
water bottles you can drink.

--------------------------------------------------------------------------------
Example:
Input: numBottles = 9, numExchange = 3
Process:
- Start: 9 full → drink all → 9 empty
- Exchange 9/3 = 3 → get 3 new full → total drunk = 9 + 3 = 12
- Drink 3 → 3 empty
- Exchange 3/3 = 1 → get 1 full → total drunk = 12 + 1 = 13
- Drink 1 → 1 empty, not enough to exchange
Output: 13

--------------------------------------------------------------------------------
Approach:
1. Start with `numDrinkBottles = numBottles` and `numEmptyBottles = numBottles`.
2. While there are enough empty bottles to exchange:
   - Compute new bottles = numEmptyBottles / numExchange.
   - Add them to the total count.
   - Update empty bottles = remainder + newly obtained full bottles.
3. Repeat until fewer than `numExchange` empty bottles remain.
4. Return total count.

--------------------------------------------------------------------------------
Complexity:
- Time Complexity: O(log(numBottles))  
  (Each loop reduces the number of empty bottles significantly).
- Space Complexity: O(1)  
  (Only a few integer variables are used).

--------------------------------------------------------------------------------
*/

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int numDrinkBottles = numBottles;
        int numEmptyBottles = numBottles;

        while (numBottles) {
            // Calculate how many new full bottles we can get
            numBottles = numEmptyBottles / numExchange;

            // Increase total count of drunk bottles
            numDrinkBottles += numBottles;

            // Update empty bottles: remainder + newly obtained bottles
            numEmptyBottles = (numEmptyBottles % numExchange) + numBottles;
        }

        return numDrinkBottles;
    }
};
