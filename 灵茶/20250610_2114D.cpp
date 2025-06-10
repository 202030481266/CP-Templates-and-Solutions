// https://codeforces.com/problemset/problem/2114/D 
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> count(const vector<int>& arr) {
    int p = 0, n = arr.size();
    vector<int> res;
    while (p < n) {
        int i = p + 1;
        while (i < n && arr[i] == arr[p]) ++i;
        res.push_back(i - p);
        p = i;
    }
    return res;
}

void cf2114D() {
    int n;
    cin >> n;
    vector<array<int, 2>> points(n);
    vector<int> a, b;
    for (int i = 0; i < n; ++i) {
        cin >> points[i][0] >> points[i][1];
        a.push_back(points[i][0]);
        b.push_back(points[i][1]);
    }
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    auto ca = count(a);
    auto cb = count(b);
    a.erase(unique(a.begin(), a.end()), a.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int mxr = a.back(), mnr = a[0];
    int mxc = b.back(), mnc = b[0];
    ll ans = 1ll * (mxr - mnr + 1) * (mxc - mnc + 1);
    for (auto& p : points) {
        int x = p[0], y = p[1];
        int i = lower_bound(a.begin(), a.end(), x) - a.begin();
        int j = lower_bound(b.begin(), b.end(), y) - b.begin();
        if (ca[i] == 1 && cb[j] == 1) {
            if (a[i] == mnr && b[j] == mnc) {
                if (n - 1 < 1ll * (mxr - a[i+1] + 1) * (mxc - b[j+1] + 1)) {
                    ans = min(ans, 1ll * (mxr - a[i+1] + 1) * (mxc - b[j+1] + 1));
                }
                else {
                    ll s1 = 1ll * (mxr - a[i+1] + 2) * (mxc - b[j+1] + 1);
                    ll s2 = 1ll * (mxr - a[i+1] + 1) * (mxc - b[j+1] + 2);
                    ans = min(ans, min(s1, s2));
                }
            }
            if (a[i] == mxr && b[j] == mnc) {
                if (n - 1 < 1ll * (a[i-1] - mnr + 1) * (mxc - b[j+1] + 1)) {
                    ans = min(ans, 1ll * (a[i-1] - mnr + 1) * (mxc - b[j+1] + 1));
                }
                else {
                    ll s1 = 1ll * (a[i-1] - mnr + 2) * (mxc - b[j+1] + 1);
                    ll s2 = 1ll * (a[i-1] - mnr + 1) * (mxc - b[j+1] + 2);
                    ans = min(ans, min(s1, s2));
                }
            }
            if (a[i] == mnr && b[j] == mxc) {
                if (n - 1 < 1ll * (mxr - a[i+1] + 1) * (b[j-1] - mnc + 1)) {
                    ans = min(ans, 1ll * (mxr - a[i+1] + 1) * (b[j-1] - mnc + 1));
                }
                else {
                    ll s1 = 1ll * (mxr - a[i+1] + 2) * (b[j-1] - mnc + 1);
                    ll s2 = 1ll * (mxr - a[i+1] + 1) * (b[j-1] - mnc + 2);
                    ans = min(ans, min(s1, s2));
                }
            }
            if (a[i] == mxr && b[j] == mxc) {
                if (n - 1 < 1ll * (a[i-1] - mnr + 1) * (b[j-1] - mnc + 1)) {
                    ans = min(ans, 1ll * (a[i-1] - mnr + 1) * (b[j-1] - mnc + 1));
                }
                else {
                    ll s1 = 1ll * (a[i-1] - mnr + 2) * (b[j-1] - mnc + 1);
                    ll s2 = 1ll * (a[i-1] - mnr + 1) * (b[j-1] - mnc + 2);
                    ans = min(ans, min(s1, s2));
                }
            }
        }
        if (ca[i] == 1) {
            if (a[i] == mxr) {
                if (n - 1 < 1ll * (a[i-1] - mnr + 1) * (mxc - mnc + 1)) {
                    ans = min(ans, 1ll * (a[i-1] - mnr + 1) * (mxc - mnc + 1));
                }
                else {
                    ll s1 = 1ll * (a[i-1] - mnr + 1) * (mxc - mnc + 2);
                    ll s2 = 1ll * (a[i-1] - mnr + 2) * (mxc - mnc + 1);
                    ans = min(ans, min(s1, s2));
                }
            }
            if (a[i] == mnr) {
                if (n - 1 < 1ll * (mxr - a[i+1] + 1) * (mxc - mnc + 1)) {
                    ans = min(ans, 1ll * (mxr - a[i+1] + 1) * (mxc - mnc + 1));
                }
                else {
                    ll s1 = 1ll * (mxr - a[i+1] + 1) * (mxc - mnc + 2);
                    ll s2 = 1ll * (mxr - a[i+1] + 2) * (mxc - mnc + 1);
                    ans = min(ans, min(s1, s2));
                }
            }
        }
        if (cb[j] == 1) {
            if (b[j] == mxc) {
                if (n - 1 < 1ll * (b[j-1] - mnc + 1) * (mxr - mnr + 1)) {
                    ans = min(ans, 1ll * (b[j-1] - mnc + 1) * (mxr - mnr + 1));
                }
                else {
                    ll s1 = 1ll * (b[j-1] - mnc + 1) * (mxr - mnr + 2);
                    ll s2 = 1ll * (b[j-1] - mnc + 2) * (mxr - mnr + 1);
                    ans = min(ans, min(s1, s2));
                }
            }
            if (b[j] == mnc) {
                if (n - 1 < 1ll * (mxc - b[j+1] + 1) * (mxr - mnr + 1)) {
                    ans = min(ans, 1ll * (mxc - b[j+1] + 1) * (mxr - mnr + 1));
                }
                else {
                    ll s1 = 1ll * (mxc - b[j+1] + 1) * (mxr - mnr + 2);
                    ll s2 = 1ll * (mxc - b[j+1] + 2) * (mxr - mnr + 1);
                    ans = min(ans, min(s1, s2));
                }
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) cf2114D();
    return 0;
}