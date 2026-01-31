#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;


void solve() {
    int n;
    cin >> n;
    vi a(n);
    for (int& v : a) cin >> v;
    auto construct = [&](const vi& arr) -> vl {
        if (n == 1) return {0};
        vl ans(n);
        if (arr[0] == arr[n - 1]) {
            ll sum = 0;
            for (int i = 1; i < n - 1; ++i) {
                ans[i] = i;
                sum += ans[i] * arr[i];
            }
            if (arr[0] == 1) {
                if (sum <= 0) {
                    ans[n - 1] = -sum + n - 1;
                    ans[0] = 1 - n;
                }
                else {
                    ans[n - 1] = n - 1;
                    ans[0] = 1 - n - sum;
                }
            }
            else {
                if (sum >= 0) {
                    ans[n - 1] = sum + n - 1;
                    ans[0] = 1 - n;
                }
                else {
                    ans[n - 1] = n - 1;
                    ans[0] = 1 - n + sum;
                }
            }
        }
        else {
            int cnt = 0, flag = 0, p = -1;
            for (int i = n - 1; i >= 0; --i) {
                if (arr[i] == arr[n - 1]) ++cnt;
                else --cnt;
                if (cnt < 0) {
                    flag = 1;
                    p = i;
                    break;
                }
            }
            if (!flag) return {};
            ll sum = 0;
            for (int i = 0; i < p; ++i) {
                ans[i] = i;
                sum += ans[i] * arr[i];
            }
            ll sub = 0;
            for (int i = p + 1, j = 1; i < n; ++i, ++j) sub += 1LL * j * arr[i];
            // p + sub
            ll pre = abs(sum);
            for (int i = p; i < n - 1; ++i) {
                ans[i] = i + sub * arr[n - 1] + pre;
                sum += ans[i] * arr[i];
            }
            ans[n - 1] = arr[n - 1] * -sum;
        }
        return ans;
    };
    auto ans = construct(a);
    if (ans.empty()) {
        reverse(a.begin(), a.end());
        ans = construct(a);
        if (!ans.empty()) {
            reverse(ans.begin(), ans.end());
            for (ll& v : ans) v *= -1;
        }
    }
    if (!ans.empty()) {
        cout << "Yes" << '\n';
        for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
    }
    else cout << "No" << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
