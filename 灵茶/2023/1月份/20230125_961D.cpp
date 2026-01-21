#include <bits/stdc++.h>
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
    if (n <= 4) {
        cout << "YES" << '\n';
        return;
    }
    vector<pii> points(n);
    for (auto& [x, y] : points) cin >> x >> y;
    auto vec = [&](int i, int j) -> pii {
        return {points[j].first - points[i].first, points[j].second - points[i].second};
    };
    auto cal = [](const pii& x, const pii& y) -> bool {
        return 1LL * x.first * y.second - 1LL * x.second * y.first == 0;
    };
    vi another;
    int find = 0;
    for (int i = 0; i < 5 && !find; ++i) {
        for (int j = i + 1; j < 5 && !find; ++j) {
            for (int k = j + 1; k < 5 && !find; ++k) {
                pii vec1 = vec(i, j);
                pii vec2 = vec(i, k);
                if (cal(vec1, vec2)) {
                    find = 1;
                    for (int x = 0; x < n; ++x) {
                        pii vc = vec(i, x);
                        if (!cal(vec1, vc)) another.push_back(x);
                    }
                }
            }
        }
    }
    if (!find) {
        cout << "NO" << '\n';
        return;
    }
    if (another.size() <= 2) {
        cout << "YES" << '\n';
        return;
    }
    pii vec3 = vec(another[0], another[1]);
    for (int i = 2; i < another.size(); ++i) {
        pii vc = vec(another[0], another[i]);
        if (!cal(vec3, vc)) {
            cout << "NO" << '\n';
            return;
        }
    }
    cout << "YES" << '\n';
}
    

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
