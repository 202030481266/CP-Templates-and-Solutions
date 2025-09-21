#include <bits/stdc++.h>

using namespace std;

static constexpr int MAXN = 30004;
static constexpr int MAXM = 200005;

int n, m, arr[MAXN], disc[MAXN];
int belong[MAXN], bl[MAXN], br[MAXN];
int cnt[MAXN], ans[MAXM];

struct Query {
    int l, r, id;
    Query(): l(0), r(0), id(0) {}
    Query(int ql, int qr, int qid): l(ql), r(qr), id(qid) {}
    bool operator < (const Query& q) const {
        if (belong[l] != belong[q.l]) {
            return belong[l] < belong[q.l];
        }
        // 奇偶排序优化一下常数
        if (belong[l] & 1) return r < q.r;
        return r > q.r;
    }
} queries[MAXM];

int kind = 0;

void del(int val) {
    --cnt[val];
    if (cnt[val] == 0) --kind;
}

void add(int val) {
    ++cnt[val];
    if (cnt[val] == 1) ++kind;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }
    int blen = sqrt(n), bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= bnum; ++i) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(n, i * blen);
        for (int j = bl[i]; j <= br[i]; ++j) belong[j] = i;
    }
    sort(queries + 1, queries + m + 1);
    for (int i = 1; i <= n; ++i) disc[i] = arr[i];
    sort(disc + 1, disc + n + 1);
    int len = unique(disc + 1, disc + n + 1) - disc - 1;
    for (int i = 1; i <= n; ++i) arr[i] = lower_bound(disc + 1, disc + len + 1, arr[i]) - disc; // NOLINT(*-narrowing-conversions)
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        int ql = queries[i].l, qr = queries[i].r, qid = queries[i].id;
        while (l > ql) add(arr[--l]);
        while (l < ql) del(arr[l++]);
        while (r > qr) del(arr[r--]);
        while (r < qr) add(arr[++r]);
        ans[qid] = kind;
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}