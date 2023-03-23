// https://leetcode.cn/problems/construct-target-array-with-multiple-sums/
// 很有趣的数学问题


class Solution {
public:
    bool isPossible(vector<int>& target) {
        int n = target.size();
        if (n == 1) return target[0] == 1;
        unordered_map<int, int> h;

        for (int c : target) {
            ++h[c];
            if (c > 1 && h[c] > 1) return false;
        }

        // the initial status
        if (h[1] == n) return true;

        long long sum = 0;
        priority_queue<long long> q;

        for (int c : target) {
            sum += 1ll * c;
            q.emplace(1ll * c);
        }

        while (!q.empty() && sum > n) {
            auto  u = q.top();
            q.pop();
            sum -= u;
            if (u <= sum) return false;
            long long y = u % sum;
            // it means there no way
            if (y == 0) {
                if (sum == 1) return true;
                else return false;
            }
            // it is valid
            q.emplace(y);
            sum += y;
        }
        return true;
    }
};