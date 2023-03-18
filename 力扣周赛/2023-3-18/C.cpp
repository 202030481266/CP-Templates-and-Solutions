class Solution {
public:
    long long findScore(vector<int>& nums) {
        int n = nums.size();

        set<pair<int, int>> s;
        for (int i = 0; i < n; ++i) {
            s.emplace(make_pair(nums[i], i));
        }
        long long ans = 0;
        vector<bool> vis(n, false);
        while (!s.empty()) {
            auto it = s.begin();
            ans += 1ll * (it->first);
            int pos = it->second;
            vis[pos] = true;
            s.erase(it);
            // flag the pre and next
            if (pos > 0 && !vis[pos - 1]) {
                vis[pos - 1] = true;
                auto x = s.lower_bound(make_pair(nums[pos - 1], pos - 1));
                s.erase(x);
            }
            if (pos < n - 1 && !vis[pos + 1]) {
                vis[pos + 1] = true;
                auto y = s.lower_bound(make_pair(nums[pos + 1], pos + 1));
                s.erase(y);
            }
        }
        return ans;
    }
};