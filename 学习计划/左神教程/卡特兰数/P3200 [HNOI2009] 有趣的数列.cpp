// 卡特兰数， 因子计数法

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'


vector<int> generate_min_divisors(int n) {
    vector<int> lp(n + 1);
    lp[1] = 1;
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= n; ++j)
            lp[i * primes[j]] = primes[j];
    }
    return lp;
}

ll quick_pow(ll a, ll b, int p) {
    ll res = 1;
    for (;b; b >>= 1) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, p;
    cin >> n >> p;
    auto prime = generate_min_divisors(n * 2);

    // f(n) = 2n * (2n - 1) * (2n-2) * ... (n+2) / n * (n-1) * (n-2) * (n-3) * ...2
    ll ans = 1;
    vector<int> cnt(2 * n + 1);
    for (int i = n+2; i <= 2*n; ++i) ++cnt[i];
    for (int i = 2; i <= n; ++i) --cnt[i];
    for (int i = 2 * n; i >= 2; --i) {
        if (prime[i] == i) continue;
        int x = prime[i], y = i / prime[i];
        cnt[x] += cnt[i];
        cnt[y] += cnt[i];
        cnt[i] = 0;
    }
    for (int i = 2; i <= 2 * n; ++i) {
        if (cnt[i] > 0) {
            ans = (ans * quick_pow(i, cnt[i], p)) % p;
        }
    }
    cout << ans << endl;
    return 0;
}