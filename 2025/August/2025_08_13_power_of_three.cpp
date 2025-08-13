class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) return false; // Negative numbers and zero are not powers of three
        while (n % 3 == 0) n /= 3; // Divide by 3 as long as it's divisible
        return n == 1; // If n reduces to 1, it's a power of three
    }
};
