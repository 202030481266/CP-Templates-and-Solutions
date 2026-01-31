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
    int n;
    cin >> n;
    vector<char> s(n);
    for (char& c : s) cin >> c;
    vi l(n), r(n);
    l[0] = 0;
    int cur = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == '(') ++cur;
        else {
            --cur;
            if (cur < 0) {
                for (int j = i + 1; j < n; ++j) l[j] = -1;
                break;
            }
        }
        l[i + 1] = cur;
    }
    r[n - 1] = 0;
    cur = 0;
    for (int i = n - 1; i > 0; --i) {
        if (s[i] == ')') ++cur;
        else {
            --cur;
            if (cur < 0) {
                for (int j = i - 1; j >= 0; --j) r[j] = -1;
                break;
            }
        }
        r[i - 1] = cur;
    }
    // debug
    //for (int i = 0; i < n; ++i) cout << l[i] << ' '; cout << endl;
    //for (int i = 0; i < n; ++i) cout << r[i] << ' '; cout << endl;

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (l[i] != -1 && r[i] != -1) {
            if (l[i] - r[i] == 1 && s[i] == '(') ++ans;
            if (r[i] - l[i] == 1 && s[i] == ')') ++ans;
        }
    }
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
