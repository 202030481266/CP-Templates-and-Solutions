// 信封问题，也就是错排问题

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'



int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	ll ans = 0, n;
    cin >> n;
    vector<ll> fac(n+1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i;
    for (int i = 0; i <= n; ++i) {
        if ((n-i) & 1) {
            ans -= fac[n]/fac[n-i];
        }
        else {
            ans += fac[n]/fac[n-i];
        }
    }
    cout<< ans << endl;
    return 0;
}