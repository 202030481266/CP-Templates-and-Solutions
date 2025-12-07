#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 100005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int fenwick[MAXN], N;

inline int lowbit(int i) {
    return i & -i;
}

void update(int pos, int val) {
    while (pos <= N) {
        fenwick[pos] += val;
        pos += lowbit(pos);
    }
}

int query(int pos) {
    int res = 0;
    while (pos) {
        res += fenwick[pos];
        pos -= lowbit(pos);
    }
    return res;
}

class Solution {
public:
    long long minInversionCount(vector<int>& nums, int k) {
        vector<int> arr(nums.begin(), nums.end());
        int n = nums.size();
        ranges::sort(arr);
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        N = arr.size();
        memset(fenwick, 0, (N + 1) * sizeof(int));
        for (int& v : nums) v = lower_bound(arr.begin(), arr.end(), v) - arr.begin() + 1;
        ll ans = 1ll * n * n, cur = 0;
        int l = 0;
        for (int i = 0; i < n; ++i) {
            cur += i - l - query(nums[i]);
            update(nums[i], 1);
            while (i - l + 1 > k) {
                cur -= query(nums[l] - 1);
                update(nums[l++], -1);
            }
            if (i - l + 1 == k) ans = min(ans, cur);
        }
        return ans;
    }
};