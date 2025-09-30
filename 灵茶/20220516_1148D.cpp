#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 1003;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> arr;
    vector<int> desc, asc;
    for (int i = 0, u, v; i < n; ++i) {
        cin >> u >> v;
        arr.emplace_back(u, v);
        if (u > v) desc.push_back(i);
        else asc.push_back(i);
    }
    if (asc.size() >= desc.size()) {
        cout << asc.size() << '\n';
        ranges::sort(asc, [&](const int& i, const int& j) {
            return arr[i].second > arr[j].second;
        });
        for (int& p : asc) cout << p + 1 << ' ';
    }
    else {
        cout << desc.size() << '\n';
        ranges::sort(desc, [&](const int& i, const int& j) {
            return arr[i].first < arr[j].first;
        });
        for (int& p : desc) cout << p + 1 << ' ';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}