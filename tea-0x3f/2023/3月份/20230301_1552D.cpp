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
    vi arr(n + 1);
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    if (n == 1) {
        cout << (arr[1] == 0 ? "YES" : "NO") << '\n';
        return;
    }
    set<int> s;
    for (int i = 0; i <= n; ++i) {
        if (s.contains(abs(arr[i]))) {
            cout << "YES" << '\n';
            return;
        }
        else {
            if (i == 0) s.insert(0);
            else {
                vi res;
                for (int v : s) {
                    res.push_back(v + abs(arr[i]));
                    res.push_back(v - abs(arr[i]));
                }
                for (int v : res) s.insert(abs(v));
            }
        }
    }
    cout << "NO" << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
