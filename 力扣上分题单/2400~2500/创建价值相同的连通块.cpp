class Solution {
public:
    int componentValue(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size(); 
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int mx = *max_element(nums.begin(), nums.end());
        vector<int> g[n];
        for (auto& c : edges) {
            g[c[0]].push_back(c[1]);
            g[c[1]].push_back(c[0]);
        }
        function<int(int, int, int)> dfs = [&](int u, int fa, int target) -> int {
            int tmp = nums[u];
            for (int v : g[u]) {
                if (v != fa) {
                    int rs = dfs(v, u, target);
                    if (rs < 0) return -1;
                    tmp += rs;
                }
            }
            if (tmp > target) return -1;
            else if (tmp < target) return tmp;
            return 0;
        };
        int ans = 0;
        for (int i = 1; i <= sum / mx; ++i) {
            if (sum % (i + 1) == 0 && dfs(0, -1, sum / (i + 1)) == 0) {
                ans = i;
            }
        }
        return ans;
    }
};