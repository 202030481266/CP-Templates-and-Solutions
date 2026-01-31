#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll quick_mul(ll a, ll b, ll p) {
    a = (a % p + p) % p;
    b = (b % p + p) % p;
    ll ans = 0;
    for(; b; b >>= 1) {
        if(b & 1) ans = (ans + a) % p;
        a = a * 2 % p;
    }
    return ans;
}

// 扩展欧几里得算法，求 ax + by = gcd(a, b) 的解，返回 gcd(a, b) 和对应的 x, y
ll extendedGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

ll ceil_div(ll a, ll b) {
    ll q = a / b;
    ll r = a % b;
    if (r != 0 && ((a ^ b) > 0)) {
        q += 1;
    }
    return q;
}


ll solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> residues(n); // 余数数组
    vector<ll> moduli(n);   // 模数数组
    vector<ll> sword(n);

    for (int i = 0; i < n; ++i) cin >> residues[i];
    for (int i = 0; i < n; ++i) cin >> moduli[i];
    for (int i = 0; i < n; ++i) cin >> sword[i];

    multiset<ll> s;
    ll tmp;
    for (int i = 0; i < m; ++i) {
        cin >> tmp;
        s.insert(tmp);
    }

    ll lcm = 1;
    ll tail = 0;

    /*
        x = lcm * k + tail 
        now, deal with ax + py = r
        -> a * (lcm * k + tail) + py = r
        -> a * lcm * k + py = r - a * tail
        exgcd -> k = k0 + p / gcd(a*lcm, p) * n (n is Integer)
        -> x = lcm * (k0 + p / gcd(a*lcm, p) * n) + tail
        -> x = (lcm * p / gcd(a*lcm, p)) * n + (tail + lcm * k0)
        so, we have
        -> new_lcm = lcm * p / gcd(a * lcm, p)
        -> new_tail = tail + lcm * k0
    */

    vector<ll> ack(n);

    for (int i = 0; i < n; ++i) {

        // find ack
        auto it = s.upper_bound(residues[i]);
        if (it != s.begin()) it = prev(it);
        
        ack[i] = *it;
        s.erase(it);
        
        ll a = ack[i] * lcm;
        ll b = moduli[i];
        ll c = residues[i] - tail * ack[i];
        ll x, y;
        ll gcd = extendedGCD(a, b, x, y);

        if (c % gcd != 0) {
            return -1;
        }

        ll m = b / gcd;
        x = quick_mul(x, c / gcd, m);
        if (x < 0) x += m; // 非负

        tail = (tail + lcm * x) % (lcm * m);
        lcm *= m;

        s.insert(sword[i]);
    }
    ll ans = (tail % lcm + lcm) % lcm, k = 0; 
    for (int i = 0; i < n; ++i) {
        if (residues[i] > (k * lcm + ans) * ack[i])
            k = ceil_div(residues[i] - ans * ack[i], lcm * ack[i]);
    }
    return k * lcm + ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        cout << solve() << '\n';
    }

    return 0;
}