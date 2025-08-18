/*
=====================================
  🎯 24 Game Problem Description
=====================================

Given a list of 4 cards (integers in the range [1, 9]), the goal is to determine
if these numbers can be combined using the binary operators {+, -, *, /}
and valid use of parentheses to form an expression that evaluates to the number 24.

Each card must be used exactly once.
Each operation must involve two operands.
Unary operators (like -a) and digit concatenation (e.g., 1 and 2 forming 12) are not allowed.

=====================================
  📘 Discrete Math Concepts Applied
=====================================

1. **Permutations without Replacement**
   - The 4 input numbers can appear in any order.
   - We must consider all 4! = 24 permutations of these numbers.
   - This is a permutation because:
     - Order matters (e.g., 8 - 4 ≠ 4 - 8)
     - No repetition allowed (each card used once)

2. **Cartesian Product with Repetition**
   - We need to choose 3 binary operators to place between the 4 numbers.
   - The set of operators is {+, -, *, /}.
   - Since operators can repeat and order matters, the number of possible operator combinations is:
     4^3 = 64
   - This is a Cartesian product: all ordered tuples of 3 elements from a 4-element set with repetition.

3. **Expression Tree Structures (Associativity)**
   - There are 5 unique ways to parenthesize 4 numbers with 3 binary operators.
   - These represent different binary expression trees — an application of Catalan structures.

4. **Floating-Point Arithmetic and Approximate Equality**
   - Real division is required (e.g., 1 / 2 = 0.5).
   - Due to floating-point precision, a small epsilon value (e.g., 1e-6) is used to compare results to 24.
*/

/*
=====================================
  🛠️ Solution Strategy Summary
=====================================

- Generate all 24 permutations of the 4 input numbers (no repition and order matters).
- For each permutation, generate all 64 combinations of the 3 operators (allow repitions and order matters).
- For each combination, evaluate all 5 valid parenthesis groupings.
- Use backtracking to exhaust all possible valid expression trees.
- Return true if any expression evaluates to 24 within a small error tolerance.

This exhaustive approach is feasible due to the limited and bounded search space.
*/

class Solution {
    inline static const double EPSILON = 1e-6;
    inline static const vector<char> ops = {'+', '-', '*', '/'};

    double apply(double a, double b, char op) {
        if (op == '+') return a + b;
        if (op == '-') return a - b;
        if (op == '*') return a * b;
        if (op == '/') return fabs(b) < EPSILON ? 1e9 : a / b; // Avoid divide-by-zero
        return 1e9;
    }

    bool check(double result) {
        return fabs(result - 24.0) < EPSILON;
    }
    bool evaluateAll(double a, double b, double c, double d) {
        for (char op1 : ops) {
            for (char op2 : ops) {
                for (char op3 : ops) {
                    // ((a op1 b) op2 c) op3 d
                    double r1 = apply(a, b, op1);
                    double r2 = apply(r1, c, op2);
                    double r3 = apply(r2, d, op3);
                    if (check(r3)) return true;

                    // (a op1 (b op2 c)) op3 d
                    r1 = apply(b, c, op2);
                    r2 = apply(a, r1, op1);
                    r3 = apply(r2, d, op3);
                    if (check(r3)) return true;

                    // a op1 ((b op2 c) op3 d)
                    r1 = apply(b, c, op2);
                    r2 = apply(r1, d, op3);
                    r3 = apply(a, r2, op1);
                    if (check(r3)) return true;

                    // a op1 (b op2 (c op3 d))
                    r1 = apply(c, d, op3);
                    r2 = apply(b, r1, op2);
                    r3 = apply(a, r2, op1);
                    if (check(r3)) return true;

                    // (a op1 b) op2 (c op3 d)
                    r1 = apply(a, b, op1);
                    r2 = apply(c, d, op3);
                    r3 = apply(r1, r2, op2);
                    if (check(r3)) return true;
                }
            }
        }
        return false;
    }
public:
    bool judgePoint24(vector<int>& cards) {
        sort(cards.begin(), cards.end());
        do {
            vector<double> v(cards.begin(), cards.end());
            if (evaluateAll(v[0], v[1], v[2], v[3])) return true;
        } while (next_permutation(cards.begin(), cards.end()));
        return false;  
    }
};
