class Solution {
public:
    int reservoir(vector<string> &shape) {
        int n = shape.size(), m = shape[0].size(), c = 1;
        // 每个格子分成四个区域（上下左右），标上序号，方便用并查集连通
        // 假设左右下还有一圈格子，直接连到超级汇点 0
        int u[n + 1][m + 2], d[n + 1][m + 2], l[n + 1][m + 2], r[n + 1][m + 2];
        memset(u, 0, sizeof(u)); memset(d, 0, sizeof(d)); memset(l, 0, sizeof(l)); memset(r, 0, sizeof(r));
        for (int i = 0; i < n; ++i)
            for (int j = 1; j <= m; ++j) // 假设格子的列号从 1 开始，这样方便表示左右边界
                u[i][j] = c++, d[i][j] = c++, l[i][j] = c++, r[i][j] = c++;

        // 并查集模板
        int fa[c];
        iota(fa, fa + c, 0);
        function<int(int)> find = [&](int x) -> int { return fa[x] == x ? x : fa[x] = find(fa[x]); };
        auto merge = [&](int x, int y) { fa[find(x)] = find(y); };

        bool ok[c]; // 能否容纳水
        memset(ok, 0, sizeof(ok));
        // 倒着判断每一行，寻找可能有水的区域
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j <= m; j++) merge(r[i][j], l[i][j + 1]); // 连通左右
            for (int j = 1; j <= m; j++) {
                merge(d[i][j], u[i + 1][j]); // 连通下
                // 根据格子的类型连接格子内部四个区域
                if (shape[i][j - 1] == '.') merge(l[i][j], u[i][j]), merge(l[i][j], d[i][j]), merge(l[i][j], r[i][j]);
                else if (shape[i][j - 1] == 'l') merge(l[i][j], d[i][j]), merge(r[i][j], u[i][j]);
                else merge(l[i][j], u[i][j]), merge(r[i][j], d[i][j]);
            }
            for (int j = 1; j <= m; j++) {
                // 在没有连接第 i-1 行的情况下，无法到达左右下边界 => 能容纳水
                ok[l[i][j]] = find(l[i][j]) != find(0);
                ok[r[i][j]] = find(r[i][j]) != find(0);
                ok[u[i][j]] = find(u[i][j]) != find(0);
                ok[d[i][j]] = find(d[i][j]) != find(0);
            }
        }

        // 第一行连上超级汇点，方便后面统一判断是否在闭合区域里面
        for (int j = 1; j <= m; j++) merge(u[0][j], 0);

        int ans = 0;
        for (int i = 0; i < c; i++)
            ans += ok[i] && find(i) == find(0); // 能容纳水，且不在闭合区域里面
        return ans / 2;
    }
};