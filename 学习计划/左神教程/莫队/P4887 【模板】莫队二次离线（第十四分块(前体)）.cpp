#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int MAXN = 100000 + 5;
static constexpr int MAXV = 1 << 14; // 16384
static constexpr int MAXE = 500000 + 5;

int n, m, k, arr[MAXN];
int bl[MAXN], br[MAXN], belong[MAXN];
int head[2][MAXN + 5];
int nxt[2][MAXE], to_l[2][MAXE], to_r[2][MAXE], to_qid[2][MAXE], to_op[2][MAXE], tot[2];
int kones[MAXV], klen = 0;
ll cnt[MAXV];
ll pre[MAXN], suf[MAXN], ans[MAXN];

struct Query {
    int l, r, id;
    Query(): l(0), r(0), id(0) {}
    Query(int _l, int _r, int _id): l(_l), r(_r), id(_id) {}
    bool operator<(const Query& q) const {
        if (belong[l] != belong[q.l]) return belong[l] < belong[q.l];
        return r < q.r;
    }
} qs[MAXN];

void addEdge(int idx, int u, int ql, int qr, int qid, int qop) {
    ++tot[idx];
    to_l[idx][tot[idx]] = ql;
    to_r[idx][tot[idx]] = qr;
    to_qid[idx][tot[idx]] = qid;
    to_op[idx][tot[idx]] = qop;
    nxt[idx][tot[idx]] = head[idx][u];
    head[idx][u] = tot[idx];
}

void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= m; ++i) {
        int l, r; cin >> l >> r;
        qs[i] = Query(l, r, i);
    }
    for (int i = 0; i < MAXV; ++i) {
        if (__builtin_popcount(i) == k) kones[++klen] = i;
    }
    pre[0] = 0;
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + cnt[arr[i]];
        for (int j = 1; j <= klen; ++j) ++cnt[arr[i] ^ kones[j]];
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = n; i >= 1; --i) {
        suf[i] = suf[i + 1] + cnt[arr[i]];
        for (int j = 1; j <= klen; ++j) ++cnt[arr[i] ^ kones[j]];
    }
    int blen = max(1, (int)sqrt(n));
    int bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= bnum; ++i) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(n, i * blen);
        for (int j = bl[i]; j <= br[i]; ++j) belong[j] = i;
    }
    sort(qs + 1, qs + 1 + m);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        int ql = qs[i].l, qr = qs[i].r, qid = qs[i].id;
        if (r < qr) {
            addEdge(0, l - 1, r + 1, qr, qid, -1);
            ans[qid] += pre[qr] - pre[r];
        }
        if (r > qr) {
            addEdge(0, l - 1, qr + 1, r, qid, 1);
            ans[qid] -= pre[r] - pre[qr];
        }
        r = qr;
        if (l > ql) {
            addEdge(1, r + 1, ql, l - 1, qid, -1);
            ans[qid] += suf[ql] - suf[l];
        }
        if (l < ql) {
            addEdge(1, r + 1, l, ql - 1, qid, 1);
            ans[qid] -= suf[l] - suf[ql];
        }
        l = ql;
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i <= n; ++i) {
        if (i > 0) {
            for (int j = 1; j <= klen; ++j) ++cnt[arr[i] ^ kones[j]];
        }
        for (int x = head[0][i]; x; x = nxt[0][x]) {
            int L = to_l[0][x], R = to_r[0][x], qid = to_qid[0][x], op = to_op[0][x];
            for (int j = L; j <= R; ++j) {
                ans[qid] += cnt[arr[j]] * op;
            }
        }
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = n + 1; i >= 1; --i) {
        if (i <= n) {
            for (int j = 1; j <= klen; ++j) ++cnt[arr[i] ^ kones[j]];
        }
        for (int x = head[1][i]; x; x = nxt[1][x]) {
            int L = to_l[1][x], R = to_r[1][x], qid = to_qid[1][x], op = to_op[1][x];
            for (int j = L; j <= R; ++j) {
                ans[qid] += cnt[arr[j]] * op;
            }
        }
    }
    for (int i = 2; i <= m; ++i) {
        ans[qs[i].id] += ans[qs[i - 1].id];
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}

int main() {
    solve();
    return 0;
}