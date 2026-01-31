#define ls rt<<1
#define rs rt<<1|1
#define mid ((l + r) >> 1)
#define lson ls,l,mid
#define rson rs,mid + 1, r
class Solution {
    static constexpr int mod = 1e9 + 7;
    typedef long long ll;
public:
    vector<int> bonus(int n, vector<vector<int>>& leadership, vector<vector<int>>& operations) {
        // [1, n]
        vector<int> g[n + 1];
        vector<ll> a(n * 4), laz(n * 4); 
        vector<int> dfn(n + 1), siz(n + 1);

        for (auto& e : leadership) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        int tot = 0;

        function<void(int,int)> dfs = [&](int u, int fa) {
            dfn[u] = ++tot;
            siz[u] = 1;
            for (int& v : g[u]) {
                if (v != fa) {
                    dfs(v, u);
                    siz[u] += siz[v];
                }
            }
        };

        dfs(1, 0);

        function<void(int,int,int)> pushdown = [&](int rt, int l, int r) {
            if (laz[rt]) {
                laz[ls] = (laz[ls] + laz[rt]) % mod;
                laz[rs] = (laz[rs] + laz[rt]) % mod;
                a[ls] = (a[ls] + (mid - l + 1) * laz[rt]) % mod;
                a[rs] = (a[rs] + (r - mid) * laz[rt]) % mod;
                laz[rt] = 0;
            }
        };

        function<void(int,int,int,int,int,int)> update = [&](int rt, int l, int r, int L, int R, int val) {
            if (L <= l && r <= R) {
                laz[rt] = (laz[rt] + val) % mod;
                a[rt] = (a[rt] + val * (r - l + 1)) % mod;  // 注意这里需要乘上区间长度，不然就真的傻逼啊！
                return;
            }
            pushdown(rt, l, r);
            if (R <= mid) update(lson, L, R, val);
            else if (L > mid) update(rson, L, R, val);
            else {
                update(lson, L, mid, val);
                update(rson, mid + 1, R, val);
            }
            a[rt] = (a[ls] + a[rs]) % mod;
        };

        function<ll(int,int,int,int,int)> query = [&](int rt, int l, int r, int L, int R) -> ll {
            if (L <= l && r <= R) {
                return a[rt];
            }
            pushdown(rt, l, r);
            if (R <= mid) return query(lson, L, R);
            else if (L > mid) return query(rson, L, R);
            else return (query(lson, L, mid) + query(rson, mid + 1, R)) % mod;
        };

        vector<int> ans; 

        for (auto& op : operations) {
            int x = dfn[op[1]];
            if (op[0] == 1) {
                update(1, 1, n, x, x, op[2]);
            }
            else if (op[0] == 2) {
                update(1, 1, n, x, x + siz[op[1]] - 1, op[2]);
            }
            else {
                ans.push_back(query(1, 1, n, x, x + siz[op[1]] - 1));
            }
        }

        return ans;
    }
};