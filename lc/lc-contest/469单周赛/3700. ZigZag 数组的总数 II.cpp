#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

vector<vector<int>> mul(const vector<vector<int>>& x, const vector<vector<int>>& y) {
    vector result(x.size(), vector<int>(y[0].size()));
    for (int i = 0; i < x.size(); ++i) {
        for (int j = 0; j < y[0].size(); ++j) {
            for (int k = 0; k < x[0].size(); ++k) {
                result[i][j] += 1LL * x[i][k] * y[k][j] % MOD; // NOLINT(*-narrowing-conversions)
                result[i][j] %= MOD;
            }
        }
    }
    return result;
}
vector<vector<int>> quick_matrix_pow(vector<vector<int>> matrix, int x) {
    vector result(matrix.size(), vector<int>(matrix[0].size()));
    for (int i = 0; i < matrix.size(); ++i) result[i][i] = 1;
    for (; x; x >>= 1) {
        if (x & 1) result = mul(result, matrix);
        matrix = mul(matrix, matrix);
    }
    return result;
}

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        vector A(m, vector<int>(m));
        vector B(m, vector<int>(m));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < i; ++j) A[i][j] = 1;
            for (int j = m - 1; j > i; --j) B[i][j] = 1;
        }
        auto AB = mul(A, B);
        auto BA = mul(B, A);
        vector init(m, vector(1, 1));
        auto result1 = quick_matrix_pow(AB, (n - 1) / 2);
        auto result2 = quick_matrix_pow(BA, (n - 1) / 2);
        if (n % 2 == 0) {
            result1 = mul(result1, A);
            result2 = mul(result2, B);
        }
        auto r1 = mul(result1, init);
        auto r2 = mul(result2, init);
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            ans = (ans + r1[i][0]) % MOD;
            ans = (ans + r2[i][0]) % MOD;
        }
        return ans;
    }
};