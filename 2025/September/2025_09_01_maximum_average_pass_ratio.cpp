/*
Problem:
--------
We have a list of classes, where each class i has:
- passi students who will pass
- totali total students

We also have extraStudents brilliant students who are guaranteed to pass in any class.  
We must assign these extra students across classes to maximize the average pass ratio.

Definitions:
- Pass ratio of a class = pass / total
- Average pass ratio = sum of all class pass ratios / number of classes

Task:
-----
Return the maximum possible average pass ratio after optimally distributing all extraStudents.  
The answer must be within 1e-5 of the correct result.

Example:
--------
classes = [[1,2], [3,5], [2,2]], extraStudents = 2

- Initial pass ratios = [0.5, 0.6, 1.0]
- Assign 1st extra student → best marginal gain is class [1,2] → becomes [2,3]
- Assign 2nd extra student → best marginal gain is class [2,3] → becomes [3,4]
- Final ratios = [0.75, 0.6, 1.0], average = 0.7833...
*/

/*
Approach (Greedy + Priority Queue / Max-Heap):
----------------------------------------------
1. **Marginal Gain (Δ)**:
   For each class, compute the *increase in pass ratio* if one extra student is added:
     Δ = (pass + 1) / (total + 1) - (pass) / (total)

   This represents the benefit of assigning one extra student to that class.

2. **Greedy Choice**:
   At each step, assign the extra student to the class with the **highest Δ** 
   (the class that benefits most from the extra student).

3. **Implementation**:
   - Use a **max-heap (priority queue)** where each class is ordered by its current Δ.
   - Initially, push all classes into the heap.
   - While extraStudents > 0:
       - Pop the class with the largest Δ.
       - Assign one extra student (increment both pass and total).
       - Push the class back with its new Δ.
   - After distributing all extra students, compute the average pass ratio.

4. **Complexity**:
   - Heap operations take O(log N).
   - We push/pop once per extra student → O(extraStudents * log N).
   - Final computation: O(N).

   This is efficient enough for typical constraints.

*/

class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        double tot_pass_ratio = 0.0;
        auto max_heap = [](const vector<int>& a, const vector<int>& b) {
                        auto gain = [](int pass, int total) {return (double)(pass + 1) / (total + 1) - (double)pass / total;};
                        return gain(a[0], a[1]) < gain(b[0], b[1]); 
                        };

        priority_queue<vector<int>, vector<vector<int>>, decltype(max_heap)> max_pass_ratio_queue(classes.begin(), classes.end(), max_heap);
        while(extraStudents > 0){
            auto student_class = max_pass_ratio_queue.top();
            max_pass_ratio_queue.pop();
            student_class[0]++;
            student_class[1]++;
            max_pass_ratio_queue.push(student_class);
            extraStudents--;
        }
        while(!max_pass_ratio_queue.empty()){
            auto student_class = max_pass_ratio_queue.top();
            max_pass_ratio_queue.pop();
            tot_pass_ratio += (double)(student_class[0]) /student_class[1];
        }
        return tot_pass_ratio/classes.size() ;
    }
};
