// https://www.luogu.com.cn/problem/P4137
// 最优解是主席树，但是这里使用回滚莫队也可以做

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
        return r > q.r; // desc order
    }
} qs[MAXN];

int cnt[MAXN], ans[MAXN], mex;

void update(int l, int r, int qid) {
    for (int i = l; i < r; ++i) {
        --cnt[arr[i]];
        if (cnt[arr[i]] == 0) ans[qid] = min(ans[qid], arr[i]);
    }
    for (int i = l; i < r; ++i) ++cnt[arr[i]];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
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
    for (int i = 1; i <= n; ++i) ++cnt[arr[i]];
    while (cnt[mex]) ++mex;
    while (p <= m) {
        int i = p, block = belong[qs[p].l];
        while (gl < bl[block]) {
            --cnt[arr[gl]];
            if (cnt[arr[gl]] == 0) mex = min(mex, arr[gl]);
            ++gl;
        }
        int last = mex, r = n;
        while (i <= m && belong[qs[i].l] == block) {
            while (r > qs[i].r) {
                --cnt[arr[r]];
                if (cnt[arr[r]] == 0) last = min(last, arr[r]);
                --r;
            }
            ans[qs[i].id] = last;
            update(bl[block], qs[i].l, qs[i].id);
            ++i;
        }
        while (r < n) ++cnt[arr[++r]];
        p = i;
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}