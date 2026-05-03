#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


// 比较有意思的一道题目

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();
        vi suf(n);
        vi pre(n);
        pre[0] = nums[0];
        for (int i = 1; i < n; ++i) pre[i] += pre[i - 1] + nums[i];
        suf[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) suf[i] += suf[i + 1] + nums[i];
        vi a(n), b(n);
        a[n - 1] = 0;
        for (int i = n - 2; i >= 0; --i) {
            a[i] = a[i + 1] + suf[i + 1];
        }
        for (int i = 1; i < n; ++i) {
            b[i] = b[i - 1] - pre[i - 1] + n * nums[i - 1]; 
        }
        int ans = numeric_limits<int>::min();
        for (int i = 0; i < n; ++i) {
            ans = max(ans, a[i] + b[i]);
        }
        return ans;
    }
};