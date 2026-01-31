class Solution {
public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        // 分组
        unordered_map<int, int> ind;
        int n = nums.size();
        vector<vector<pair<int, int>>> g;
        for (int i = 0; i < n; ++i) {
            if (!ind.count(nums[i])) {
                ind[nums[i]] = g.size();
                g.push_back({});
            }
        }
        int pre = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i] != nums[pre]) {
                int index = ind[nums[pre]];
                g[index].emplace_back(pre, i); // [pre, i)
                pre = i;
            }
        }
        g[ind[nums[pre]]].emplace_back(pre, n); //[pre, n)
        int ans = 0;
        for (auto& arr : g) {
            int m = arr.size();
            int l = 0, res = arr[0].second - arr[0].first, sum = 0;
            ans = max(ans, res); // 这里需要取最大值
            for (int i = 1; i < m; ++i) {
                // [a, b) [c, d) 距离就是 [b, c)
                sum += arr[i].first - arr[i - 1].second;
                res += arr[i].second - arr[i].first;
                while (sum > k) {
                    sum -= arr[l + 1].first - arr[l].second;
                    res -= arr[l].second - arr[l].first;
                    ++l;
                }
                ans = max(ans, res);
            }
        }
        return ans;
    }
};