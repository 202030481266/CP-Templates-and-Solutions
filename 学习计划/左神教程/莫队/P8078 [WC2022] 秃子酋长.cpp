// https://www.luogu.com.cn/problem/P8078

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 500005;

int n, m, arr[MAXN], b[MAXN], pre[MAXN], nxt[MAXN], pos[MAXN];
int belong[MAXN], bl[MAXN], br[MAXN];

struct Query {
    int l, r, id;

    Query(): l(0), r(0), id(0) {}
    Query(int _l, int _r, int _id): l(_l), r(_r), id(_id) {}

    bool operator<(const Query& q) const {
        if (belong[l] != belong[q.l]) return belong[l] < belong[q.l];
        return r > q.r; // desc order
    }
} qs[MAXN];

ll ans[MAXN], sum, last;

void del(int i, ll& s) {
    if (pre[i]) {
        nxt[pre[i]] = nxt[i];
        s -= abs(i - pre[i]);
    }
    if (nxt[i]) {
        pre[nxt[i]] = pre[i];
        s -= abs(i - nxt[i]);
    }
    if (pre[i] && nxt[i]) s += abs(nxt[i] - pre[i]);
}

void add(int i, ll& s) {
    if (pre[i] && nxt[i]) s -= abs(nxt[i] - pre[i]);
    if (nxt[i]) {
        pre[nxt[i]] = i;
        s += abs(nxt[i] - i);
    }
    if (pre[i]) {
        nxt[pre[i]] = i;
        s += abs(pre[i] - i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        pos[arr[i]] = i; // 1 ~ n
    }
    for (int i = 1; i <= n; ++i) {
        pre[i] = pos[arr[i] - 1];
        nxt[i] = pos[arr[i] + 1];
    }
    for (int i = 1, l, r; i <= m; ++i) {
        cin >> l >> r;
        qs[i] = Query(l, r, i);
    }
    int blen = static_cast<int>(sqrt(n)), bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= bnum; ++i) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(n, i * blen);
        for (int j = bl[i]; j <= br[i]; ++j) belong[j] = i;
    }
    sort(qs + 1, qs + 1 + m);
    int p = 1, gl = 1;
    for (int i = 1; i <= n; ++i) {
        if (pre[i]) sum += abs(i - pre[i]);
    }
    while (p <= m) {
        int i = p, block = belong[qs[p].l];
        while (gl < bl[block]) del(gl++, sum);
        int r = n;
        last = sum;
        while (i <= m && belong[qs[i].l] == block) {
            while (r > qs[i].r) del(r--, last);
            for (int k = bl[block]; k < qs[i].l; ++k) del(k, last);
            ans[qs[i].id] = last;
            for (int k = qs[i].l - 1; k >= bl[block]; --k) add(k, last);
            ++i;
        }
        while (r < n) add(++r, last);
        assert(last == sum); // validate
        p = i;
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}
