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

template <typename T, class Op>
struct ST {
    int N;
    Op op;
    std::vector<std::vector<T>> vec;
    
    ST(int n, Op operation) : N(n), op(operation) {
        vec.assign(N + 1, vector<T>(30));
    }

    ST(const std::vector<T>& a, Op operation) : op(operation) {
        N = a.size();
        int max_log = std::__lg(N) + 1;
        vec.assign(N, std::vector<T>(max_log));
        for (int i = 0; i < N; i++) {
            vec[i][0] = a[i];
        }
        
        for (int i = 1; i < max_log; i++) {
            for (int j = 0; j + (1 << i) <= N; j++) {
                vec[j][i] = op(vec[j][i - 1], vec[j + (1 << (i - 1))][i - 1]);
            }
        }
    }

    T query(int l, int r) {
        int k = std::__lg(r - l + 1);
        return op(vec[l][k], vec[r - (1 << k) + 1][k]);
    }
};

class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        auto mn_op = [](int a, int b) { return a < b ? a : b; };
        auto mx_op = [](int a, int b) { return a > b ? a : b; };
        ST<int, decltype(mn_op)> mn_table(nums, mn_op);
        ST<int, decltype(mx_op)> mx_table(nums, mx_op);
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            int l = i - 1, r = n;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                int mx = mx_table.query(i, mid);
                int mn = mn_table.query(i, mid);
                if (1ll * (mx - mn) * (mid - i + 1) <= k) l = mid;
                else r = mid;
            }
            ans += l - i + 1;
        }
        return ans;
    }
};
