// Problem: B. Peculiar Movie Preferences
// Contest: Codeforces - Codeforces Round 767 (Div. 1)
// URL: https://codeforces.com/problemset/problem/1628/B
// Memory Limit: 512 MB
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

int cnt[26][26];
int pre[26][26], suf[26][26];
int tot[26][26][26];

void solve() {
    int n;
    cin >> n;
    vector<string> w(n);
    for (string& s : w) cin >> s;
    bool flag = false;
    for (string& s : w) {
        int m = s.size();
        if (m == 1) flag = true;
        if (m == 2) {
            if (s[0] == s[1]) flag = true;
            // 2 + 2, ab look for ba
            if (cnt[s[1] - 'a'][s[0] - 'a']) flag = true;
            // 3 + 2, ab look for bax
            if (pre[s[1] - 'a'][s[0] - 'a']) flag = true;
            cnt[s[0] - 'a'][s[1] - 'a']++;
        }
        if (m == 3) {
            if (s[0] == s[2]) flag = true;
            // 3 + 3
            // abc look for cba
            if (tot[s[2] - 'a'][s[1] - 'a'][s[0] - 'a']) flag = true;
            // 2 + 3, xab look for ba
            if (cnt[s[2] - 'a'][s[1] - 'a']) flag = true;
            pre[s[0] - 'a'][s[1] - 'a']++;
            tot[s[0] - 'a'][s[1] - 'a'][s[2] - 'a']++;
        }
    }
    if (flag) cout << "YES\n";
    else cout << "NO\n";
    for (string& s : w) {
        int m = s.size();
        if (m == 2) {
            cnt[s[0] - 'a'][s[1] - 'a'] = 0;
        }
        if (m == 3) {
            pre[s[0] - 'a'][s[1] - 'a'] = 0;
            tot[s[0] - 'a'][s[1] - 'a'][s[2] - 'a'] = 0;
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