// Problem: A. Nephren gives a riddle
// Contest: Codeforces - Codeforces Round 449 (Div. 1)
// URL: https://codeforces.com/problemset/problem/896/A
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 300005;
static constexpr int MOD = 998244353;
static constexpr int INF = 0x3f3f3f3f;

const char* s0 = "What are you doing at the end of the world? Are you busy? Will you save us?";
const char* s1 = "What are you doing while sending \""; // 34
const char* s2 = "\"? Are you busy? Will you send \""; // 32
const char* s3 = "\"?"; // 2
ll f[54];

char getChar(int m, ll k) {
    int x = m - 53;
    if (x > 0) {
        if (k - 34 * x <= 0) {
            k %= 34;
            if (k == 0) k = 34;
            return s1[k - 1];
        }
        k -= x * 34;
        m = 53;
    }
    while (true) {
        if (k > f[m]) return '.';
        if (m == 0) return s0[k - 1];
        if (k <= 34) return s1[k - 1];
        if (k <= 34 + f[m - 1]) {
            m = m - 1;
            k = k - 34;
            continue;
        }
        if (k <= 66 + f[m - 1]) return s2[k - 34 - f[m - 1] - 1];
        if (k <= 66 + 2 * f[m - 1]) {
            k = k - 66 - f[m - 1];
            m = m - 1;
            continue;
        }
        return s3[k - 2 * f[m - 1] - 66 - 1];
    }
}

void solve() {
    f[0] = strlen(s0);
    for (int i = 1; i < 54; ++i) f[i] = 2 * f[i - 1] + 68;
    int n, m;
    ll k;
    cin >> n;
    while (n--) {
        cin >> m >> k;
        cout << getChar(m, k);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
}


