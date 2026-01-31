class Solution {
    static constexpr int mod = 1e9 + 7;
    typedef long long ll;
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        unordered_map<int, ll> h;
        unordered_map<int, int> pos;
        for (int i = 0; i < n; ++i) 
            pos[arr[i]] = i;
        function<ll(int)> dfs = [&](int root) -> ll {
            if (h.count(root)) return h[root];
            ll& rs = h[root];
            rs = 1;
            for (int i = 0; 1ll * arr[i] * arr[i] <= 1ll * root; ++i) {
                if (root % arr[i] == 0 && pos.count(arr[i]) && pos.count(root / arr[i])) {
                    if (arr[i] != root / arr[i])
                        rs = (rs + 2 * (dfs(arr[i]) * dfs(root / arr[i])) % mod) % mod;
                    else rs = (rs + (dfs(arr[i]) * dfs(arr[i])) % mod) % mod;
                }
            }
            return rs;
        };
        int ans = 0;
        for (int& c : arr) {
            ans = (ans + dfs(c)) % mod;
        }
        return ans;
    }
};