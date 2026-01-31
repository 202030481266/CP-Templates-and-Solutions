#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 60005;
static constexpr int INF = 0x3f3f3f3f;

#define INT(x) static_cast<int>(x)

char s[MAXN];
int n, m, arr[MAXN], belong[MAXN];
int cnt[1 << 26], ans[MAXN];

struct Query {
    int l, r, id;
    Query(): l(0), r(0), id(0) {}
    Query(int ql, int qr, int qid): l(ql), r(qr), id(qid) {}
    bool operator < (const Query& q) const {
        if (belong[l] != belong[q.l]) return belong[l] < belong[q.l];
        return belong[l] & 1 ? r < q.r : r > q.r;
    }
} qs[MAXN];

int cur = 0;

void add(int status) {
    cur += cnt[status];
    ++cnt[status];
    for (int i = 0; i < 26; ++i) {
        cur += cnt[status ^ 1 << i];
    }
}

void del(int status) {
    --cnt[status];
    cur -= cnt[status];
    for (int i = 0; i < 26; ++i) {
        cur -= cnt[status ^ 1 << i];
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        arr[i + 1] = 1 << (s[i] - 'a');
    }
    ++n; // 1 is the zero status
    for (int i = 2; i <= n; ++i) arr[i] ^= arr[i - 1];
    for (int i = 1; i <= m; ++i) {
        cin >> qs[i].l >> qs[i].r;
        ++qs[i].r;
        qs[i].id = i;
    }
    int blen = INT(sqrt(n));
    for (int i = 1; i <= n; ++i) belong[i] = (i - 1) / blen + 1;
    sort(qs + 1, qs + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        int ql = qs[i].l, qr = qs[i].r, qid = qs[i].id;
        while (l < ql) del(arr[l++]);
        while (l > ql) add(arr[--l]);
        while (r > qr) del(arr[r--]);
        while (r < qr) add(arr[++r]);
        ans[qid] = cur;
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}