#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 153000;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

int n, m, z, N;
int a[MAXN], b[MAXN], idx[MAXN];
int belong[MAXN];
int ans[MAXN];

struct Query {
    int l, r, id;
    Query(): l(0), r(0), id(-1) {}
    Query(int ql, int qr, int qid): l(ql), r(qr), id(qid) {}
    bool operator<(const Query& q) const {
        if (belong[l] != belong[q.l]) return belong[l] < belong[q.l];
        return belong[l] & 1 ? r < q.r : r > q.r;
    }
} qs[MAXN];

#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int sum[MAXN << 2], over[MAXN << 2], have[MAXN << 2];

void pushup(int rt) {
    int c = min(over[rs], have[ls]);
    sum[rt] = c + sum[ls] + sum[rs];
    over[rt] = over[ls] + over[rs] - c;
    have[rt] = have[ls] + have[rs] - c;
}

void build(int rt, int l, int r) {
    have[rt] = r - l + 1;
    if (l == r) return;
    build(lson);
    build(rson);
}

void add(int rt, int l, int r, int p) {
    if (p == 0) return;
    if (l == r) {
        if (have[rt]) {
            ++sum[rt];
            --have[rt];
        }
        else ++over[rt];
        return;
    }
    if (p <= mid) add(lson, p);
    else add(rson, p);
    pushup(rt);
}

void del(int rt, int l, int r, int p) {
    if (p == 0) return;
    if (l == r) {
        if (over[rt]) --over[rt];
        else {
            ++have[rt];
            --sum[rt];
        }
        return;
    }
    if (p <= mid) del(lson, p);
    else del(rson, p);
    pushup(rt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> z;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];
    int blen = INT(sqrt(m));
    for (int i = 1; i <= m; ++i) belong[i] = (i - 1) / blen + 1;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].id = i;
    }
    sort(qs + 1, qs + 1 + N);
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= m; ++i) idx[i] = INT(distance(a, upper_bound(a + 1, a + n + 1, z - b[i]))) - 1;
    int l = 1, r = 0;
    build(1, 1, n);
    for (int i = 1; i <= N; ++i) {
        int ql = qs[i].l, qr = qs[i].r, qid = qs[i].id;
        while (l < ql) del(1, 1, n, idx[l++]);
        while (l > ql) add(1, 1, n, idx[--l]);
        while (r > qr) del(1, 1, n, idx[r--]);
        while (r < qr) add(1, 1, n, idx[++r]);
        ans[qid] = sum[1];
    }
    for (int i = 1; i <= N; ++i) cout << ans[i] << '\n';
}