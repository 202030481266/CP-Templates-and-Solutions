class Solution {
public:
    int earliestSecondToMarkIndices(vector<int> &nums, vector<int> &changeIndices) {
        int n = nums.size();
        int m = changeIndices.size();
        long long total = n + accumulate(nums.begin(), nums.end(), 0LL);

        vector<int> first_t(n, -1);
        for (int t = m - 1; t >= 0; t--) {
            first_t[changeIndices[t] - 1] = t;
        }

        auto check = [&](int mx) -> bool {
            int cnt = 0;
            long long slow = total; // 慢速复习+考试所需天数
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            for (int t = mx - 1; t >= 0; t--) {
                int i = changeIndices[t] - 1;
                int v = nums[i];
                if (v <= 1 || t != first_t[i]) {
                    cnt++; // 留给左边，用来快速复习/考试
                    continue;
                }
                if (cnt == 0) {
                    if (pq.empty() || v <= pq.top().first) {
                        cnt += 1; // 留给左边，用来快速复习/考试
                        continue;
                    }
                    slow += pq.top().first + 1;
                    pq.pop();
                    cnt += 2; // 反悔：一天快速复习，一天考试
                }
                slow -= v + 1;
                cnt--; // 快速复习，然后消耗一天来考试
                pq.emplace(v, i);
            }
            return cnt >= slow; // 剩余天数不能慢速复习+考试
        };

        int left = n - 1, right = m + 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right > m ? -1 : right;
    }
};

