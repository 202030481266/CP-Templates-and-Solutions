#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 300005;
static constexpr int MOD = 998244353;
static constexpr int INF = 0x3f3f3f3f;

int n, m, arr[MAXN];

int dis(int from, int to) {
    return ((to - from) % m + m) % m;
}

bool check(int cost) {
    int pre = 0;
    for (int i = 1; i <= n; ++i) {
        if (dis(arr[i], pre) > cost) {
            if (arr[i] < pre) return false;
            else pre = arr[i];
        }
    }
    return true;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    int l = -1, r = m + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    cout << r << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
}
