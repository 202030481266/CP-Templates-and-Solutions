#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
class Solution {
    vector<long long> mx;
public:
    long long query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return mx[rt];
        if (R <= mid) return query(lson, L, R);
        else if (L > mid) return query(rson, L, R);
        else return max(query(lson, L, mid), query(rson, mid + 1, R));
    }
    void update(int rt, int l, int r, int p, long long val) {
        if (l == r) {
            mx[rt] = max(mx[rt], val);
            return;
        }
        if (p <= mid) update(lson, p, val);
        else update(rson, p, val);
        mx[rt] = max(mx[ls], mx[rs]);
    }
    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> arr(n);

        for (int i = 0; i < n; ++i)
            arr[i] = nums[i] - i;

        // LIS
        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());

        n = arr.size();

        // 对于同一个 bi 来讲，我们只需要记录它的最大值
        mx.resize(n * 4 + 10);
        long long ans = -2e18;

        for (int i = 0; i < nums.size(); ++i) {
            int idx = lower_bound(arr.begin(), arr.end(), nums[i] - i) - arr.begin() + 1;
            long long tmp = query(1, 1, n, 1, idx) + nums[i];
            update(1, 1, n, idx, tmp);
            ans = max(ans, tmp);
        }
        return ans;
    }
};