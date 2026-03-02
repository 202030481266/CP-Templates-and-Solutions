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
    vector<char> arr(n);
    for (char& c : arr) cin >> c;
    if (n & 1) {
        cout << -1 << '\n';
        return;
    }
    int sum = 0;
    for (char c : arr) {
        if (c == '1') ++sum;
    }
    if (sum != n / 2) {
        cout << -1 << '\n';
        return;
    }
    // then we can always construct the string
    deque<int> q;
    vi a, b;
    vi ans;
    for (char c : arr) q.push_back(c - '0');
    while (!q.empty()) {
        int x = q.front();
        int y = q.back();
        if (x ^ y) {
            a.push_back(x);
            b.push_back(y);
            q.pop_front();
            q.pop_back();
        }
        else {
            if (x) {
                ans.push_back(a.size());
                a.push_back(0);
                b.push_back(1);
                q.push_front(1);
                q.pop_back();
                n += 2;
            }
            else {
                ans.push_back(n - b.size());
                a.push_back(0);
                b.push_back(1);
                q.push_back(0);
                q.pop_front();
                n += 2;
            }
        }
    }
    cout << ans.size() << '\n';
    for (int v : ans) cout << v << ' ';
    cout << '\n';
} 


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    int t;
    cin >> t;
    while (t--) solve();
}

