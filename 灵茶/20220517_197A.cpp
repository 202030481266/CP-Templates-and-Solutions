#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 1003;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)


void solve() {
    int n, m, r;
    cin >> n >> m >> r;
    if (n >= 2 * r && m >= 2 * r) cout << "First\n";
    else cout << "Second\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}