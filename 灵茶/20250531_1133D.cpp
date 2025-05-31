// https://codeforces.com/problemset/problem/1133/D

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

static constexpr int maxn = 200001;
int n, a[maxn], b[maxn];

long long hash_pair(int a, int b) {
    const long long OFFSET = 1000000000LL;
    const long long MASK = (1LL << 31) - 1;  // 31位掩码
    
    long long offset_a = (long long)a + OFFSET;
    long long offset_b = (long long)b + OFFSET;
    
    return (offset_a << 31) | (offset_b & MASK);
}

unordered_map<long long, int> cnt;

void cf1133D() {
    cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1; i <= n; ++i) {
    	if (a[i] == 0) {
    		if (b[i] == 0) ++ans;
    		continue;
    	}
        int g = __gcd(a[i], b[i]);
        a[i] /= g;
        b[i] /= g;
        // (2, 3) is not the same as (3, 2)
        cnt[hash_pair(a[i], b[i])]++;
    }
    int res = 0;
    for (auto &p : cnt) {
        res = max(res, p.second);
    }
    cout << res + ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cf1133D();
}