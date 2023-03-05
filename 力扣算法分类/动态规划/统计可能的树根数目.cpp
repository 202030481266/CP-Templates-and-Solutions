// https://leetcode.cn/problems/count-number-of-possible-root-nodes/description/
// 不是拓扑排序，而是换根dp！！


class Solution {
public:
    int rootCount(vector<vector<int>> &edges, vector<vector<int>> &guesses, int k) {
        vector<vector<int>> g(edges.size() + 1);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x); // 建图
        }

        unordered_set<long> s;
        for (auto &e : guesses) // guesses 转成哈希表
            s.insert((long) e[0] << 32 | e[1]); // 两个 4 字节数压缩成一个 8 字节数

        int ans = 0, cnt0 = 0;
        function<void(int, int)> dfs = [&](int x, int fa) {
            for (int y : g[x])
                if (y != fa) {
                    cnt0 += s.count((long) x << 32 | y); // 以 0 为根时，猜对了
                    dfs(y, x);
                }
        };
        dfs(0, -1);

        function<void(int, int, int)> reroot = [&](int x, int fa, int cnt) {
            ans += cnt >= k; // 此时 cnt 就是以 x 为根时的猜对次数
            for (int y : g[x])
                if (y != fa) {
                    reroot(y, x, cnt
                                 - s.count((long) x << 32 | y) // 原来是对的，现在错了
                                 + s.count((long) y << 32 | x)); // 原来是错的，现在对了
                }
        };
        reroot(0, -1, cnt0);
        return ans;
    }
};

