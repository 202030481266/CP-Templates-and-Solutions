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

struct ST {
    long long N;
    vector<vector<long long>> vec;

    ST() {}
    ST(int n) {
        N = n;
        vec.resize(N);
        for (auto &v : vec) v = vector<long long>(30, 0);
        for (int i = 0; i < N; i++) {
            cin >> vec[i][0]; 
        }
    }
    ST(const vector<long long>&a) {
        vec.resize(a.size());
        N = a.size();
        for (auto &v : vec) v = vector<long long>(30, 0);
        for (int i = 0; i < N; i++) vec[i][0] = a[i];
    }
    void ST_work() {
        int t = log(N) / log(2) + 1;
        for (int i = 1; i < t; i++) {
            for (int j = 0; j + (1 << i) - 1 < N; j++) {
                vec[j][i] = max(vec[j][i - 1], vec[j + (1 << (i - 1))][i - 1]);
            }
        }
    }
    long long query(int l, int r) {
        int k = log(r - l + 1) / log(2);
        return max(vec[l][k], vec[r - (1 << k) + 1][k]);
    }
};

class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        // 子数组越长cost越大
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
        }
    }
};
