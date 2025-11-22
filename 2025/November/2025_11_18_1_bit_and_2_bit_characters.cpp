/*
    Problem Summary:
    ----------------
    We are given a binary array `bits` that encodes characters using the following scheme:
    - The first character type uses 1 bit: 0
    - The second character type uses 2 bits: 10 or 11
    The array always ends with 0. Determine if the last character is necessarily a one-bit character.

    Approach:
    ---------
    • Initialize index = 0.
    • Traverse the array:
        - If bits[index] == 0:
            • If this is the last element, the last character is a one-bit character, set ans = true.
            • Increment index by 1.
        - If bits[index] == 1:
            • This represents a two-bit character, skip the next bit by incrementing index by 2.
    • Return ans at the end.

    Time Complexity:
    ----------------
    O(n), where n = bits.size()
    • Each bit is visited at most once.

    Space Complexity:
    -----------------
    O(1), only a few integer variables are used.
*/

class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int n = bits.size();
        int index = 0;
        bool ans = false;

        while (index < n) {
            if (bits[index] == 0) {
                if (index == n - 1) ans = true;  // Last character is one-bit
                index++;
            } else {
                index += 2;  // Skip the two-bit character
            }
        }

        return ans;
    }
};
