/*
Problem Statement:
------------------
Anti-theft security devices are activated inside a bank. You are given a 0-indexed binary string array `bank`
representing the floor plan of the bank, which is an m x n 2D matrix. 

- `bank[i]` represents the ith row, consisting of '0's and '1's.
  - '0' means the cell is empty.
  - '1' means the cell has a security device.

There is **one laser beam** between any two security devices if both conditions are met:
  1. The two devices are located on two different rows: r1 and r2, where r1 < r2.
  2. For each row i where r1 < i < r2, there are **no security devices** in the ith row.

Laser beams are independent (they don’t interfere or combine with each other).

Return the **total number of laser beams** in the bank.


Approach:
---------
1. Iterate through each row and count the number of security devices ('1's) in that row.
2. Skip rows that have zero devices since they don’t contribute to any laser connections.
3. When encountering a row with devices:
   - Multiply the number of devices in this row by the number of devices in the previous valid (non-empty) row.
   - Add this product to the total number of beams.
   - Update the previous row’s device count.
4. Continue until all rows are processed.

This works because each pair of consecutive rows with devices forms all possible connections between their devices.


Time Complexity:
----------------
O(m * n)
- We iterate through all rows (m) and count '1's in each (n characters per row).

Space Complexity:
-----------------
O(1)
- Only a few integer variables are used regardless of input size.


Code:
-----
*/

class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int SecurityDevice_num = 0;
        int answer = 0;
        int DeviceNumPrevRow = 0;

        for (int i = 0; i < bank.size(); i++) {
            SecurityDevice_num = count(bank[i].begin(), bank[i].end(), '1');
            if (!SecurityDevice_num) continue;
            else {
                answer += DeviceNumPrevRow * SecurityDevice_num;
                DeviceNumPrevRow = SecurityDevice_num;
            }
        }
        return answer; 
    }
};
