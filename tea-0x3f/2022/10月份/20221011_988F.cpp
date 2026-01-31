// Problem: F. Rain and Umbrellas
// Contest: Codeforces - Codeforces Round 486 (Div. 3)
// URL: https://codeforces.com/contest/988/problem/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

// CHT optimized DP
struct CHT
{
    vector<ll> m, b;
    int ptr = 0;

    bool bad(int l1, int l2, int l3)
    {
        return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  > 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query max), (slope inc+query min)
    }

    void add(ll _m, ll _b)
    {
        while (!m.empty() && m.back() >= _m) { // delete the useless line
            m.pop_back();
            b.pop_back();
        }
        if (m.empty() || _b < b.back()) {
            m.push_back(_m);
            b.push_back(_b);
            int s = m.size();
            while(s >= 3 && bad(s - 3, s - 2, s - 1))
            {
                s--;
                m.erase(m.end() - 2);
                b.erase(b.end() - 2);
            }
        }
    }

    ll f(int i, ll x)
    {
        return m[i] * x + b[i];
    }

    //(slope dec+query min), (slope inc+query max) -> x increasing
    //(slope dec+query max), (slope inc+query min) -> x decreasing
    // ll query(ll x)
    // {
    //     if(ptr >= m.size()) ptr = m.size() - 1;
    //     while(ptr < m.size() - 1 && f(ptr + 1, x) < f(ptr, x)) ptr++;
    //     return f(ptr, x);
    // }
    ll query(ll x) {
        if (m.empty()) return INF;
        if (ptr >= m.size()) ptr = m.size() - 1;
        while (ptr > 0 && f(ptr - 1, x) < f(ptr, x)) --ptr;
        return f(ptr, x);
    }

    ll bs(ll x) {
        if (m.empty()) return INF;
        return bs(0, m.size() - 1, x);
    }

    ll bs(int l, int r, ll x)
    {
        int mid = (l + r) / 2;
        if(mid + 1 < m.size() && f(mid + 1, x) < f(mid, x)) return bs(mid + 1, r, x); // > for max
        if(mid - 1 >= 0 && f(mid - 1, x) < f(mid, x)) return bs(l, mid - 1, x); // > for max
        return f(mid, x);
    }
};

void solve() {
    int n, m, dst;
    cin >> dst >> n >> m;
    vector<pii> rain(n);
    vector<pii> unb(m);
    stack<pii> st;
    for (int i = 0; i < n; ++i) cin >> rain[i].first >> rain[i].second;
    for (int i = 0; i < m; ++i) cin >> unb[i].first >> unb[i].second;
    ranges::sort(rain);
    ranges::sort(unb);
    int i = 0;
    ll ans = 0;
    CHT cht;
    for (auto [l, r] : rain) {
        while (i < m && unb[i].first <= l) {
            // ans + unb[i].second * (x - unb[i].first) = unb[i].second * x - unb[i].second * unb[i].first + ans;
            cht.add(unb[i].second, ans - unb[i].first * unb[i].second);
            ++i;
        }
        if (cht.m.empty()) {
        	cout << -1 << '\n';
        	return;
        }
        while (i < m && unb[i].first < r) {
            ans = cht.bs(unb[i].first);
            cht.add(unb[i].second, ans - unb[i].first * unb[i].second);
            ++i;
        }
        // arrive at the r
        ans = cht.bs(r);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}