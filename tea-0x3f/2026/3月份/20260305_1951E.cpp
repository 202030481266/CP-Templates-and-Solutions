// Problem: E. No Palindromes
// Contest: Codeforces - Codeforces Global Round 25
// URL: https://codeforces.com/contest/1951/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

bool isPalindrome(string& s) {
    int n = s.size();
    int l = 0, r = n - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        ++l;
        --r;
    }
    return true;
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    if (!isPalindrome(s)) {
        cout << "YES\n";
        cout << 1 << '\n' << s << '\n';
        return;
    }
    for (int i = 1; i + 1 < n - 1; ++i) {
        if (s[i] != s[0] && s[i + 1] != s[0]) {
            cout << "YES\n";
            cout << 2 << '\n';
            cout << s.substr(0, i + 1) << '\n' << s.substr(i + 1, n - i - 1) << '\n';
            return;
        }
    }
    vi pos;
    for (int i = 0; i < n; ++i) {
        if (s[i] != s[0]) pos.push_back(i);
    }
    int m = pos.size();
    if (m < 2) {
        cout << "NO\n";
        return;
    }
    int c = pos[0];
    for (int i = 1; i < m; ++i) {
        int seg = pos[i] - pos[i - 1] - 1;
        if (seg != c) {
            cout << "YES\n";
            cout << m << '\n';
            // 0 ... 1 ... 2 ... 3 ... i - 1 ... i ...  i + 1 ...
            for (int j = 0; j < i - 1; ++j) {
                int st = j == 0 ? 0 : pos[j - 1] + 1; // [st, pos[j]]
                cout << s.substr(st, pos[j] - st + 1) << '\n';
            }
            int st = i == 1 ? 0 : pos[i - 2] + 1; // [st, pos[i])
            cout << s.substr(st, pos[i] - st) << '\n';
            for (int j = i; j < m; ++j) {
                int ed = j == m - 1 ? n : pos[j + 1];
                cout << s.substr(pos[j], ed - pos[j]) << '\n';
            }
            return;
        }
    }
    // 这说明都是等间距的
    if (c > 1) {
        cout << "YES\n";
        cout << m << '\n';
        cout << s.substr(0, 2 * c) << '\n';
        cout << s.substr(2 * c, m == 2 ? n - 2 * c : pos[2] - 2 * c) << '\n';
        for (int i = 2; i < m; ++i) {
            int ed = i == m - 1 ? n : pos[i + 1];
            cout << s.substr(pos[i], ed - pos[i]) << '\n';
        }
    }
    else {
        int p = 1; 
        while (p < m && s[pos[p]] == s[pos[0]]) ++p; 
        if (p == m) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n"; // [0, p] is 1
            cout << 1 + m - p << '\n';
            cout << s.substr(0, p == m - 1 ? n : pos[p + 1]) << '\n';
            for (int i = p + 1; i < m; ++i) {
                int ed = i == m - 1 ? n : pos[i + 1];
                cout << s.substr(pos[i], ed - pos[i]) << '\n';
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}