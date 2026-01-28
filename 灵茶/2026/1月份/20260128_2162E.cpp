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

int get(int n, int a, int b) {
    // get diff numbers , a b c and they pairwise different
    int mn, mx;
    if (a > b) mx = a, mn = b;
    else mx = b, mn = a;
    if (mn + 1 < mx) return mn + 1;
    if (mx + 1 <= n) return mx + 1;
    return mn - 1;
} 
    
void solve() {
    int n, k;
    cin >> n >> k;
    vi arr(n);
    for (int& v : arr) cin >> v;
    vi use(n + 1);
    for (int v : arr) use[v] = 1;
    int p = arr[0];
    for (int i = 1; i <= n; ++i) {
        if (!use[i]) {
            p = i;
            break;
        }
    }
    cout << p << ' ';
    int a = arr.back(), b = p;
    for (int i = 0; i < k - 1; ++i) {
        int nxt = get(n, a, b);
        cout << nxt << ' ';
        a = b;
        b = nxt;
    }
    cout << '\n';
}
    
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
