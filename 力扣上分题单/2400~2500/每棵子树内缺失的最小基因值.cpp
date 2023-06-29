struct q {
    int l, r, id;
    q(int _l, int _r, int _id): l(_l), r(_r), id(_id) {}
};
class Solution {
    static constexpr int N = 100000, K = 317;
    int dfn[N + 1], ref[N + 1], a[N + 1], belong[N + 1], siz[N + 1];
    int cnt[N + 1], num[K + 1], tot = 1;
public:
    void add(int x) {
        if (!cnt[x]) num[x / K]++;
        ++cnt[x];
    }
    void del(int x) {
        if (cnt[x] == 1) num[x / K]--;
        --cnt[x];
    }
    int query() {
        for (int i = 1; i <= K; ++i) {
            if (num[i - 1] != K) {
                for (int j = (i - 1) * K; j < i * K; ++j)
                    if (!cnt[j]) return j;
            }
        }
        return 0;
    }
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        // 区间Mex问题
        int n = parents.size();
        vector<int> g[n];
        for (int i = 1; i < n; ++i) g[parents[i]].push_back(i);
        function<void(int)> dfs = [&](int u) {
            dfn[u] = tot;
            ref[tot] = u;
            ++tot;
            siz[u] = 1;
            for (int v : g[u]) {
                dfs(v);
                siz[u] += siz[v];
            }
        };
        dfs(0);
        // 莫队
        for (int i = 1; i <= n; ++i) a[i] = nums[ref[i]] - 1;
        int len = sqrt(n);
        for (int i = 1; i <= n; ++i) belong[i] = (i - 1) / len + 1;
        vector<q> interval; 
        for (int i = 0; i < n; ++i) interval.emplace_back(dfn[i], dfn[i] + siz[i] - 1, i);
        sort(interval.begin(), interval.end(), [&](q& A, q& B){
            if (belong[A.l] == belong[B.l]) return A.r < B.r;
            else return belong[A.l] < belong[B.l];
        });
        int l = interval[0].l, r = interval[0].r;
        vector<int> ans(n);
        for (int i = l; i <= r; ++i) add(a[i]);
        ans[interval[0].id] = query() + 1;
        for (int i = 1; i < n; ++i) {
            while (l < interval[i].l) del(a[l++]);
            while (l > interval[i].l) add(a[--l]);
            while (r < interval[i].r) add(a[++r]);
            while (r > interval[i].r) del(a[r--]);
            ans[interval[i].id] = query() + 1;
        }
        return ans;
    }
};