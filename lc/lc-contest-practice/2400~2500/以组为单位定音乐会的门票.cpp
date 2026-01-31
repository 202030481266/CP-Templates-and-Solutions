#define ls rt*2
#define rs rt*2+1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r
typedef long long ll;
class BookMyShow {
    static constexpr int N = 50010;
    int a[N], M, mx[N * 4], p = 1;
    ll sum[N * 4], n;
public:
    void pushup(int rt) {
        mx[rt] = max(mx[ls], mx[rs]);
        sum[rt] = sum[ls] + sum[rs];
    }
    void modify(int rt, int l, int r, int p, int val) {
        if (l == r) {
            a[l] = mx[rt] = sum[rt] = val;
            return;
        }
        if (p <= mid) modify(lson, p, val);
        else modify(rson, p, val);
        pushup(rt);
    }
    int query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return mx[rt];
        if (R <= mid) return query(lson, L, R);
        else if (L > mid) return query(rson, L, R);
        else return max(query(lson, L, mid), query(rson, mid + 1, R));
    }
    ll Query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return sum[rt];
        if (R <= mid) return Query(lson, L, R);
        else if (L > mid) return Query(rson, L, R);
        else return Query(lson, L, mid) + Query(rson, mid + 1, R);
    }
    BookMyShow(int N, int m) {
        M = m;
        n = N;
        for (int i = 1; i <= n; ++i)
            modify(1, 1, n, i, m);
    }
    
    vector<int> gather(int k, int maxRow) {
        int L = p, R = maxRow + 1, ans = -1;
        while (L <= R) {
            int m = (L + R) >> 1;
            if (query(1, 1, n, p, m) >= k) ans = m, R = m - 1;
            else L = m + 1;
        }
        if (ans == -1) return {};
        vector<int> res{ans - 1, M - a[ans]};
        modify(1, 1, n, ans, a[ans] - k);
        return res;
    }
    
    bool scatter(int k, int maxRow) {
        int L = p, R = maxRow + 1, res = -1;
        while (L <= R) {
            int m = (L + R) >> 1;
            if (Query(1, 1, n, p, m) >= 1ll * k) res = m, R = m - 1;
            else L = m + 1;
        }
        if (res == -1) return false;
        for (int i = p; i <= res; ++i) {
            if (a[i] <= k) {
                k -= a[i];
                modify(1, 1, n, i, 0);
            }
            else {
                modify(1, 1, n, i, a[i] - k);
            }
        }
        if (a[res] == 0) p = res + 1;
        else p = res;
        return true;
    }
};

/**
 * Your BookMyShow object will be instantiated and called as such:
 * BookMyShow* obj = new BookMyShow(n, m);
 * vector<int> param_1 = obj->gather(k,maxRow);
 * bool param_2 = obj->scatter(k,maxRow);
 */