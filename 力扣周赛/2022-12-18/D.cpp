class Solution {
public:
    vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries) {
        // LCA + 1
        vector<int> ans;
        for (auto c : queries) {
            int x = c[0], y = c[1];
            if (x < y) swap(y, x);
            int l = -1, r = -1;
            for (int i = 32; i >= 0; i--) {
                if (l == -1 && ((x >> i) & 1)) l = i;
                if (r == -1 && ((y >> i) & 1)) r = i;
            }
            int a = l - 1, b = r - 1, lca = 1;
            if (b < 0) {
                ans.emplace_back(l + 1);
            } else {
                while (((x >> a) & 1) == ((y >> b) & 1)) {
                    lca = lca * 2 + ((x >> a) & 1);
                    a--, b--;
                    if (b < 0) break;
                }
                if (b < 0) ans.emplace_back(a + 2);
                else ans.emplace_back(a + b + 3);
            }
        }
        return ans;
    }
};