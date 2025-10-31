/*
Problem:
--------
In the town of Digitville, you are given an integer array `nums` that contains
numbers from 0 to n - 1. Normally, each number should appear exactly once.
However, two numbers appear **twice** (duplicated). Your task is to return
those two sneaky duplicated numbers in any order.

Approach:
---------
Use an `unordered_map<int, int>` to count occurrences of each number while
iterating over the array. Whenever a number reaches a count of 2, push it
into the result list.

Time Complexity:
----------------
O(n) — We iterate through the list once.

Space Complexity:
-----------------
O(n) — Worst case, the hashmap may store counts for up to n numbers.
*/

class Solution {
public:
    vector<int> getSneakyNumbers(vector<int>& nums) {
        unordered_map<int, int>num_to_count;
        vector<int>result;
        for(int num: nums){
            num_to_count[num]++;
            if(num_to_count[num] == 2)result.push_back(num);
        }
        return result;
    }
};
