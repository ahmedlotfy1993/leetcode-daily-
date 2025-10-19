/***************************************************************************************************
💠 Problem: Lexicographically Smallest String After Applying Operations
----------------------------------------------------------------------------------------------------
You are given:
  - A string `s` of even length consisting of digits '0' to '9'.
  - Two integers `a` and `b`.

You can perform either of the following operations **any number of times and in any order**:

1️⃣ Add operation:
     ➤ Add integer `a` to all digits at **odd indices** (0-indexed).
     ➤ If a digit exceeds 9, it wraps around to 0 (i.e., modulo 10 addition).
     Example: s = "3456", a = 5 → s = "3951"

2️⃣ Rotate operation:
     ➤ Rotate the string to the **right by b positions**.
     Example: s = "3456", b = 1 → s = "6345"

Return the **lexicographically smallest string** obtainable by applying the above operations any number of times.

----------------------------------------------------------------------------------------------------
🔹 Example 1:
Input:
    s = "5525", a = 9, b = 2
Output:
    "2050"
Explanation:
    Apply add operation twice → "5505" → "5050"
    Rotate → "2050"
    It’s the smallest possible string.

🔹 Example 2:
Input:
    s = "74", a = 5, b = 1
Output:
    "24"

----------------------------------------------------------------------------------------------------
💡 Approach: Breadth-First Search (BFS) Over All Reachable States ✅
----------------------------------------------------------------------------------------------------
🔸 We treat each string configuration as a **state**.
🔸 From each state:
     - Apply the add operation.
     - Apply the rotate operation.
     - Push unseen resulting states into a BFS queue.
🔸 Keep track of all visited strings using a `unordered_set` to avoid cycles.
🔸 During traversal, maintain the smallest string seen so far.

The BFS ensures all possible configurations are explored in increasing depth order
and guarantees we find the lexicographically smallest reachable string.

----------------------------------------------------------------------------------------------------
🔹 Key Technique:
- BFS (state-space traversal)
- Modular arithmetic for digit wrapping
- String rotation handling

----------------------------------------------------------------------------------------------------
🔸 Time Complexity:  O(10 * n²)
    - At most 10 rotations × 10 additions × n string operations.
    - Each string operation (copy/rotation) is O(n).

🔸 Space Complexity: O(10 * n)
    - For the visited set and BFS queue.

***************************************************************************************************/
class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
#if USE_BFS
        unordered_set<string> seen;
        queue<string> q;
        string res = s;
        int n = s.size();

        q.push(s);
        seen.insert(s);

        while (!q.empty()) {
            string cur = q.front(); 
            q.pop();

            res = min(res, cur);

            // Operation 1: Add 'a' to all digits at odd indices
            string add = cur;
            for (int i = 1; i < n; i += 2) {
                add[i] = (add[i] - '0' + a) % 10 + '0';
            }
            if (seen.insert(add).second) q.push(add);

            // Operation 2: Rotate right by 'b' positions
            string rot = cur.substr(n - b) + cur.substr(0, n - b);
            if (seen.insert(rot).second) q.push(rot);
        }

        return res;
#endif
    }
};
