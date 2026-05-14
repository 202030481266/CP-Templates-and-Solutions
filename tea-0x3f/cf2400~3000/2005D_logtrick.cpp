#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ll = long long;

struct State {
    int a, b;
    int count;
};

void solve() {
    int n;
    cin >> n;
    vi a(n), b(n);
    for (int& v : a) cin >> v;
    for (int& v : b) cin >> v;

    vi preA(n + 1, 0), preB(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        preA[i + 1] = gcd(preA[i], a[i]);
        preB[i + 1] = gcd(preB[i], b[i]);
    }

    vi sufA(n + 1, 0), sufB(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
        sufA[i] = gcd(sufA[i + 1], a[i]);
        sufB[i] = gcd(sufB[i + 1], b[i]);
    }

    ll max_sum = 0, ans_cnt = 0;
    
    vector<State> cur;
    cur.reserve(150);
    vector<State> nxt;
    nxt.reserve(150);

    for (int r = 0; r < n; ++r) {
        nxt.clear();
        
        for (auto& s : cur) {
            nxt.push_back({gcd(s.a, b[r]), gcd(s.b, a[r]), s.count});
        }
        
        nxt.push_back({gcd(preA[r], b[r]), gcd(preB[r], a[r]), 1});

        sort(nxt.begin(), nxt.end(), [](const State& x, const State& y) {
            if (x.a != y.a) return x.a < y.a;
            return x.b < y.b;
        });

        cur.clear();
        for (auto& s : nxt) {
            if (!cur.empty() && cur.back().a == s.a && cur.back().b == s.b) {
                cur.back().count += s.count;
            } else {
                cur.push_back(s);
            }
        }

        for (auto& s : cur) {
            int final_a = gcd(s.a, sufA[r + 1]);
            int final_b = gcd(s.b, sufB[r + 1]);
            ll sum = (ll)final_a + final_b;
            
            if (sum > max_sum) {
                max_sum = sum;
                ans_cnt = s.count;
            } else if (sum == max_sum) {
                ans_cnt += s.count;
            }
        }
    }

    cout << max_sum << " " << ans_cnt << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}