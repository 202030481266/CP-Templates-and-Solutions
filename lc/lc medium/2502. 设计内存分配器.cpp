#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// segment tree，最优解
// 使用并查集的方法也可以，速度也很快

const int maxn = 1007;
struct node {
    int l_s, r_s, sum, ms, lazy;
} tree[maxn<<2];

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid+1, r

void pushup(int rt, int l, int r) {
    tree[rt].sum = tree[ls].sum + tree[rs].sum;
    if (tree[ls].sum == mid-l+1) tree[rt].l_s = tree[ls].sum + tree[rs].l_s;
    else tree[rt].l_s = tree[ls].l_s;
    if (tree[rs].sum == r-mid) tree[rt].r_s = tree[rs].sum + tree[ls].r_s;
    else tree[rt].r_s = tree[rs].r_s;
    tree[rt].ms = max(max(tree[rt].l_s, tree[rt].r_s), max(tree[ls].ms, tree[rs].ms));
    if (tree[ls].r_s + tree[rs].l_s > tree[rt].ms) tree[rt].ms = tree[ls].r_s + tree[rs].l_s;
}

void flip(int rt, int l, int r) {
    if (tree[rt].sum == r-l+1) {
        tree[rt].sum = tree[rt].l_s = tree[rt].r_s = tree[rt].ms = 0;
    }
    else tree[rt].sum = tree[rt].l_s = tree[rt].r_s = tree[rt].ms = r-l+1;
}

void pushdown(int rt, int l, int r) {
    if (tree[rt].lazy) { // 需要翻转
        tree[ls].lazy ^= 1;
        tree[rs].lazy ^= 1;
        // 翻转
        flip(ls, l, mid);
        flip(rs, mid+1, r);
        tree[rt].lazy = 0;
    }
}

void build(int rt, int l, int r) {
    tree[rt].l_s = tree[rt].r_s = tree[rt].sum = tree[rt].ms = r-l+1;
    tree[rt].lazy = 0;
    if (l == r) return;
    build(lson);
    build(rson);
    pushup(rt, l, r);
}

int query(int rt, int l, int r, int k) {
    if (l == r) return l;
    pushdown(rt, l, r);
    if (tree[ls].ms >= k) return query(lson, k);
    else {
        if (tree[ls].r_s + tree[rs].l_s >= k && tree[ls].r_s >= 0) return mid - tree[ls].r_s + 1;
        else return query(rson, k);
    }
}

void update(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        flip(rt, l, r);
        tree[rt].lazy ^= 1;
        return;
    }
    pushdown(rt, l, r);
    if (R <= mid) update(lson, L, R);
    else if (L > mid) update(rson, L, R);
    else {
        update(lson, L, mid);
        update(rson, mid+1, R);
    }
    pushup(rt, l, r);
}

class Allocator {
public:
    vector<vector<int>> mp;
    vector<vector<int>> ps;
    int n;
    Allocator(int N) {
        n = N;
        build(1, 1, n);
        mp.resize(1001);
        ps.resize(1001);
    }
    
    int allocate(int size, int mID) {
        if (tree[1].ms < size) return -1;
        int pos = query(1, 1, n, size);
        mp[mID].push_back(size);
        ps[mID].push_back(pos);
        update(1, 1, n, pos, pos+size-1);
        return pos-1;
    }
    
    int freeMemory(int mID) {
        int sz = 0;
        for (int i = 0; i < mp[mID].size(); ++i) {
            update(1, 1, n, ps[mID][i], ps[mID][i]+mp[mID][i]-1);
            sz += mp[mID][i];
        }
        mp[mID].clear();
        ps[mID].clear();
        return sz;
    }
};