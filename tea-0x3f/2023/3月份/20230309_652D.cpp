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

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>   

using namespace __gnu_pbds;

typedef tree<
    int, 
    null_type, 
    less<int>, 
    rb_tree_tag, 
    tree_order_statistics_node_update
> ordered_set;

void solve() {
    int n;
    cin >> n;
    vector<pii> arr(n);
    for (auto& [l, r] : arr) cin >> l >> r;
    vi ids(n);
    iota(ids.begin(), ids.end(), 0);
    ranges::sort(ids, [&](int i, int j) { return arr[i].second < arr[j].second; });
    ordered_set os;
    vi ans(n);
    for (int i = 0; i < n; ++i) {
        int idx = ids[i];
        ans[idx] = i - os.order_of_key(arr[idx].first);
        os.insert(arr[idx].first);
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
