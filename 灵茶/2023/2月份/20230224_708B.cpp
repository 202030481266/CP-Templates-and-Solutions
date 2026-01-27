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
    ll zero = a00 > 0 ? sqrt(a00 * 2) + 1 : 0;
    ll one = a11 > 0 ? sqrt(a11 * 2) + 1 : 0;
    // 验证 a00, a11 都是三角形数
    if (zero > 0 && zero * (zero - 1) != a00) {
        cout << "Impossible" << '\n';
        return;
    }
    if (one > 0 && one * (one - 1) != a11) {
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
    if (a01 == 0 || a10 == 0) {
        if (a01) {
            for (int i = 0; i < zero; ++i) cout << '0';
            for (int i = 0; i < one; ++i) cout << '1';
        }
        if (a10) {
            for (int i = 0; i < one; ++i) cout << '1';
            for (int i = 0; i < zero; ++i) cout << '0';
        }
        return;
    }
    if (




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}

