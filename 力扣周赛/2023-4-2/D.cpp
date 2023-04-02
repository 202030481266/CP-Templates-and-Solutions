class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        unordered_set<int> ban;
        for (int u : banned) ban.emplace(u);

        set<int> sets[2];
        for (int i = 0; i < n; ++i) {
            if (!ban.count(i) && i != p) sets[i % 2].emplace(i);
        }
        sets[0].emplace(n);
        sets[1].emplace(n);

        vector<int> ans(n, -1);
        vector<int> q{p};
        for (int i = 0; !q.empty(); ++i) {
            vector<int> tmp;
            for (int u : q) {
                ans[u] = i;
                int left = max(u - k + 1, k - 1 - u);
                int right = min(u + k - 1, 2 * n - k - 1 - u);
                auto &s = sets[left % 2];
                for (auto it = s.lower_bound(left); *it <= right; it = s.erase(it)) {
                    // 边删边遍历
                    tmp.push_back(*it);
                }
            }
            q = move(tmp);
        }
        return ans;
    }
};