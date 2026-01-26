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
    string s;
    cin >> s;
    vi cnt(26);
    for (char c : s) cnt[c - 'a']++;
    vi a;
    for (int i = 0; i < 26; ++i) {
        if (cnt[i] & 1) {
            a.push_back(i);
        }
    }
    int m = a.size();
    int x = m / 2;
    ranges::sort(a);
    for (int i = m - 1; i >= x; --i) {
        --cnt[a[i]];
        ++cnt[a[m - 1 - i]];
    }
    int n = s.size();
    vector<char> ans(n);
    for (int i = 0, j = 0; i < 26; ++i) {
        while (cnt[i] >= 2) {
            ans[j] = ans[n - 1 - j] = i + 'a';
            cnt[i] -= 2;
            ++j;
        }
        if (cnt[i] == 1) ans[n / 2] = i + 'a';
    }
    for (char c : ans) cout << c;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
