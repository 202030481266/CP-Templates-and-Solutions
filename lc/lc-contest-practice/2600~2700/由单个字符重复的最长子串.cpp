// 卡空间卡死了
// 两种思路： 线段树+最大连续子段和, 平衡树维护线段结构体（合并和分割）
// 最大子段和问题
#define lc rt<<1
#define rc rt<<1|1
#define mid ((l + r) >> 1)
#define lson lc, l, mid
#define rson rc, mid + 1, r
static constexpr int maxn = 100001;
int ls[maxn << 2][26], rs[maxn << 2][26], sum[maxn << 2][26], ms[maxn << 2][26];
class Solution {
public:
    void pushup(int rt, int l, int r, int id) {
        sum[rt][id] = sum[lc][id] + sum[rc][id];
        // 更新左端点连续最大和
        if (sum[lc][id] == (mid - l + 1))  // 左边全部是 1
            ls[rt][id] = sum[lc][id] + ls[rc][id];
        else ls[rt][id] = ls[lc][id];
        // 更新右端点的连续最大和
        if (sum[rc][id] == (r - mid))  // 右边全部是1
            rs[rt][id] = sum[rc][id] + rs[lc][id];
        else rs[rt][id] = rs[rc][id];
        ms[rt][id] = max(max(ms[lc][id], ms[rc][id]), rs[lc][id] + ls[rc][id]);
    }
    void update(int rt, int l, int r, int id, int p, int val) {
        if (l == r) {
            ls[rt][id] = rs[rt][id] = sum[rt][id] = ms[rt][id] = val;
            return;
        }
        if (p <= mid) update(lson, id, p, val);
        else update(rson, id, p, val);
        pushup(rt, l, r, id);
    }
    vector<int> longestRepeating(string s, string c, vector<int>& a) {
        int n = s.size(), m = a.size();
        memset(ls, 0, sizeof(ls));
        memset(rs, 0, sizeof(ls));
        memset(sum, 0, sizeof(ls));
        memset(ms, 0, sizeof(ls));
        for (int i = 0; i < n; ++i) {
            update(1, 1, n, s[i] - 'a', i + 1, 1);
        }
        vector<int> ans;
        for (int i = 0; i < m; ++i) {
            update(1, 1, n, s[a[i]] - 'a', a[i] + 1, 0);
            update(1, 1, n, c[i] - 'a', a[i] + 1, 1);
            s[a[i]] = c[i];
            int tmp = 0;
            for (int j = 0; j < 26; ++j)
                tmp = max(tmp, ms[1][j]);
            ans.push_back(tmp);
        }
        return ans;
    }
};