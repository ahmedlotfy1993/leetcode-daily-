/*
🟢 Problem: Maximum 69 Number (LeetCode #1323)

🔍 Description:
Given a positive integer 'num' consisting only of the digits 6 and 9,
return the maximum number you can obtain by changing **at most one digit**.
You are allowed to change a single '6' to '9', or a single '9' to '6'.

🎯 Goal:
Maximize the number by modifying at most one digit.

💡 Strategy:
To get the maximum number:
- Locate the first occurrence of '6' (starting from the most significant digit).
- Change it to '9' to get the largest possible increase.
- Only one change is allowed, so stop after the first change.

🛠️ Implementation:
- Convert the number to a string.
- Use `find()` to locate the first '6'.
- If found, replace it with '9'.
- Convert the string back to an integer and return.

🕒 Time Complexity: O(1) — at most 4 digits (constant time)
📦 Space Complexity: O(1) — minimal extra space used for the string

✅ Example:
Input: 9669
Output: 9969
Explanation: Change the first '6' to '9' to get the maximum number.
*/

class Solution {
public:
    int maximum69Number (int num) {
        string number = to_string(num);
        size_t index = number.find('6');
        if (index != string::npos) number[index] = '9';
        return stoi(number);
    }
};
