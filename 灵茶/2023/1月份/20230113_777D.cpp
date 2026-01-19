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


void solve() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (string& v : s) cin >> v;
    vector<int> ed(n);
    ed[n - 1] = s[n - 1].size();
    for (int i = n - 2; i >= 0; --i) {
        int& k = ed[i];
        while (k < min((int)s[i].size(), ed[i + 1])) {
            if (s[i][k] < s[i + 1][k]) {
                k = s[i].size();
                break;
            }
            else if (s[i][k] > s[i + 1][k]) break;
            else ++k;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < ed[i]; ++k) cout << s[i][k];
        cout << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}