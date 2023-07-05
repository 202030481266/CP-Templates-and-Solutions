// 懒修改线段树
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r
typedef long long ll;
class Fancy {
    static constexpr int mod = 1e9 + 7;
    static constexpr int N = 100010;
    ll add[N * 4], mul[N * 4], n;
public:
    Fancy() {
        n = 0;
        fill(add, add + N * 4, 0);
        fill(mul, mul + N * 4, 1);
    }
    void pushdown(int rt) {
        if (mul[rt] != 1) {
            mul[ls] = (mul[ls] * mul[rt]) % mod; 
            add[ls] = (add[ls] * mul[rt]) % mod;
            mul[rs] = (mul[rs] * mul[rt]) % mod; 
            add[rs] = (add[rs] * mul[rt]) % mod;
            mul[rt] = 1;
        }
        if (add[rt] > 0) {
            add[ls] = (add[ls] + add[rt]) % mod;
            add[rs] = (add[rs] + add[rt]) % mod;
            add[rt] = 0;
        }
    }
    void update(int rt, int l, int r, int L, int R, int val, int type) {
        if (L <= l && r <= R) {
            if (type == 1) { // 加法
                add[rt] = (add[rt] + val) % mod;
            }
            else {
                mul[rt] = (mul[rt] * val) % mod;
                add[rt] = (add[rt] * val) % mod;
            }
            return;
        }
        pushdown(rt);
        if (R <= mid) update(lson, L, R, val, type);
        else if (L > mid) update(rson, L, R, val, type);
        else {
            update(lson, L, mid, val, type);
            update(rson, mid + 1, R, val, type);
        }
    }
    ll query(int rt, int l, int r, int p) {
        if (l == r) 
            return add[rt];
        pushdown(rt);
        if (p <= mid) return query(lson, p);
        else return query(rson, p);
    }
    void append(int val) {
        ++n;
        update(1, 1, 100000, n, n, val, 1);
    }
    void addAll(int inc) {
        if (n == 0) return;
        update(1, 1, 100000, 1, n, inc, 1);
    }

    void multAll(int m) {
        if (n == 0) return;
        update(1, 1, 100000, 1, n, m, 2);
    }

    int getIndex(int idx) {
        ++idx;
        if (idx > n) return -1;
        return query(1, 1, 100000, idx);
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */