#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 矩阵快速幂板子题目
const ll MOD = 1e9+7;

// 矩阵乘法
vector<vector<ll>> multiply(const vector<vector<ll>>& A, const vector<vector<ll>>& B) {
    int n = A.size();
    vector<vector<ll>> C(n, vector<ll>(n, 0));
    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            for(int k=0; k<n; ++k)
                C[i][j] = (C[i][j] + A[i][k]*B[k][j]%MOD) % MOD;
    return C;
}

// 矩阵快速幂
vector<vector<ll>> matrix_pow(vector<vector<ll>> A, ll n) {
    int size = A.size();
    vector<vector<ll>> result(size, vector<ll>(size, 0));
    // 初始化为单位矩阵
    for(int i=0; i<size; ++i)
        result[i][i] = 1;
    while(n > 0) {
        if(n % 2 == 1)
            result = multiply(result, A);
        A = multiply(A, A);
        n /= 2;
    }
    return result;
}


class Solution {
public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        vector matrix(26, vector<ll>(26));
        for (int i = 0; i < 26; ++i) {
            for (int j = 1; j <= nums[i]; j++) {
                matrix[i][(i + j) % 26] = 1;
            }
        }
        auto res = matrix_pow(matrix, t);
        vector<ll> dp(26);
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                dp[i] = (dp[i] + res[i][j]) % mod;
            }
        }
        ll ans = 0;
        for (char c : s) {
            ans = (ans + dp[c - 'a']) % mod;
        }
        return ans;
    }
};