/*
  * Problem:
  * --------
    * - You start with numBottles full bottles.
    * - Each time you drink a bottle, it becomes an empty one.
    * - You can exchange exactly numExchange empty bottles for 1 new full bottle.
    * - After every exchange, numExchange increases by 1.
    * - Goal: maximize the total number of bottles you can drink.
    *
    * Approach:
    * ---------
      * - Initialize:
         *      numDrinkBottles = numBottles   (all initial bottles will be drunk)
         *      numEmptyBottles = numBottles   (after drinking, all are empty)
      * - While we have enough empty bottles to exchange (numEmptyBottles >= numExchange):
         *      1. Spend numExchange empty bottles → numEmptyBottles -= numExchange.
         *      2. Increase the exchange threshold → numExchange++.
         *      3. Get one new full bottle → drink it immediately → numDrinkBottles++.
         *      4. That bottle becomes empty → numEmptyBottles++.
      * - Stop once we don’t have enough empty bottles to exchange.
    * Complexity:
    * -----------
      * - Each loop increases numExchange by 1, so at most O(numBottles) iterations.
      * - Time: O(numBottles) in the worst case, practically much less.
      * - Space: O(1).
*/
class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int numDrinkBottles = numBottles;
        int numEmptyBottles = numBottles;

        while (numEmptyBottles >= numExchange) {
            numEmptyBottles -= numExchange;  // exchange empties
            numExchange++;                   // increase cost of next exchange
            numDrinkBottles++;               // drink new bottle
            numEmptyBottles++;               // it becomes empty
        }
        return numDrinkBottles;
    }
};
