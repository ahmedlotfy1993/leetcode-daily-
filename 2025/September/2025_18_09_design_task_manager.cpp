/**
 * Problem: Task Management System
 * --------------------------------
 * We want to design a system that manages user tasks with priorities.
 * Each task is identified by (userId, taskId, priority).
 * 
 * Supported operations:
 *  - TaskManager(vector<vector<int>>& tasks)
 *        Initialize system with tasks [userId, taskId, priority].
 *  - void add(int userId, int taskId, int priority)
 *        Add a new task for a user.
 *  - void edit(int taskId, int newPriority)
 *        Change priority of an existing task.
 *  - void rmv(int taskId)
 *        Remove a task from the system.
 *  - int execTop()
 *        Execute (remove & return userId of) the task with the highest priority.
 *        If multiple tasks have the same highest priority, the one with the
 *        highest taskId is chosen. Return -1 if no tasks exist.
 *
 * Approaches:
 * -----------
 * 1) Map + Set based implementation (TASK_MANAGER_USE_MAP_SET_INDEXES)
 *    - Each user maintains a set of (priority, taskId).
 *    - Global map from priority -> set of (taskId, userId).
 *    - taskInfo maps taskId -> (userId, priority).
 *    - Pros: Efficient per-user queries, exact removals and edits.
 *    - Cons: Slightly heavier memory usage, multiple log(n) operations per update.
 *
 * 2) Priority Queue + Lazy Deletion (TASK_MANAGER_USE_PRIORITY_QUEUE_INDEX)
 *    - Maintain a max-heap of tasks (priority, taskId, userId).
 *    - taskInfo maps taskId -> (userId, priority).
 *    - Removal and edits are lazy: old/outdated entries remain in heap until popped.
 *    - Pros: Very fast insertions, simpler structure, small constant factors.
 *    - Cons: Heap may contain stale entries, execTop() may take multiple pops.
 *
 * Time Complexity:
 * ----------------
 * Operation      | Map + Set               | Priority Queue
 * ---------------|-------------------------|------------------------
 * add()          | O(log n)                | O(log n)
 * edit()         | O(log n) (remove+insert)| O(log n) (push new entry)
 * rmv()          | O(log n)                | O(1) (lazy erase in map)
 * execTop()      | O(log n)                | Amortized O(log n) (may skip stale entries)
 *
 * Space Complexity:
 * -----------------
 *  - Map + Set: O(n) for user sets + O(n) for global map + O(n) taskInfo.
 *  - Priority Queue: O(n) for heap + O(n) for taskInfo (heap may have stale entries).
 *
 * When to Use:
 * ------------
 *  - Use Map + Set if you need frequent per-user queries or exact task iteration.
 *  - Use Priority Queue if you only need global top execution, with simpler code and faster practical performance.
 */
#define TASK_MANAGER_USE_MAP_SET_INDEXES 0
#define TASK_MANAGER_USE_PRIORITY_QUEUE_INDEX 1
#if TASK_MANAGER_USE_MAP_SET_INDEXES
class TaskManager {
    struct PriorityComparator {
        bool operator()(const pair<int,int>& lhs, const pair<int,int>& rhs) const {
            return lhs.first != rhs.first ? lhs.first > rhs.first : lhs.second > rhs.second;
        }
    };

    struct TaskIdComparator {
        bool operator()(const pair<int,int>& lhs, const pair<int,int>& rhs) const {
            return lhs.first != rhs.first ? lhs.first > rhs.first : lhs.second > rhs.second;
        }
    };

    using TaskPrioritySet = set<pair<int, int>, PriorityComparator>;  // (priority, taskId)
    using PriorityTaskSet = set<pair<int, int>, TaskIdComparator>;    // (taskId, userId)
    using TaskMetadata    = pair<int, int>;                           // (userId, priority)

    unordered_map<int, TaskPrioritySet> userTasks;
    unordered_map<int, TaskMetadata>    taskInfo;
    map<int, PriorityTaskSet, greater<int>> globalPriorityMap;

public:
    TaskManager(vector<vector<int>>& tasks) {
        /**
         * userTasks:       maps userId to set of (priority, taskId)
         * taskInfo:        maps taskId to (userId, priority)
         * globalPriorityMap: maps priority to set of (taskId, userId) for global top execution
         */
        for (const auto& task : tasks) {
            int userId   = task[0];
            int taskId   = task[1];
            int priority = task[2];

            userTasks[userId].emplace(priority, taskId);
            taskInfo[taskId] = {userId, priority};
            globalPriorityMap[priority].emplace(taskId, userId);
        }
    }
    
    void add(int userId, int taskId, int priority) {
        userTasks[userId].emplace(priority, taskId);
        taskInfo[taskId] = {userId, priority};
        globalPriorityMap[priority].emplace(taskId, userId);
    }
    
    void edit(int taskId, int newPriority) {
        auto& [userId, oldPriority] = taskInfo[taskId];

        auto& userTaskSet = userTasks[userId];
        userTaskSet.erase({oldPriority, taskId});
        userTaskSet.emplace(newPriority, taskId);

        auto& globalTaskSet = globalPriorityMap[oldPriority];
        globalTaskSet.erase({taskId, userId});
        if (globalTaskSet.empty()) globalPriorityMap.erase(oldPriority);
        globalPriorityMap[newPriority].emplace(taskId, userId);

        oldPriority = newPriority;
    }
    
    void rmv(int taskId) {
        auto& [userId, priority] = taskInfo[taskId];

        auto& userTaskSet = userTasks[userId];
        userTaskSet.erase({priority, taskId});
        if (userTaskSet.empty()) userTasks.erase(userId);

        auto& globalTaskSet = globalPriorityMap[priority];
        globalTaskSet.erase({taskId, userId});
        if (globalTaskSet.empty()) globalPriorityMap.erase(priority);

        taskInfo.erase(taskId);
    }
    
    int execTop() {
        if (globalPriorityMap.empty()) return -1;

        auto highestPriorityIt = globalPriorityMap.begin();
        auto& taskSet = highestPriorityIt->second;
        auto topTaskIt = taskSet.begin();

        int taskId = topTaskIt->first;
        int userId = topTaskIt->second;
        int priority = highestPriorityIt->first;

        taskSet.erase(topTaskIt);
        if (taskSet.empty()) globalPriorityMap.erase(highestPriorityIt);

        auto& userTaskSet = userTasks[userId];
        userTaskSet.erase({priority, taskId});
        if (userTaskSet.empty()) userTasks.erase(userId);

        taskInfo.erase(taskId);

        return userId;
    }
};
#endif

#if TASK_MANAGER_USE_PRIORITY_QUEUE_INDEX
class TaskManager {
    struct Task {
        int priority;
        int taskId;
        int userId;
    };

    struct MaxHeapComparator {
        bool operator()(const Task& a, const Task& b) const {
            if (a.priority != b.priority) return a.priority < b.priority; 
            return a.taskId < b.taskId;
        }
    };

    priority_queue<Task, vector<Task>, MaxHeapComparator> maxHeap;
    unordered_map<int, pair<int,int>> taskInfo;

public:
    TaskManager(vector<vector<int>>& tasks) {
        for (auto& t : tasks) {
            int userId = t[0], taskId = t[1], priority = t[2];
            taskInfo[taskId] = {userId, priority};
            maxHeap.push({priority, taskId, userId});
        }
    }

    void add(int userId, int taskId, int priority) {
        taskInfo[taskId] = {userId, priority};
        maxHeap.push({priority, taskId, userId});
    }

    void edit(int taskId, int newPriority) {
        auto& [userId, oldPriority] = taskInfo[taskId];
        oldPriority = newPriority;
        maxHeap.push({newPriority, taskId, userId});
    }

    void rmv(int taskId) {
        taskInfo.erase(taskId); // lazy removal
    }

    int execTop() {
        while (!maxHeap.empty()) {
            auto top = maxHeap.top();
            auto it = taskInfo.find(top.taskId);

            if (it == taskInfo.end()) { 
                maxHeap.pop(); // task was removed
                continue;
            }

            auto [userId, currentPriority] = it->second;
            if (currentPriority != top.priority) {
                maxHeap.pop(); // outdated entry
                continue;
            }

            // Valid task found → execute & remove
            maxHeap.pop();
            taskInfo.erase(top.taskId);
            return userId;
        }
        return -1; // no tasks left
    }
};
#endif
