/*
  Problem:
  --------
    Given an array of integers nums, repeatedly find two adjacent numbers that are non-coprime 
    (i.e., their GCD > 1), replace them with their LCM (Least Common Multiple), and continue 
    until no more adjacent non-coprime pairs exist. Return the final modified array. 

    Notes:
    - Non-coprime numbers share a common factor greater than 1.
    - The final array is guaranteed to have all numbers <= 10^8.

  Approach:
  ---------
    1) USE_STACK_APPROACH:
        - Use a stack to maintain the processed numbers.
        - For each new number, check the top of the stack for non-coprime pairs.
        - If GCD > 1, pop the top, compute LCM with the current number, and repeat until no more merges.
        - Finally, reconstruct the result array from the stack.

    2) USE_VECTOR_APPROACH:
        - Use a vector as a stack to store the result progressively.
        - For each number in nums, check the last element in the vector.
        - While the last element and the current number are non-coprime, replace them with LCM and pop the last element.
        - Push the merged number to the vector.
        - Return the vector as the final array.

  Time Complexity:
  ----------------
    O(n * log(max_num)), where n = size of nums, because each GCD/LCM operation takes O(log(max_num)) time.

  Space Complexity:
  -----------------
    O(n), for storing the stack/vector of merged numbers.
*/

#define USE_STACK_APPROACH 0
#define USE_VECTOR_APPROACH 1

class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
#if USE_STACK_APPROACH
        auto gcd = [](int a, int b) {
            while (b != 0) {
                int temp = b;
                b = a % b; 
                a = temp;
            }
            return a;
        };
        int size = nums.size();
        stack<long long> s_result;
        s_result.push(nums[0]);

        for (int index = 1; index < size; index++) {
            long long current = nums[index];

            while (!s_result.empty()) {
                long long top = s_result.top();
                long long g = gcd(top, current);
                if (g > 1) {
                    s_result.pop();
                    current = (top * current) / g;
                } else {
                    break;
                }
            }

            s_result.push(current);
        }
        vector<int> result(s_result.size());
        for (int index = result.size() - 1; index >= 0; index--) {
            result[index] = s_result.top();
            s_result.pop();
        }
        return result;
#endif

#if USE_VECTOR_APPROACH
        vector<int> result; 
      
        for (int num : nums) {
            long long current = num;
            while (!result.empty() && gcd(result.back(), current) > 1) {
                current = lcm(result.back(), current);
                result.pop_back();
            }
            result.push_back(current);
        }

        return result;
#endif
    }
};
