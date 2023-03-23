// https://leetcode.cn/problems/number-of-flowers-in-full-bloom/
// 逆向映射，反过来计算花对答案的贡献


class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        int n = flowers.size(), m = people.size();

        vector<int> ans(m);
        vector<pair<int, int>> b;

        for (int i = 0; i < m; ++i) {
            b.emplace_back(people[i], i);
        }
        sort(b.begin(), b.end());

        vector<int> sum(m + 1);
        for (auto flower : flowers) {
            auto left = lower_bound(b.begin(), b.end(), pair<int, int>{flower[0], -1});
            auto right = upper_bound(b.begin(), b.end(), pair<int, int>{flower[1], INT_MAX});
            // [left, right)
            if (left == b.end()) {
                // there is no people at the right time
                continue;
            }
            else {
                int l = left - b.begin(), r;
                if (right == b.end()) r = m;
                else r = right - b.begin();
                // [l, r) add 1
                sum[r] -= 1;
                sum[l] += 1;
            }
        }
        for (int i = 1; i < m; ++i)
            sum[i] += sum[i - 1];
        for (int i = 0; i < m; ++i)
            ans[b[i].second] = sum[i];
        return ans;
    }
};