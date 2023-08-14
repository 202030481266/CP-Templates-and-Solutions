// SAM居然被卡了，好家伙！
static constexpr int N = 100005;
struct Suffix_Automation {
    int len[N * 2], link[N * 2], siz, last;
    int f[N * 2], res[N * 2];
    unordered_map<int, int> ch[N * 2];
    vector<vector<int>> g;
    void init() {
        memset(len, 0, sizeof(len));
        memset(link, 0, sizeof(link));
        memset(res, 0, sizeof(res));
        for (int i = 0; i < N * 2; ++i) ch[i].clear();
        siz = last = 0;
        link[0] = -1;
        g.assign(N * 2, vector<int>{});
    }
    void extend(int c) {
        int cur = ++siz, p = last;
        len[cur] = len[p] + 1;
        while (p != -1 && ch[p][c] == 0) {
            ch[p][c] = cur;
            p = link[p];
        }
        if (p == -1) link[cur] = 0;
        else {
            int q = ch[p][c];
            if (len[q] == len[p] + 1) link[cur] = q;
            else {
                int copy = ++siz;
                len[copy] = len[p] + 1;
                link[copy] = link[q];
                ch[copy] = ch[q];
                while (p != -1 && ch[p][c] == q) {
                    ch[p][c] = copy;
                    p = link[p];
                }
                link[q] = link[cur] = copy;
            }
        }
        last = cur;
    }
    void update(vector<int>& a) {
        memset(f, 0, sizeof(f));
        int p = 0, l = 0;
        for (int i = 0; i < a.size(); ++i) {
            while (p && ch[p][a[i]] == 0) {
                p = link[p];
                l = len[p];
            }
            if (ch[p][a[i]]) {
                p = ch[p][a[i]];
                ++l;
            }
            f[p] = max(f[p], l);
        }
        dfs(0);
        for (int i = 1; i <= siz; ++i) res[i] = min(res[i], f[i]);
    }
    void build() {
        for (int i = 1; i <= siz; ++i) g[link[i]].push_back(i);
        for (int i = 1; i <= siz; ++i) res[i] = len[i];
    }
    void dfs(int u) {
        for (int v : g[u]) {
            dfs(v);
            f[u] = max(f[u], f[v]);
        }
    }
} sam;
class Solution {
public:
    int longestCommonSubpath(int N, vector<vector<int>>& paths) {
        sam.init();
        int ans = 0, m = paths.size();
        for (int& p : paths[0]) sam.extend(p);
        sam.build();
        for (int i = 1; i < m; ++i) sam.update(paths[i]);
        for (int i = 1; i <= sam.siz; ++i) ans = max(ans, sam.res[i]);
        return ans;
    }
};