#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 200005;

int n;
ll s, x;
ll sum[maxn], arr[maxn];

void solve() {
    cin >> n >> s >> x;
    unordered_map<ll, int> cnt;
    cnt.reserve(n);
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i-1] + arr[i];
        if (arr[i] < x) arr[i] = 0;
        else if (arr[i] == x) arr[i] = 1;
        else arr[i] = inf;
    }
    int left1 = 1, left2 = 1;
    int p1 = 0, p2 = 1;
    ll s1 = 0, s2 = 0, ans = 0;
    cnt[0] = 1; //[p1,p2)
    for (int i = 1; i <= n; ++i) {
        s1 += arr[i];
        s2 += arr[i];
        while (s1 >= inf) { // <=inf
            s1 -= arr[left1++];
        }
        while (s2 > 0) { // ==0
            s2 -= arr[left2++];
        }
        // [left1, left2)
        // [left1-1, left2-1)
        if (left2 > left1) {
            while (p2 < left2 - 1) {
                cnt[sum[p2]]++;
                p2++;
            }
            while (p1 < left1 - 1) {
                cnt[sum[p1]]--;
                p1++;
            }
            ans += cnt[sum[i]-s];
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}