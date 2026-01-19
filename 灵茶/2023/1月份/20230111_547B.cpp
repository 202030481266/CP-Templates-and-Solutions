// Problem: B. Mike and Feet
// Contest: Codeforces - Codeforces Round 305 (Div. 1)
// URL: https://codeforces.com/problemset/problem/547/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;


void solve() {
    int n;
    cin >> n;
    // interval update and monotonic stack
    vi arr(n);
    for (int& v : arr) cin >> v;
    stack<int> s;
    vi left(n);
    vi right(n);
    for (int i = 0; i < n; ++i) {
        while (!s.empty() && arr[s.top()] > arr[i]) {
            right[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    while (!s.empty()) {
        right[s.top()] = n;
        s.pop();
    }
    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && arr[s.top()] > arr[i]) {
            left[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    while (!s.empty()) {
        left[s.top()] = -1;
        s.pop();
    }
    vi ans(n + 1);
    for (int i = 0; i < n; ++i) {
        int len = right[i] - left[i] - 1;
        ans[len] = max(ans[len], arr[i]);
    }
    for (int i = n - 1; i >= 1; --i) ans[i] = max(ans[i], ans[i + 1]);
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}