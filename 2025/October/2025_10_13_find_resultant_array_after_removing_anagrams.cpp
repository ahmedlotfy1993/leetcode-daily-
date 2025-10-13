/***************************************************************************************************
💠 Problem: Remove Anagrams (LeetCode-style)
----------------------------------------------------------------------------------------------------
You are given a 0-indexed string array `words`, where each `words[i]` consists of lowercase English letters.

🔹 In one operation:
    - Select any index `i` such that `0 < i < words.length`, and
    - If `words[i - 1]` and `words[i]` are anagrams, delete `words[i]` from the array.

Keep performing this operation as long as there exists such an index `i`.

Return the resulting array of words after performing all operations.

It can be shown that the final result is **independent of the order** in which you perform the deletions.

----------------------------------------------------------------------------------------------------
📘 Definition:
An **Anagram** is a word or phrase formed by rearranging all letters of another word or phrase,
using all original letters exactly once.
Example: "dacb" is an anagram of "abdc".

----------------------------------------------------------------------------------------------------
🔹 Example 1:
Input:
    words = ["abba","baba","bbaa","cd","cd"]
Output:
    ["abba","cd"]

Explanation:
    - "abba" and "baba" are anagrams → remove "baba"
    - "abba" and "bbaa" are anagrams → remove "bbaa"
    - "cd" and "cd" are anagrams → remove the second "cd"
    Final result: ["abba", "cd"]

----------------------------------------------------------------------------------------------------
💡 Approach:
1️⃣ Initialize an empty result vector.
2️⃣ Iterate through the input `words` one by one.
3️⃣ For each word:
      - If the result vector is empty → directly push the word.
      - Otherwise, compare it with the last word in the result:
            • Sort both strings alphabetically.
            • If they are equal → current word is an anagram → skip it.
            • Otherwise → push it to the result.
4️⃣ Return the final `result` vector.

Since we only compare each word to the last valid word, the process naturally
simulates the "keep removing adjacent anagrams" operation.

----------------------------------------------------------------------------------------------------
⏱️ Time Complexity:
    O(n * L log L)
    - For each of the n words, sorting costs O(L log L), where L = average word length.

🧠 Space Complexity:
    O(n * L)
    - To store the resulting words and temporary sorted copies.

----------------------------------------------------------------------------------------------------
✅ Implementation:
***************************************************************************************************/
class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words) {
        vector<string> result;
        
        for (string word : words) {
            if (!result.empty()) {
                string last = result.back();
                string temp_word = word;
                sort(temp_word.begin(), temp_word.end());
                sort(last.begin(), last.end());
                
                if (last != temp_word) {
                    result.push_back(word);
                }
            } else {
                result.push_back(word);
            }
        }
        
        return result;
    }
};
