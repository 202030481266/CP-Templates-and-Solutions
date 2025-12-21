#include <bits/stdc++.h>
using namespace std;

// 保留原有的常量定义
static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;
using ll = long long;

int n, m;
ll arr[MAXN], b[15]; 

template<typename T> void read(T &x) { cin >> x; }
void writeln(int x) { cout << x << "\n"; }

void solve() {
    read(n);
    read(m);
    arr[1] = 0;
    vector<ll> vals;
    vals.reserve(n);
    vals.push_back(0);
    
    for (int i = 2; i <= n; ++i) {
        ll tmp;
        read(tmp);
        arr[i] = tmp - arr[i - 1];
        vals.push_back(arr[i]);
    }
    for (int i = 1; i <= m; ++i) read(b[i]);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto get_id = [&](ll val) -> int {
        auto it = lower_bound(vals.begin(), vals.end(), val);
        if (it != vals.end() && *it == val) {
            return int(it - vals.begin());
        }
        return -1;
    };
    int sz = vals.size();
    vector<int> cnt[2];
    cnt[0].resize(sz, 0);
    cnt[1].resize(sz, 0);
    for (int i = 1; i <= n; ++i) {
        int id = get_id(arr[i]);
        cnt[i & 1][id]++;
    }

    int ans = 0;
    for (int u = 0; u < sz; ++u) {
        ll val = vals[u];
        for (int p = 0; p < 2; ++p) {
            if (cnt[p][u] == 0) continue;
            for (int j = 1; j <= m; ++j) {
                int res = 0;
                for (int k = 1; k <= m; ++k) {
                    ll target1 = b[k] - b[j] + val;
                    int id1 = get_id(target1);
                    if (id1 != -1) res += cnt[p][id1];
                    ll target2 = b[k] + b[j] - val;
                    int id2 = get_id(target2);
                    if (id2 != -1) res += cnt[p ^ 1][id2];
                }
                ans = max(ans, res);
            }
        }
    }
    writeln(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}