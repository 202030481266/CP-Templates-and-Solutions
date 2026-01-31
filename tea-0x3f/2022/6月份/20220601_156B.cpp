#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 1000005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> yes(n + 1), no(n + 1);
    vector<int> q(n + 1);
    char op;
    for (int i = 1; i <= n; ++i) {
        cin >> op;
        cin >> q[i];
        if (op == '+') {
            ++yes[q[i]];
        }
        else {
            ++no[q[i]];
            q[i] *= -1;
        }
    }
    int a = accumulate(yes.begin(), yes.end(), 0);
    vector<int> arr;
    vector<int> vis(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (a - yes[i] + no[i] == n - m) {
            arr.push_back(i);
            vis[i] = 1;
        }
    }
    assert(!arr.empty());
    if (arr.size() == 1) {
        for (int i = 1; i <= n; ++i) {
            if (q[i] > 0) {
                if (q[i] != arr[0]) cout << "Lie\n";
                else cout << "Truth\n";
            }
            else {
                if (-q[i] == arr[0]) cout << "Lie\n";
                else cout << "Truth\n";
            }
        }
    }
    else {
        for (int i = 1; i <= n; ++i) {
            if (q[i] > 0) {
                if (!vis[q[i]]) cout << "Lie\n";
                else cout << "Not defined\n";
            }
            else {
                if (!vis[-q[i]]) cout << "Truth\n";
                else cout << "Not defined\n";
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
