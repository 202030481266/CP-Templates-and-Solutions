#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

#define SEGMENT_TREE 1

#if SEGMENT_TREE 
#define mid ((l + r) >> 1)
#define ls rt<<1
#define rs rt<<1|1
#define lson ls, l, mid
#define rson rs, mid+1, r
#endif

// 一道十分精彩的线段树题目
const int maxn = 1e5 + 7;
int p, val[maxn << 2], dp[maxn << 2][5];

void pushup(int rt) {
    for (int i = 0; i < p; ++i) dp[rt][i] = dp[ls][i];
    for (int i = 0; i < p; ++i) {
        dp[rt][(i * val[ls]) % p] += dp[rs][i];
    }
    val[rt] = (val[ls] * val[rs]) % p;
}
void build(const vector<int>& nums, int rt, int l, int r) {
    if (l == r) {
        val[rt] = nums[l];
        memset(dp[rt], 0, sizeof(dp[rt]));
        dp[rt][nums[l]] = 1;
        return;
    }
    build(nums, lson);
    build(nums, rson);
    pushup(rt);
}
void update(int rt, int l, int r, int pos, int value) {
    if (l == r) {
        dp[rt][val[rt]] = 0;
        val[rt] = value;
        dp[rt][value] = 1;
        return;
    }
    if (pos <= mid) update(lson, pos, value);
    else update(rson, pos, value);
    pushup(rt);
}
pair<int, int> query(int rt, int l, int r, int pos, int x) {
    if (l == r) {
        return {dp[rt][x], val[rt]};
    }
    if (pos > mid) return query(rson, pos, x);
    auto [result, sum] = query(lson, pos, x);
    for (int i = 0; i < p; ++i) {
        if (i * sum % p == x) result += dp[rs][i];
    }
    return {result, sum * val[rs] % p};
}

class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n = nums.size();
        p = k;
        for (int& v : nums) v %= p;
        build(nums, 1, 0, n - 1);
        vector<int> ans;
        for (auto& q : queries) {
            int index = q[0], value = q[1], start = q[2], x = q[3];
            update(1, 0, n - 1, index, value % p);
            auto [result, _] = query(1, 0, n - 1, start, x);
            ans.emplace_back(result);
        }
        return ans;
    }
};