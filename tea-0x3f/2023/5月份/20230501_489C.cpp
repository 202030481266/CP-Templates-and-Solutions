// Problem: C. Given Length and Sum of Digits...
// Contest: Codeforces - Codeforces Round 277.5 (Div. 2)
// URL: https://codeforces.com/problemset/problem/489/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

void print(int val, int times) {
    for (int i = 0; i < times; ++i) cout << val;
}
void solve() {
    int n, m;
    cin >> n >> m;
    if (m > 9 * n) {
        cout << -1 << ' ' << -1 << '\n';
        return;
    }
    if (m == 0) {
        if (n == 1) cout << 0 << ' ' << 0 << '\n';
        else cout << -1 << ' ' << -1 << '\n';
        return;
    }
    if (m <= 9) {
        if (n == 1) print(m, 1);
        else {
            print(1, 1);
            print(0, n - 2);
            print(m - 1, 1);
        }
    }
    else {
        if (n == 1) print(m, 1); // 9
        else {
            int x = m / 9, y = m % 9;
            int need = x + (y > 0);
            if (need == n) {
                if (y) print(y, 1);
                print(9, x);
            }
            else {
                print(1, 1);
                x = (m - 1) / 9;
                y = (m - 1) % 9;
                need = x + (y > 0);
                print(0, n - need - 1);
                if (y) print(y, 1);
                print(9, x);
            }
        }
    }
    cout << ' ';
    if (m <= 9) {
        print(m, 1);
        print(0, n - 1);
    }
    else {
        if (n == 1) print(m, 1);
        else {
            int x = m / 9, y = m % 9;
            print(9, x);
            if (y) {
                print(y, 1);
                print(0, n - x - 1);
            }
            else print(0, n - x);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}