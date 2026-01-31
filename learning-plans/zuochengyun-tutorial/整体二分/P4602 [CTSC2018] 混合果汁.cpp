// https://www.luogu.com.cn/problem/P4602
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const ll inf = 1e18;

static constexpr int maxn = 100007;
int n, m, U, D;
int qid[maxn];
int lstk[maxn], rstk[maxn], lsiz, rsiz;
ll qG[maxn], qL[maxn];
int ans[maxn];

struct juice {
    int d, p, l;
    bool operator<(const juice& rhs) const {
        return d > rhs.d;
    }
} arr[maxn];

// segment tree to support fast search
#define ls rt<<1
#define rs rt<<1|1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid+1, r
ll sum[maxn<<2], cost[maxn<<2];

void pushup(int rt) {
    sum[rt] = sum[ls] + sum[rs];
    cost[rt] = cost[ls] + cost[rs];
}
void update(int rt, int l, int r, int price, int limit) {
    if (l == r) {
        sum[rt] += limit;
        cost[rt] += 1ll * limit * price;
       	return;
    }
    if (price <= mid) update(lson, price, limit);
    else update(rson, price, limit);
    pushup(rt);
}
ll query(int rt, int l, int r, ll volumn) {
    if (sum[rt] < volumn) return inf; // impossible
    if (l == r) return volumn * l;
    if (sum[ls] >= volumn) return query(lson, volumn);
    else return cost[ls] + query(rson, volumn - sum[ls]);
}
int ptr = 1;
void dfs(int ql, int qr, int vl, int vr) {
	if (ql > qr) return;
    int vmid = (vl + vr) / 2;
    while (ptr <= n && arr[ptr].d >= vmid) {
        update(1, 1, U, arr[ptr].p, arr[ptr].l);
        ++ptr;
    }
    while (ptr > 1 && arr[ptr-1].d < vmid) {
        --ptr;
        update(1, 1, U, arr[ptr].p, -arr[ptr].l);
    }
    lsiz = rsiz = 0;
    for (int i = ql; i <= qr; ++i) {
        int id = qid[i];
        ll min_cost = query(1, 1, U, qL[id]);
        if (min_cost <= qG[id]) {
            lstk[lsiz++] = id;
            ans[id] = vmid;
        }
        else {
            rstk[rsiz++] = id;
        }
    }
    if (vl == vr) return;
    for (int i = ql; i < ql + lsiz; ++i) qid[i] = lstk[i-ql];
    for (int i = ql + lsiz; i <= qr; ++i) qid[i] = rstk[i-(ql+lsiz)];
    int len = lsiz;
    dfs(ql, ql + len - 1, vmid + 1, vr);
    dfs(ql + len, qr, vl, vmid);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i].d >> arr[i].p >> arr[i].l;
        U = max(U, arr[i].p);
        D = max(D, arr[i].d);
    }
    for (int i = 1; i <= m; ++i) {
        cin >> qG[i] >> qL[i];
    }
    sort(arr + 1, arr + 1 + n);
    for (int i = 1; i <= m; ++i) qid[i] = i;
    memset(ans, -1, sizeof(ans));
    dfs(1, m, 1, D);
    for (int i = 1; i <= m; ++i) {
        cout << ans[i] << '\n';
    }
}