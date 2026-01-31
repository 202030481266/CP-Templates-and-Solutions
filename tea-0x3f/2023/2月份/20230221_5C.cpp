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
    int n = s.size();
    int mx = 0, ans = 1;
    vector<pii> a;
    int cur = 0;
    a.emplace_back(0, -1);
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') {
            if (cur < 0) {
                cur = 0;
                a.clear();
                a.emplace_back(0, i - 1);
            }
            ++cur;
            a.emplace_back(cur, i);
        }
        else {
            --cur;
            if (cur >= 0) {
                while (!a.empty() && a.back().first > cur) a.pop_back();
                if (!a.empty()) {
                    int len = i - a.back().second;
                    if (len > mx) {
                        mx = len;
                        ans = 1;
                    }
                    else if (len == mx) ++ans;
                }
            }
        }
    }
    cout << mx << ' ' << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
