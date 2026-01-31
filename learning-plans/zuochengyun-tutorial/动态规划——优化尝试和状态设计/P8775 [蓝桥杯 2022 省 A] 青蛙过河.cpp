#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

int n, m;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    cin >> n >> m;    
    // 2 * m
    vector<ll> h(n);
    for (int i = 0; i < n-1; ++i) {
        cin >> h[i];
    }
    h[n-1] = m*2;
    
    int l = 0, ans = 0;
    ll s = 0;
    for (int i = 0; i < n; ++i) {
        s += h[i];
        while (s >= 2 * m) {
            s -= h[l++];
        }
        // [l-1,i]
        ans = max(ans, i-l+2);   
    }

    cout << ans << endl;

    return 0;
}