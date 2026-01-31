// https://atcoder.jp/contests/joisc2014/tasks/joisc2014_c
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 200005;

int n, m, arr[MAXN], b[MAXN];
int belong[MAXN], bl[MAXN], br[MAXN];

struct Query {
    int l, r, id;

    Query(): l(0), r(0), id(0) {}
    Query(int _l, int _r, int _id): l(_l), r(_r), id(_id) {}

    bool operator<(const Query& q) const {
        if (belong[l] != belong[q.l]) return belong[l] < belong[q.l];
        return r < q.r;
    }
} qs[MAXN];

int cnt[MAXN];
ll ans[MAXN], last;

void update(int l, int r, int qid) { // use to scan and calculate and update the ans[qid]
    for (int i = l; i <= r; ++i) {
        ++cnt[arr[i]];
        ans[qid] = max(ans[qid], 1ll * cnt[arr[i]] * b[arr[i]]);
    }
    for (int i = l; i <= r; ++i) --cnt[arr[i]];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        b[i] = arr[i];
    }
    for (int i = 1, l, r; i <= m; ++i) {
        cin >> l >> r;
        qs[i] = Query(l, r, i);
    }
    sort(b + 1, b + 1 + n);
    int len = static_cast<int>(unique(b + 1, b + 1 + n) - b - 1);
    for (int i = 1; i <= n; ++i) arr[i] = static_cast<int>(lower_bound(b + 1, b + 1 + len, arr[i]) - b);
    int blen = static_cast<int>(sqrt(n)), bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= bnum; ++i) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(n, i * blen);
        for (int j = bl[i]; j <= br[i]; ++j) belong[j] = i;
    }
    sort(qs + 1, qs + 1 + m);
    int p = 1;
    while (p <= m) {
        int i = p, block = belong[qs[p].l], r = br[block];
        last = 0;
        fill(cnt + 1, cnt + 1 + len, 0);
        while (i <= m && belong[qs[i].l] == block) {
            if (qs[i].r <= br[block]) { // at the same block so we'd better calculate directly
                update(qs[i].l, qs[i].r, qs[i].id);
            }
            else {
                while (r < qs[i].r) {
                    ++cnt[arr[++r]];
                    last = max(last, 1ll * cnt[arr[r]] * b[arr[r]]);
                }
                ans[qs[i].id] = last;
                update(qs[i].l, br[block], qs[i].id);
            }
            ++i;
        }
        p = i;
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}