/**
 * Problem: Spreadsheet Implementation
 * -----------------------------------
 * We need to design a simple spreadsheet with 26 columns ('A' to 'Z')
 * and a given number of rows. Each cell can hold an integer [0, 10^5].
 * 
 * API Requirements:
 * -----------------
 *  - Spreadsheet(int rows):
 *        Initialize a spreadsheet with rows x 26 cells, all set to 0.
 * 
 *  - void setCell(string cell, int value):
 *        Set the cell (like "A1", "B10") to the given value.
 * 
 *  - void resetCell(string cell):
 *        Reset the cell back to 0.
 * 
 *  - int getValue(string formula):
 *        Given a formula like "=A1+5" or "=B3+C7", return the sum.
 *        If a cell was never set explicitly, treat its value as 0.
 * 
 * Approaches:
 * -----------
 * 1) Using 2D Vector (SPREADSHEET_IMPL_VECTOR)
 *    - Represent spreadsheet as vector<vector<int>> of size rows x 26.
 *    - Direct O(1) indexing for set/get/reset.
 *    - Validate cell references using row/col bounds.
 *    - Pros: Very fast lookups, predictable memory layout.
 *    - Cons: Uses O(rows * 26) memory even if most cells are empty.
 *
 * 2) Using Hash Map (SPREADSHEET_IMPL_HASHMAP)
 *    - Represent spreadsheet as unordered_map<string, int>.
 *    - Only store cells that are explicitly set.
 *    - Missing cells default to 0.
 *    - Pros: Memory efficient for sparse spreadsheets.
 *    - Cons: Slightly slower lookups due to hashing, and uses string keys.
 *
 * Time Complexity:
 * ----------------
 * Operation       | 2D Vector             | Hash Map
 * ----------------|---------------------|----------------------
 * setCell         | O(1)                 | O(1) average
 * resetCell       | O(1)                 | O(1) average
 * getCellValue    | O(1)                 | O(1) average
 * getValue        | O(1) per operand     | O(1) per operand
 *
 * Space Complexity:
 * -----------------
 *  - Vector: O(rows * 26) regardless of number of non-zero cells.
 *  - Hash Map: O(k) where k = number of explicitly set cells.
 *
 * When to Use:
 * ------------
 *  - Use vector when rows are known and memory isn't a concern.
 *  - Use hash map for very large, sparse spreadsheets to save memory.
 */

#define SPREADSHEET_IMPL_VECTOR   0
#define SPREADSHEET_IMPL_HASHMAP  1

#define SPREADSHEET_IMPL SPREADSHEET_IMPL_VECTOR

#if SPREADSHEET_IMPL == SPREADSHEET_IMPL_VECTOR
class Spreadsheet {
    inline static constexpr int COLUMNS = 26;
    vector<vector<int>> cells;

    bool isNumber(const string& token) const {
        return !token.empty() && all_of(token.begin(), token.end(), ::isdigit);
    }

    pair<int,int> parseCellRef(const string& cellRef) const {
        int col_index = cellRef[0] - 'A';
        int row_index = stoi(cellRef.substr(1)) - 1;
        if (row_index < 0 || row_index >= (int)cells.size() ||
            col_index < 0 || col_index >= COLUMNS) {
            throw out_of_range("Invalid cell reference: " + cellRef);
        }
        return {row_index, col_index};
    }

    int getCellValue(const string& cellRef) const {
        auto [row, col] = parseCellRef(cellRef);
        return cells[row][col];
    }

public:
    Spreadsheet(int rows) {
        cells.resize(rows, vector<int>(COLUMNS, 0));
    }

    void setCell(string cell, int value) {
        auto [row, col] = parseCellRef(cell);
        cells[row][col] = value;
    }

    void resetCell(string cell) {
        auto [row, col] = parseCellRef(cell);
        cells[row][col] = 0;
    }

    int getValue(string formula) {
        string expr = formula.substr(1);  // Remove '='
        auto plusPos = expr.find('+'); // Find the '+'
        string left = expr.substr(0, plusPos);
        string right = expr.substr(plusPos + 1);

        int leftVal  = isNumber(left)  ? stoi(left)  : getCellValue(left);
        int rightVal = isNumber(right) ? stoi(right) : getCellValue(right);
        return leftVal + rightVal;
    }
};
#endif

#if SPREADSHEET_IMPL == SPREADSHEET_IMPL_HASHMAP
class Spreadsheet {
    unordered_map<string, int> cells;

    bool isNumber(const string& token) const {
        return !token.empty() && all_of(token.begin(), token.end(), ::isdigit);
    }

    int getCellValue(const string& cellRef) const {
        auto it = cells.find(cellRef);
        return (it != cells.end()) ? it->second : 0;
    }

public:
    Spreadsheet(int /*rows*/) {
        // Rows are irrelevant here since we store only what is set
    }

    void setCell(const string& cell, int value) {
        cells[cell] = value;
    }

    void resetCell(const string& cell) {
        cells.erase(cell);
    }

    int getValue(const string& formula) const {
        string expr = formula.substr(1); // Remove '='
        auto plusPos = expr.find('+'); // Find the '+'
        string left = expr.substr(0, plusPos);
        string right = expr.substr(plusPos + 1);

        int leftVal  = isNumber(left)  ? stoi(left)  : getCellValue(left);
        int rightVal = isNumber(right) ? stoi(right) : getCellValue(right);
        return leftVal + rightVal;
    }
};
#endif
