#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

using t3i = tuple<int, int, int>;

template<typename T, typename F>
struct ST {
    int N;
    std::vector<std::vector<T>> vec;
    F op;

    ST(const std::vector<T>& a, F _op) : N(a.size()), op(_op) {
        if (N == 0) return;
        int logN = std::log2(N) + 1;
        vec.assign(N, std::vector<T>(logN));
        for (int i = 0; i < N; ++i) {
            vec[i][0] = a[i];
        }
        ST_work();
    }

    void ST_work() {
        if (N == 0) return;
        int t = std::log2(N) + 1;
        for (int i = 1; i < t; ++i) {
            for (int j = 0; j + (1 << i) <= N; ++j) {
                vec[j][i] = op(vec[j][i - 1], vec[j + (1 << (i - 1))][i - 1]);
            }
        }
    }

    T query(int l, int r) {
        int k = std::log2(r - l + 1);
        return op(vec[l][k], vec[r - (1 << k) + 1][k]);
    }
};

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();
        auto mx_f = [](int a, int b) { return std::max(a, b); };
        auto mn_f = [](int a, int b) { return std::min(a, b); };
        ST<int, decltype(mx_f)> mx_table(nums, mx_f);
        ST<int, decltype(mn_f)> mn_table(nums, mn_f);
        priority_queue<t3i> q;
        q.emplace(mx_table.query(0, n - 1) - mn_table.query(0, n - 1), 0, n - 1);
        ll ans = 0;
        unordered_set<ll> use;
        use.insert(n - 1);
        while (k--) {
            auto [score, l, r] = q.top();
            q.pop();
            ans += score;
            use.insert(1ll * l * n + r);
            if (l + 1 <= r && use.find(1ll * (l + 1) * n + r) == use.end()) {
                q.emplace(mx_table.query(l + 1, r) - mn_table.query(l + 1, r), l + 1, r);
                use.insert(1ll * (l + 1) * n + r);
            }
            if (r - 1 >= l && use.find(1ll * l * n + r - 1) == use.end()) {
                q.emplace(mx_table.query(l, r - 1) - mn_table.query(l, r - 1), l, r - 1);
                use.insert(1ll * l * n + r - 1);
            }
        }
        return ans;
    }
};