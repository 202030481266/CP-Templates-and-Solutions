typedef pair<int, int> pii;
class Solution {
public:
    long long maxSpending(vector<vector<int>>& values) {
        // 贪心
        // 排序不等式

        int n = values.size(), m = values[0].size();
        priority_queue<pii, vector<pii>, greater<pii>> q;

        for (int i = 0; i < n; ++i) 
            q.emplace(values[i][m - 1], i * m + m - 1);

        long long ans = 0, t = 0;
        while (!q.empty()) {
            ++t;
            auto [value, index] = q.top();
            q.pop();
            ans += t * value;
            int x = index / m, y = index % m;
            if (y - 1 >= 0) q.emplace(values[x][y - 1], index - 1);
        }
        return ans;
    }
};