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
    int n, k;
    cin >> n >> k;
    vl A, B, C;
    for (int i = 0, t, a, b; i < n; ++i) {
        cin >> t >> a >> b;
        if (a && b) C.push_back(t);
        else if (a) A.push_back(t);
        else if (b) B.push_back(t);
    }
    ranges::sort(A);
    ranges::sort(B);
    ranges::sort(C);
    for (int i = 1; i < (int)A.size(); ++i) A[i] += A[i - 1];
    for (int i = 1; i < (int)B.size(); ++i) B[i] += B[i - 1];
    for (int i = 1; i < (int)C.size(); ++i) C[i] += C[i - 1];
    ll ans = LLINF;
    int mn = min(A.size(), B.size());
    if (mn >= k) ans = A[k - 1] + B[k - 1];
    for (int i = (mn >= k ? 0 : k - mn - 1); i < min((int)C.size(), k); ++i) {
        ll res = (i + 1 < k ? A[k - i - 2] + B[k - i - 2] : 0);
        ans = min(ans, res + C[i]);
    }
    if (ans == LLINF) cout << -1 << '\n';
    else cout << ans << '\n';
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
