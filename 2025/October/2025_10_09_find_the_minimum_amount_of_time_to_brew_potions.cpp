/*
Problem: Minimum Brewing Time for Sequential Wizards and Potions
---------------------------------------------------------------
We are given:
- n wizards, each with skill[i]
- m potions, each with mana[j]
Every potion must pass **sequentially** through all wizards in order.
Each wizard i takes time:
      time[i][j] = skill[i] * mana[j]

Each potion j:
  - Must start with wizard 0.
  - After finishing with wizard k, it immediately goes to wizard k+1 (no waiting gap).
  - The next potion cannot start for a wizard until that wizard finishes the current one.

We must compute the **minimum total time** for all potions to be brewed sequentially.

---------------------------------------------------------------
Conceptual Analogy:
This is essentially a **pipeline scheduling** problem.
- Wizard[i] = machine/stage i
- Potion[j]  = job j

The timeline looks like a pipeline flow:
Wizard0 → Wizard1 → Wizard2 → ... → WizardN-1  
Each potion flows through this pipeline one after another.

---------------------------------------------------------------
Algorithm (Pipeline DP Simulation)
---------------------------------------------------------------
We maintain `finishTime[i]` = time when wizard i is free after processing potions so far.

For each potion j:
    potionFinish = 0
    for wizard i = 0 .. n-1:
        processing = skill[i] * mana[j]
        potionFinish = max(potionFinish, finishTime[i]) + processing
        // 'max' ensures synchronization (can only start when both potion and wizard are ready)

    finishTime[n-1] = potionFinish

Then, for synchronization with next potion:
    - We back-propagate intermediate finish times for previous wizards
      to reflect when the potion actually reached each wizard.
      This ensures correct overlap when next potion starts.
---------------------------------------------------------------

Time Complexity: O(n * m)
Space Complexity: O(n)

---------------------------------------------------------------
*/

class Solution {
public:
    using ll = long long;

    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size();
        int m = mana.size();
        vector<ll> finishTime(n, 0);  // finish time for each wizard

        for (int j = 0; j < m; ++j) {
            ll potionFinish = 0;

            // Forward pass: simulate potion flow through wizards
            for (int i = 0; i < n; ++i) {
                ll processTime = 1LL * skill[i] * mana[j];
                potionFinish = max(potionFinish, finishTime[i]) + processTime;
            }

            // Update last wizard’s finish time for this potion
            finishTime[n - 1] = potionFinish;

            // Backward pass: sync intermediate wizard finish times
            for (int i = n - 2; i >= 0; --i) {
                ll nextProcessTime = 1LL * skill[i + 1] * mana[j];
                finishTime[i] = finishTime[i + 1] - nextProcessTime;
            }
        }

        return finishTime[n - 1];
    }
};
