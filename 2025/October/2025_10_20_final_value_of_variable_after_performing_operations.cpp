/***************************************************************************************************
💠 Problem: Final Value of Variable After Performing Operations
----------------------------------------------------------------------------------------------------
You are given an array of strings `operations`, where each string represents one of the following:
    "++X"  → Pre-increment operation (increase X by 1)
    "X++"  → Post-increment operation (increase X by 1)
    "--X"  → Pre-decrement operation (decrease X by 1)
    "X--"  → Post-decrement operation (decrease X by 1)

Initially, the variable X = 0.

Return the final value of X after performing all operations in the given order.

----------------------------------------------------------------------------------------------------
🔹 Example 1:
Input:
    operations = ["--X","X++","X++"]
Output:
    1
Explanation:
    X = 0 → -1 → 0 → 1

🔹 Example 2:
Input:
    operations = ["++X","++X","X++"]
Output:
    3

----------------------------------------------------------------------------------------------------
💡 Approach: Direct Counting ✅
----------------------------------------------------------------------------------------------------
🔸 Observation:
    - Any operation containing "++" increases X by 1.
    - Any operation containing "--" decreases X by 1.
🔸 Therefore, we can iterate once and count increments vs. decrements directly.

----------------------------------------------------------------------------------------------------
🔹 Key Technique:
- String pattern check (simple decision based on substring match)
- No complex data structures required

----------------------------------------------------------------------------------------------------
🔸 Time Complexity:  O(n)
    - One pass over the list of operations.

🔸 Space Complexity: O(1)
    - Constant auxiliary space.

***************************************************************************************************/
class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
#if USE_DIRECT_COUNT
        int result = 0;
        for (const auto& operation : operations) {
            if (operation == "++X" || operation == "X++")
                result++;
            else
                result--;
        }
        return result;
#endif
    }
};
