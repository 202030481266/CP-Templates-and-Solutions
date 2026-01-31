#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int MAXN = 100005;
static constexpr int MAXM = 100005;

int n, m, k, arr[MAXN], disc[MAXN];
int belong[MAXN], bl[MAXN], br[MAXN];
ll cnt[1 << 20];
ll ans[MAXM];

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

ll cur = 0;

void del(int val) {
    if (k) cur -= cnt[val ^ k];
    else cur -= cnt[val] - 1;
    --cnt[val];
}

void add(int val) {
    if (k) cur += cnt[val ^ k];
    else cur += cnt[val];
    ++cnt[val];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) arr[i] ^= arr[i - 1];
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
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        int ql = queries[i].l, qr = queries[i].r, qid = queries[i].id;
        while (l > ql) add(arr[--l]);
        while (l < ql) del(arr[l++]);
        while (r > qr) del(arr[r--]);
        while (r < qr) add(arr[++r]);
        ans[qid] = cur + cnt[arr[l - 1] ^ k];
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}