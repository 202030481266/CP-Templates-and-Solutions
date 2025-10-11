#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 1000005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

void cal_right(const vi& arr, vi& right, int flag) {
    stack<int> stk;
    auto comp = [&](int i, int j) -> bool {
        if (flag == 1) return arr[i] <= arr[j];
        if (flag == 0) return arr[i] >= arr[j];
        return arr[i] > arr[j];
    };
    for (int i = 0; i < arr.size(); ++i) {
        while (!stk.empty() && comp(stk.top(), i)) {
            right[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }
    while (!stk.empty()) {
        right[stk.top()] = INT(arr.size());
        stk.pop();
    }
}

void cal_left(vi& arr, vi& left, int flag) {
    stack<int> stk;
    for (int i = INT(arr.size()) - 1; i >= 0; --i) {
        while (!stk.empty() && (flag ? arr[stk.top()] < arr[i] : arr[stk.top()] > arr[i])) {
            left[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }
    while (!stk.empty()) {
        left[stk.top()] = -1;
        stk.pop();
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n), c(n * 2);
    for (int &v : a) cin >> v;
    for (int &v : b) cin >> v;
    for (int i = 0; i < n; ++i) c[i] = a[i];
    for (int i = n; i < n * 2; ++i) c[i] = b[i - n];
    ranges::sort(c);
    auto dup = ranges::unique(c);
    c.erase(dup.begin(), dup.end());
    for (int &v : a) v = INT(ranges::lower_bound(c, v) - c.begin());
    for (int &v : b) v = INT(ranges::lower_bound(c, v) - c.begin());
    vector<int> al(n), ar(n), bl(n), br(n), brr(n);
    cal_right(a, ar, 1);
    cal_left(a, al, 1);
    cal_right(b, br, 0);
    cal_left(b, bl, 0);
    cal_right(b, brr, 2);
    vii group(c.size());
    for (int i = 0; i < n; ++i) group[b[i]].push_back(i);
    vi p(c.size());
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        int v = a[i];
        while (p[v] < group[v].size() && (group[v][p[v]] <= al[i] || br[group[v][p[v]]] <= i)) p[v]++;
        if (p[v] < group[v].size()) {
            int x = group[v][p[v]];
            if (x < ar[i] && i > bl[x]) {
                if (x <= i) {
                    ans += 1ll * (x - max(al[i], bl[x])) * (min(br[x], ar[i]) - i);
                    if (br[x] < ar[i] && brr[x] > br[x]) {
                        ans += 1ll * (i - max(bl[x], al[i])) * (min(ar[i], brr[x]) - br[x]);
                    }
                }
                else {
                    ans += 1ll * (i - max(bl[x], al[i])) * (min(brr[x], ar[i]) - x);
                }
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
