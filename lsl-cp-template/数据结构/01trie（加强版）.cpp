struct Trie {
    int ch[40005 * 15][2];
    int sz[40005 * 15];
    int cnt;
    
    void init() {
        cnt = 1;
        ch[0][0] = ch[0][1] = 0;
        sz[0] = 0;
    }
    
    void insert(int x) {
        int u = 0;
        sz[u]++;
        for (int i = 14; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (!ch[u][b]) {
                ch[cnt][0] = ch[cnt][1] = 0;
                sz[cnt] = 0;
                ch[u][b] = cnt++;
            }
            u = ch[u][b];
            sz[u]++;
        }
    }
    
    void remove(int x) {
        int u = 0;
        sz[u]--;
        for (int i = 14; i >= 0; i--) {
            int b = (x >> i) & 1;
            u = ch[u][b];
            sz[u]--;
        }
    }

    // 查询 x 与 trie 中某个数 xor 的最大值（x 不必在 trie 中）
    int queryMax(int x) {
        int u = 0, res = 0;
        for (int i = 14; i >= 0; i--) {
            int b = (x >> i) & 1;
            int want = 1 - b;
            if (ch[u][want] && sz[ch[u][want]] > 0) {
                res |= (1 << i);
                u = ch[u][want];
            } else {
                u = ch[u][b];
            }
        }
        return res;
    }

    // 查询 trie 中任意两数的最大 xor 值
    int dfs(int u, int bit) {
        if (bit < 0) return 0;
        int l = ch[u][0], r = ch[u][1];
        bool hasL = l && sz[l] > 0;
        bool hasR = r && sz[r] > 0;
        if (hasL && hasR) {
            return (1 << bit) + maxXorBetween(l, r, bit - 1);
        } else {
            return dfs(hasL ? l : r, bit - 1);
        }
    }

    int maxXorBetween(int u, int v, int bit) {
        if (bit < 0) return 0;
        auto has = [&](int node, int b) {
            return ch[node][b] && sz[ch[node][b]] > 0;
        };
        int res = 0;
        if (has(u, 0) && has(v, 1))
            res = max(res, (1 << bit) + maxXorBetween(ch[u][0], ch[v][1], bit - 1));
        if (has(u, 1) && has(v, 0))
            res = max(res, (1 << bit) + maxXorBetween(ch[u][1], ch[v][0], bit - 1));
        if (res) return res;
        if (has(u, 0) && has(v, 0))
            res = max(res, maxXorBetween(ch[u][0], ch[v][0], bit - 1));
        if (has(u, 1) && has(v, 1))
            res = max(res, maxXorBetween(ch[u][1], ch[v][1], bit - 1));
        return res;
    }

    // 查询 trie 中任意两数的最大 xor 值（入口）
    int queryAllMax() {
        if (sz[0] < 2) return 0;
        return dfs(0, 14);
    }
} trie;