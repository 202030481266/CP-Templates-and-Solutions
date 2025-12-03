#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;

#define INT(x) static_cast<int>(x)

int n, d, arr[MAXN], mx[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> d;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    int r = d;
    for (int i = n; i >= 1; --i) {
        if (arr[i] < 0 || arr[i] > 0) {
            // x + arr[i] <= r -> x <= r - arr[i]
        	r = min(d, r - arr[i]);
        }
        else {
        	if (r < 0) {
        		cout << -1 << '\n';
        		return 0;
        	}
        }
        mx[i] = r;
    }
    if (mx[1] < 0) {
    	cout << -1 << '\n';
    	return 0;
    }
    int cur = 0, ans = 0;
    for (int i = 1; i <= n; ++i) {
    	cerr << mx[i] << ' ';
        cur += arr[i];
        if (arr[i] == 0) {
            if (cur < 0) {
                ++ans;
                cur = mx[i];
            }
        }
    }
    cout << ans << '\n';
}