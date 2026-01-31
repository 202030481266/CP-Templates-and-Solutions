// Problem: E. Archaeology
// Contest: Codeforces - Codeforces Global Round 4
// URL: https://codeforces.com/problemset/problem/1178/E
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
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


void solve() {
    string s;    
    cin >> s;
    int n = s.size();
    if (n <= 3) {
        cout << s[0] << '\n';
        return;
    }
    int m = (n - 4) / 2; // [0, m) + [m, m+4) + [m+4, n)
    vector<char> left, right;
    int l = -1, r = -1;
    for (int i = m; i < m + 4 && l == -1; ++i) {
        for (int j = i + 1; j < m + 4; ++j) {
            if (s[i] == s[j]) {
                l = i;
                r = j;
                break;
            }
        }
    }
    assert(l != -1 && r != -1 && r - l > 1);
    left.push_back(s[l + 1]);
    while (l >= 0 && r < n) {
        if (s[l] == s[r]) {
            right.push_back(s[r]);
            left.push_back(s[l]);
            ++r;
            --l;
        }
        else if (r + 1 < n && s[l] == s[r + 1]) {
            right.push_back(s[r + 1]);
            left.push_back(s[l]);
            --l;
            r += 2;
        }
        else if (l > 0 && s[l - 1] == s[r]) {
            right.push_back(s[r]);
            left.push_back(s[l - 1]);
            ++r;
            l -= 2;
        }
        else if (r + 1 < n && l > 0 && s[l - 1] == s[r + 1]) {
            right.push_back(s[r + 1]);
            left.push_back(s[l - 1]);
            r += 2;
            l -= 2;
        }
        else {
            if (l > 0) --l;
            else ++r;
        }
    }
    for (int i = (int)left.size() - 1; i >= 0; --i) cout << left[i];
    for (int i = 0; i < right.size(); ++i) cout << right[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}