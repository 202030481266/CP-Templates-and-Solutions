#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int MAXN = 200005;
static constexpr int MAXM = 200005;

int n, m, k, arr[MAXN], disc[MAXN];
int belong[MAXN], bl[MAXN], br[MAXN];
int cnt[1 << 20];
int ans[MAXM];

int cur, tot_q, tot_u;
int record[MAXM][2];

struct Query {
    int l, r, id, tim;
    Query(): l(0), r(0), id(0), tim(0) {}
    Query(int ql, int qr, int qid, int qtim): l(ql), r(qr), id(qid), tim(qtim) {}
    bool operator < (const Query& q) const {
        if (belong[l] != belong[q.l]) {
            return belong[l] < belong[q.l];
        }
        if (belong[r] != belong[q.r]) {
            return belong[r] < belong[q.r];
        }
        return tim < q.tim;
    }
} queries[MAXM];

int kind = 0;

void del(int val) {
    --cnt[val];
    if (cnt[val] == 0) --kind;
    if (cnt[val] == 1) ++kind;
}

void add(int val) {
    ++cnt[val];
    if (cnt[val] == 1) ++kind;
    if (cnt[val] == 2) --kind;
}

void move(int l, int r, int tim) {
    int p = record[tim][0], v = record[tim][1];
    if (l <= p && p <= r) {
        del(arr[p]);
        add(v);
    }
    swap(arr[p], record[tim][1]); // 方便回溯重新构建，相当于借书还书
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1, op, pos, new_val, l, r; i <= m; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> pos >> new_val;
            ++pos;
            record[++tot_u][0] = pos;
            record[tot_u][1] = new_val;
        }
        else {
            ++tot_q;
            cin >> l >> r;
            queries[tot_q] = Query(l + 1, r + 1, tot_q, tot_u);
        }
    }
    int blen = max(1, static_cast<int>(pow(n, 2.0 / 3))), bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= bnum; ++i) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(n, i * blen);
        for (int j = bl[i]; j <= br[i]; ++j) belong[j] = i;
    }
    sort(queries + 1, queries + tot_q + 1);
    int l = 1, r = 0, t = 0;
    for (int i = 1; i <= tot_q; ++i) {
        int ql = queries[i].l, qr = queries[i].r, qid = queries[i].id, qt = queries[i].tim;
        while (l > ql) add(arr[--l]);
        while (l < ql) del(arr[l++]);
        while (r > qr) del(arr[r--]);
        while (r < qr) add(arr[++r]);
        while (t > qt) move(ql, qr, t--);
        while (t < qt) move(ql, qr, ++t);
        ans[qid] = kind;
    }
    for (int i = 1; i <= tot_q; ++i) cout << ans[i] << '\n';
}