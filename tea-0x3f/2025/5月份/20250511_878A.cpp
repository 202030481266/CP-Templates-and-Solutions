#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

int n;

void solve() {
    cin >> n;
    int x = 1023, y = 0, v;
    char op;
    for (int i = 0; i < n; ++i) {
        cin >> op >> v;
        if (op == '|') {
            x |= v;
            y |= v;
        }
        else if (op == '^') {
            x ^= v;
            y ^= v;
        }
        else {
            x &= v;
            y &= v;
        }
    }
    int or_value = 0, and_value = 1023, xor_value = 0;
    for (int i = 0; i < 10; ++i) {
        int a = x >> i & 1, b = y >> i & 1;
        if (a == 0 && b == 0) {
            and_value &= ~(1 << i);
        }
        else if (a == 1 && b == 1) {
            or_value |= 1 << i;
        }
        else if (a == 0 && b == 1) {
            xor_value |= 1 << i;
        }
    }
    cout << 3 << '\n';
    cout << '|' << ' ' << or_value << '\n';
    cout << '&' << ' ' << and_value << '\n';
    cout << '^' << ' ' << xor_value << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}