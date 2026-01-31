#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r

static constexpr int maxn = 200005;

int n, q;
int a[maxn<<2], b[maxn<<2], arr[maxn];
int mx[maxn<<2], smx[maxn<<2];

void modify(int& ca, int& cb, int& cmx, int& csmx, int al, int bl, int& mxl, int& smxl, int ar, int br, int mxr, int smxr) {
    if (mxl == mxr) {
        ca = al + ar;
        cmx = mxl;
        csmx = max(smxl, smxr);
        cb = (csmx == smxl ? bl : 0) + (csmx == smxr ? br : 0);
    }
    else if (mxl > mxr) {
        cmx = mxl;
        ca = al;
        csmx = max(smxl, mxr);
        cb = (csmx == smxl ? bl : 0) + (csmx == mxr ? ar : 0);
    }
    else {
        cmx = mxr;
        ca = ar;
        csmx = max(smxr, mxl);
        cb = (csmx == smxr ? br : 0) + (csmx == mxl ? al : 0);
    }
}

void build(int rt, int l, int r) {
    if (l == r) {
        a[rt] = 1;
        mx[rt] = arr[l];
        return;
    }
    build(lson);
    build(rson);
    modify(a[rt], b[rt], mx[rt], smx[rt], a[ls], b[ls], mx[ls], smx[ls], a[rs], b[rs], mx[rs], smx[rs]);
}

void update(int rt, int l, int r, int p, int val) {
    if (l == r) {
        mx[rt] = val;
        return;
    }
    if (p <= mid) update(lson, p, val);
    else update(rson, p, val);
    modify(a[rt], b[rt], mx[rt], smx[rt], a[ls], b[ls], mx[ls], smx[ls], a[rs], b[rs], mx[rs], smx[rs]);
}

int qx, qy;
int qcx, qcy;

void query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        int nx, ny;
        int ncx, ncy;
        modify(ncx, ncy, nx, ny, qcx, qcy, qx, qy, a[rt], b[rt], mx[rt], smx[rt]);
        qx = nx;
        qy = ny;
        qcx = ncx;
        qcy = ncy;
        return;
    }
    if (R <= mid) query(lson, L, R);
    else if (L > mid) query(rson, L, R);
    else {
        query(lson, L, mid);
        query(rson, mid + 1, R);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    build(1, 1, n);
    for (int i = 1, op, p, x, l, r; i <= q; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> p >> x;
            update(1, 1, n, p, x);
        }
        else {
            qx = qy = 0;
            qcx = qcy = 0;
            cin >> l >> r;
            query(1, 1, n, l, r);
            cout << qcy << '\n';
        }
    }
    return 0;
}