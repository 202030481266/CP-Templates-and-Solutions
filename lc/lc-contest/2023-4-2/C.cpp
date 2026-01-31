class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        if (k == 0) return accumulate(reward2.begin(), reward2.end(), 0);

        int n = reward1.size();
        if (k >= n) return accumulate(reward1.begin(), reward1.end(), 0); // eat all

        priority_queue<pair<int, int>> q;
        for (int i = 0; i < n; ++i) {
            q.emplace(reward1[i] - reward2[i], i);
        }
        int ans = 0;
        vector<int> use(n, false);
        while (k--) {
            auto [u, v] = q.top();
            q.pop();
            ans += reward1[v];
            use[v] = true;
        }
        for (int i = 0; i < n; ++i) {
            if (!use[i]) {
                ans += reward2[i];
            }
        }
        return ans;
    }
};