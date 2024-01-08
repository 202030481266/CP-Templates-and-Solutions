class Solution {
    using ll = long long;
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int n = points.size();
        int ans = 0;

        const ll offset = 1e9; 

        unordered_map<ll, ll> cnt;

        for (int i = 0; i < n; ++i) {
            cnt.clear();
            for (int j = 0; j < n; ++j) {
                ll x = abs(points[i][0] - points[j][0]), y = abs(points[i][1] - points[j][1]);
                ++cnt[x * x + y * y];
            }
            for (auto [u, v] : cnt) {
                ans += (v - 1) * v;
            }
        }
        return ans;
    }
};