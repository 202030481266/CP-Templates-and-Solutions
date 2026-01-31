class Solution {
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        // 长度为 3 的最大权的简单路径 或者 长度为 4 的 最大权的环
        // 枚举中间的边即可， 然后维护所有的点的最大权的 三个 出边即可，后面就可以做分类讨论

        // 0x3f 的实现非常牛逼，抄一手
        int n = scores.size();
        vector<pair<int,int>> g[n];
        for (auto& e : edges) {
            int x = e[0], y = e[1];
            g[x].emplace_back(-scores[y], y);
            g[y].emplace_back(-scores[x], x);
        }
        for (auto& vs : g) {
            if (vs.size() > 3) {
                // 快速选择的写法，非常优雅的写法
                nth_element(vs.begin(), vs.begin() + 3, vs.end());
                vs.resize(3);
            }
        }
        int ans = -1;
        for (auto& e : edges) {
            int x = e[0], y = e[1];
            for (auto& [va, a] : g[x])
                for (auto& [vb, b] : g[y])
                    if (a != b && a != y && x != b)
                        ans = max(ans, scores[x] + scores[y] - va - vb);
        }
        return ans;
    }
};