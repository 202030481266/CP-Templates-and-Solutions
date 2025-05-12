// https://codeforces.com/problemset/problem/601/E
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int P = 1e7 + 19;
const int mod = 1e9 + 7;
const int maxk = 1007;
const int maxn = 5007;
const int maxm = 30007;
const int N = maxn + maxm;

int n, m, q;
ll pw[maxk], dp[20][maxk];
int head[maxm<<2], to[N*20], nxt[N*20], eCnt = 0;
int ev[N], ew[N], st[N], ed[N];
int ans[maxm];

void addEdge(int rt, int eid) {
    to[eCnt] = eid;
    nxt[eCnt] = head[rt];
    head[rt] = eCnt++;
}

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r

void add(int rt, int l, int r, int L, int R, int eid) {
    if (L <= l && r <= R) {
        addEdge(rt, eid);
        return;
    }
    if (R <= mid) add(lson, L, R, eid);
    else if (L > mid) add(rson, L, R, eid);
    else {
        add(lson, L, mid, eid);
        add(rson, mid+1, R, eid);
    }
}
void dfs(int rt, int l, int r, int d) {
    for (int i = 1; i <= m; ++i) dp[d][i] = dp[d-1][i];
    for (int i = head[rt]; ~i; i = nxt[i]) {
        int x = to[i];
        for (int j = m; j >= ew[x]; --j) {
            dp[d][j] = max(dp[d][j], dp[d][j-ew[x]] + ev[x]);
        }
    }
    if (l == r) {
        if (ans[l]) {
            ll res = 0;
            for (int i = 1; i <= m; ++i) {
                res = (res + dp[d][i] * pw[i-1] % mod) % mod;
            }
            cout << res << '\n';
        }
    }
    else {
        dfs(lson, d+1);
        dfs(rson, d+1);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    memset(head, -1, sizeof(head));
    pw[0] = 1;
    for (int i = 1; i <= m; ++i) pw[i] = pw[i-1] * P % mod;
    for (int i = 1; i <= n; ++i) {
        cin >> ev[i] >> ew[i];
    }
    cin >> q;
    for (int i = 1; i <= n; ++i) ed[i] = q;
    for (int i = 1, op, eid; i <= q; ++i) {
        cin >> op;
        if (op == 1) {
            ++n;
            cin >> ev[n] >> ew[n];
            st[n] = i;
            ed[n] = q;
        }
        else if (op == 2) {
            cin >> eid;
            ed[eid] = i;
        }
        else {
            ans[i] = 1;
        }
    }
    for (int i = 1; i <= n; ++i) {
        add(1, 0, q, st[i], ed[i], i);
    }
    dfs(1, 0, q, 1);
}

