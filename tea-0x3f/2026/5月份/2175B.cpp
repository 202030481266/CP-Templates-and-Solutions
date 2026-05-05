// Problem: B. XOR Array
// Contest: Codeforces - Codeforces Round 1069 (Div. 2)
// URL: https://codeforces.com/problemset/problem/2175/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;


void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> arr(n + 1);
    iota(arr.begin(), arr.end(), 0);
    arr[l - 1] = arr[r];
    for (int i = 1; i <= n; ++i) {
        cout << (arr[i] ^ arr[i - 1]) << ' ';
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
