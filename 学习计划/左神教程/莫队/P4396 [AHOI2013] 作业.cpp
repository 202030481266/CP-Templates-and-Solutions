#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 100003;
static constexpr int MAXB = 320;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

int n, m, arr[MAXN];
int belong1[MAXN], bl[MAXB], br[MAXB]; // 值域分块
int belong2[MAXN];
int ans1[MAXN], ans2[MAXN], cnt[MAXN], kind[MAXB], tot[MAXB];

struct Query {
    int l, r, id, mn, mx;
    Query() : l(0), r(0), id(0), mn(0), mx(0) {}
    Query(int ql, int qr, int qid, int vl, int vr): l(ql), r(qr), id(qid), mn(vl), mx(vr) {}
    bool operator <(const Query& q) const {
        if (belong2[l] != belong2[q.l]) return belong2[l] < belong2[q.l];
        return belong2[l] & 1 ? r < q.r : r > q.r;
    }
} qs[MAXN];

void add(int x) {
    int b = belong1[x];
    ++cnt[x];
    ++tot[b];
    if (cnt[x] == 1) ++kind[b];
}

void del(int x) {
    int b = belong1[x];
    --cnt[x];
    --tot[b];
    if (cnt[x] == 0) --kind[b];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= m; ++i) {
        cin >> qs[i].l >> qs[i].r >> qs[i].mn >> qs[i].mx;
        qs[i].id = i;
    }
    int blen = INT(sqrt(n));
    for (int i = 1; i <= n; ++i) belong2[i] = (i - 1) / blen + 1;
    sort(qs + 1, qs + 1 + m);
    for (int i = 1; i <= 317; ++i) { // sqrt(100000) = 316, bnum = 317
        bl[i] = (i - 1) * 316 + 1;
        br[i] = min(100000, i * 316);
        for (int j = bl[i]; j <= br[i]; ++j) belong1[j] = i;
    }
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        int ql = qs[i].l, qr = qs[i].r, qid = qs[i].id, L = qs[i].mn, R = qs[i].mx;
        while (l < ql) del(arr[l++]);
        while (l > ql) add(arr[--l]);
        while (r > qr) del(arr[r--]);
        while (r < qr) add(arr[++r]);
        if (belong1[L] == belong1[R]) {
            for (int j = L; j <= R; ++j) {
                if (cnt[j]) {
                    ans1[qid] += cnt[j];
                    ++ans2[qid];
                }
            }
        }
        else {
            for (int j = L; j <= br[belong1[L]]; ++j) {
                if (cnt[j]) {
                    ans1[qid] += cnt[j];
                    ++ans2[qid];
                }
            }
            for (int j = bl[belong1[R]]; j <= R; ++j) {
                if (cnt[j]) {
                    ans1[qid] += cnt[j];
                    ++ans2[qid];
                }
            }
            for (int j = belong1[L] + 1; j < belong1[R]; ++j) {
                ans1[qid] += tot[j];
                ans2[qid] += kind[j];
            }
        }
    }
    for (int i = 1; i <= m; ++i) cout << ans1[i] << ' ' << ans2[i] << '\n';
}