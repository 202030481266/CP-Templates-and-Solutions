#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r
class Solution {
    vector<int> arr;
    vector<int> seg;
    vector<int> lazy;
public:
    void pushup(int rt) {
        seg[rt] = max(seg[ls], seg[rs]);
    }
    void pushdown(int rt) {
        if (lazy[rt] > 0) {
            seg[ls] = lazy[ls] = lazy[rt];
            seg[rs] = lazy[rs] = lazy[rt];
            lazy[rt] = 0;
        }
    }
    void update(int rt, int l, int r, int L, int R, int val) {
        if (L <= l && r <= R) {
            lazy[rt] = val;
            seg[rt] = val;  // 区间的取值变为区间最大值的叠加
            return;
        }
        pushdown(rt);
        if (R <= mid) update(lson, L, R, val);
        else if (L > mid) update(rson, L, R, val);
        else {
            update(lson, L, mid, val);
            update(rson, mid + 1, R, val);
        }
        pushup(rt);
    } 
    int query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return seg[rt];
        pushdown(rt);
        if (R <= mid) return query(lson, L, R);
        else if (L > mid) return query(rson, L, R);
        else return max(query(lson, L, mid), query(rson, mid + 1, R));
    }
    vector<int> fallingSquares(vector<vector<int>>& positions) {

        // 离散化
        for (auto& p : positions) {
            arr.emplace_back(p[0]);
            arr.emplace_back(p[0] + p[1] - 1);
        }
        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        for (auto& p : positions) {
            // 左右端点 [L, R)
            p.push_back(p[1]); // 记录高度
            p[1] = lower_bound(arr.begin(), arr.end(), p[0] + p[1] - 1) - arr.begin() + 1;
            p[0] = lower_bound(arr.begin(), arr.end(), p[0]) - arr.begin() + 1;
        }

        // 构建线段树
        int n = arr.size();
        seg.resize(arr.size() * 4);
        lazy.resize(arr.size() * 4);

        vector<int> ans;
        for (auto& p : positions) {
            int tmp = query(1, 1, n, p[0], p[1]);
            update(1, 1, n, p[0], p[1], p[2] + tmp);
            ans.push_back(seg[1]);
        }
        return ans;
    } 
};