// Problem: E. Bored Bakry
// Contest: Codeforces - Codeforces Round 746 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1592/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 1000005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int n, arr[MAXN], sum[MAXN];

static constexpr int MAX_BIT = 20;
static constexpr int MAX_NODE = MAXN << 2;

int tree[MAX_NODE][2], tot = 0;
int ptr[MAX_NODE];
vi idx[MAX_NODE];

int alloc() {
    int x = ++tot;
    tree[x][0] = tree[x][1] = 0;
    return x;
}

void reset() {
    for (int i = 1; i <= tot; ++i) {
        tree[i][0] = tree[i][1] = 0;
        idx[i].clear();
        ptr[i] = 0;
    }
    tot = 0;
}

int root;

void insert(int x, int root, int p) {
    int u = root;
    for (int i = MAX_BIT - 1; i >= 0; --i) {
        int b = x >> i & 1;
        if (!tree[u][b]) tree[u][b] = alloc();
        u = tree[u][b];
        idx[u].push_back(p);
    }
}

int pos[MAX_BIT];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) sum[i] = arr[i] ^ sum[i - 1];
    int ans = 0;
    auto cal = [&](int st) -> void {
        reset();
        root = alloc();
        memset(pos, 0, sizeof(pos));
        for (int i = st; i <= n; ++i) {
            for (int j = MAX_BIT - 1; j >= 0; --j) {
                if (!(arr[i] >> j & 1)) pos[j] = i;
            }
            if ((i & 1) != (st & 1)) continue;
            int u = root;
            for (int j = MAX_BIT - 1; j >= 0; --j) {
                int b = sum[i] >> j & 1;
                if (!tree[u][b]) break;
                u = tree[u][b];
                while (ptr[u] < idx[u].size() && idx[u][ptr[u]] < pos[j]) ++ptr[u];
                if (ptr[u] < idx[u].size() && ans < i - idx[u][ptr[u]]) {
                    ans = i - idx[u][ptr[u]];
                }
            }
            insert(sum[i], root, i);
        }
    };
    cal(0);
    cal(1);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
