#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;


void solve() {
    ll a00, a01, a10, a11;
    cin >> a00 >> a01 >> a10 >> a11;
    if (a00 + a01 + a10 + a11 == 0) { // very special case for 1 char
        cout << 0;
        return;
    }
    ll zero = a00 + a10 + a01 > 0 ? sqrt(a00 * 2) + 1 : 0;
    ll one = a11 + a10 + a01 > 0 ? sqrt(a11 * 2) + 1 : 0;
    // 验证 a00, a11 都是三角形数
    if (zero > 0 && zero * (zero - 1) != a00 * 2) {
        cout << "Impossible" << '\n';
        return;
    }
    if (one > 0 && one * (one - 1) != a11 * 2) {
        cout << "Impossible" << '\n';
        return;
    }
    if (zero == 0 || one == 0) {
        if (a01 || a10) {
            cout << "Impossible" << '\n';
            return;
        }
        if (zero) {
            for (int i = 0; i < zero; ++i) cout << '0';
        }
        if (one) {
            for (int i = 0; i < one; ++i) cout << '1';
        }
        return;
    }
    if (a01 + a10 != one * zero) {
        cout << "Impossible" << '\n';
        return;
    }
    // consider swap 01 to 10, will downgrade the 01 1, and upgrade the 10 1
    // assume that we have 00000...1111, that we could use this to predict the final situation
    ll steps = a10;
    ll num = steps / zero, r = steps % zero;
    for (int i = 0; i < num; ++i) cout << 1;
    for (int i = 0; i < zero - r; ++i) cout << 0;
    if (one - num > 0) cout << 1;
    for (int i = 0; i < r; ++i) cout << 0;
    for (int i = 0; i < one - num - 1; ++i) cout << 1;
}

vector<pii> use;
int n, m, a01, a10;
void dfs(int last, int one, int zero, int b01, int b10) {
    if (one == n && zero == m) {
        if (b01 == a01 && b10 == a10) {
            for (auto [val, num] : use) {
                while (num--) cout << val;
            }
            cout << '\n';
        }
        return;
    }
    if (last == -1 || last == 0) {
        for (int i = 1; i <= n - one; ++i) {
            if (b01 + zero * i > a01) break;
            use.emplace_back(1, i);
            dfs(1, one + i, zero, b01 + zero * i, b10);
            use.pop_back();
        }
    }
    if (last == -1 || last == 1) {
        for (int i = 1; i <= m - zero; ++i) {
            if (b10 + one * i > a10) break;
            use.emplace_back(0, i);
            dfs(0, one, zero + i, b01, b10 + one * i);
            use.pop_back();
        }
    }
}


void bruteforce() {
    cin >> n >> m >> a01 >> a10;
    dfs(-1, 0, 0, 0, 0);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    // bruteforce();
}

