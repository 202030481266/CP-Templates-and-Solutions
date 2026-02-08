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


class Solution {
public:
    vector<long long> mergeAdjacent(vector<int>& nums) {
        int n = nums.size();
        vl ans(n);
        int ptr = 0;
        for (int i = 0; i < n; ++i) {
            ans.push_back(nums[i]);
            while (ptr >= 2 && ans[ptr - 1] == ans[ptr - 2]) {
                ll sum = ans[ptr - 1] * 2;
                ptr -= 2;
                ans[ptr++] = sum;
            }
        }
        ans.resize(ptr);
        return ans;
    }
};