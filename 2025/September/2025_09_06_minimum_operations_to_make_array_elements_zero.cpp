/*
Problem:
--------
We are given a list of queries. 
Each query is of the form [l, r], which represents an array:
    nums = [l, l+1, ..., r].

Operation allowed:
- Pick two integers (a, b) from nums.
- Replace them with floor(a/4) and floor(b/4).

Task:
- For each query, compute the minimum number of operations needed 
  to reduce all elements of nums to zero.
- Return the total sum across all queries.
*/

/*
--------------------------------------------------
Approach (buckets counting):
---------
For each query [l, r]:
1. Build buckets of numbers where each bucket corresponds to a division depth.
   - Bucket 0: [l..3] (numbers < 4)
   - Bucket 1: [4..15]
   - Bucket 2: [16..63]
   - and so on, until exceeding r.
2. For each bucket, accumulate steps = bucket_size * (depth).
3. Compute operations = ceil(total_steps / 2).
4. Add result to global sum.

--------------------------------------------------
Complexity:
-----------
- Each query needs O(log(max(r))) buckets (since we grow by powers of 4).
- For Q queries, total = O(Q * log(max(r))).
- Space: O(log(max(r))) for bucket sizes.

--------------------------------------------------
*/
#define BUCKETS_COUNTING
#ifdef BUCKETS_COUNTING
class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        long long result = 0;

        for (const auto& query : queries) {
            int start_range = query[0];
            int end_range = query[1];

            long long next_bucket_start = 4;
            vector<long long> buckets;

            while (next_bucket_start < start_range) {
                buckets.push_back(0);
                next_bucket_start *= 4;
            }

            while (next_bucket_start <= end_range) {
                buckets.push_back(next_bucket_start - start_range);
                start_range = next_bucket_start;
                next_bucket_start *= 4;
            }

            buckets.push_back(end_range - start_range + 1);

            int num_buckets = buckets.size();
            long long total_steps = 0;

            for (int bucket_index = 0; bucket_index < num_buckets; bucket_index++) {
                int division_depth = bucket_index + 1;
                total_steps += (buckets[bucket_index] * division_depth);
            }

            result += (total_steps + 1) / 2;
        }

        return result;
    }
};
#endif
/*
--------------------------------------------------
Approach (inline bucket aggregation):
-----------------
- For each query [l, r]:
  - Start from bucket [1..3] at level 1 (power = 1).
  - Grow bucket size ×4 each time.
  - For each bucket, compute overlap with [l, r] and accumulate steps.
  - Stop once r is fully covered.
  - Result contribution = ceil(total_steps / 2).

--------------------------------------------------
Complexity:
-----------
- Each query traverses O(log_4(r)) buckets.
- If Q = number of queries, total = O(Q * log(r)).
- Space = O(1).

--------------------------------------------------
*/
#define INLINE_BUCKETS_AGGREGATION
#ifdef INLINE_BUCKETS_AGGREGATION
class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        long long result = 0;

        for (const auto& query : queries) {
            long long l = query[0];
            long long r = query[1];

            long long total_steps = 0;
            long long power = 1;   
            int level = 1;

            while (power <= r) {
                long long bucket_start = power;
                long long bucket_end;

                if (power > r / 4) {
                    bucket_end = r;
                    long long left = max(l, bucket_start);
                    long long right = min(r, bucket_end);
                    if (left <= right) total_steps += (right - left + 1) * level;
                    break;
                }

                bucket_end = power * 4 - 1;
                long long left = max(l, bucket_start);
                long long right = min(r, bucket_end);
                if (left <= right) total_steps += (right - left + 1) * level;

                power *= 4;
                ++level;
            }

            result += (total_steps + 1) / 2;
        }

        return result;
    }
};
#endif
