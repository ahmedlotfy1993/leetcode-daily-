/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#define APPROACH_PARENTS_MAPPING   0   // Keeps track of parents of nodes (less efficient)
#define APPROACH_HASH_SET          1   // Optimal, uses unordered_set

class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {

#if APPROACH_PARENTS_MAPPING
        /*********************************************************************
         * Approach #1 (Less optimal):
         * Use a map<int, vector<ListNode*>> to store all parent pointers of
         * nodes whose values match nums[]. Later, use these parents to unlink nodes.
         *
         * Time Complexity:  O(n + m)
         *      - n = number of nodes in the list
         *      - m = nums.size()
         *      But overhead of storing parent pointers makes this slower than optimal.
         *
         * Space Complexity: O(n + m)
         *      - map stores all nodes grouped by value
         *********************************************************************/

        if (!head) return head;

        unordered_map<int, vector<ListNode*>> parents;
        unordered_set<ListNode*> nodesToRemove;

        // Build parent relationships (track who points to whom)
        ListNode* current = head;
        parents[current->val].push_back(nullptr); // head has no parent

        while (current->next) {
            parents[current->next->val].push_back(current);
            current = current->next;
        }

        // Mark all nodes that should be removed
        for (int num : nums) {
            if (parents.count(num)) {
                for (ListNode* parent : parents[num]) {
                    ListNode* actualNode = (parent == nullptr) ? head : parent->next;
                    nodesToRemove.insert(actualNode);
                }
            }
        }

        // Remove nodes using a dummy
        ListNode dummy(0, head);
        ListNode* prev = &dummy;
        current = head;

        while (current) {
            if (nodesToRemove.count(current)) {
                prev->next = current->next;
                current->next = nullptr;
                current = prev->next;
            } else {
                prev = current;
                current = current->next;
            }
        }

        return dummy.next;
#endif


#if APPROACH_HASH_SET
        /*********************************************************************
         * Approach #2 (Optimal Recommended Solution):
         * Use an unordered_set<int> to store all values that should be removed.
         * Then do a single traversal and unlink nodes on the fly.
         *
         * Time Complexity:  O(n + m)
         *      - O(m) to build hash set
         *      - O(n) to traverse and remove nodes
         *
         * Space Complexity: O(m)
         *      - unordered_set contains only nums[]
         *********************************************************************/

        unordered_set<int> toRemove(nums.begin(), nums.end());

        ListNode dummy(0, head);
        ListNode* prev = &dummy;
        ListNode* current = head;

        while (current) {
            if (toRemove.count(current->val)) {
                ListNode* temp = current;
                prev->next = current->next;   // unlink node
                current = current->next;
                temp->next = nullptr;         // optional cleanup
            } else {
                prev = current;
                current = current->next;
            }
        }

        return dummy.next;
#endif
    }
};
