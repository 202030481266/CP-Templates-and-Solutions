#define ls rt<<1
#define rs rt<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
int tree[11][40010];
void Pushup(int rt, int g) {
    tree[g][rt] = min(tree[g][ls], tree[g][rs]);
}
void Update(int rt, int l, int r, int g, int p, int val) {
    if (l == r) {
        tree[g][rt] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) Update(lson, g, p, val);
    else Update(rson, g, p, val);
    Pushup(rt, g);
}
int Query(int rt, int l, int r, int g, int L, int R) {
    if (L <= l && r <= R) return tree[g][rt];
    int mid = (l + r) >> 1;
    if (R <= mid) return Query(lson, g, L, R);
    else if (L > mid) return Query(rson, g, L, R);
    else return min(Query(lson, g, L, mid), Query(rson, g, mid + 1, R));
}

class Solution {
public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        int n = nums.size(), m = andValues.size(), t[n + 1][14], dp[n + 1][m + 1];
        memset(tree, 0x3f, sizeof(tree));
        // 1 index
        for (int i = 1; i <= n; ++i) t[i][0] = nums[i - 1];
        for (int k = 1; k < 14; ++k) {
            for (int i = 1; i + (1 << k) - 1 <= n; ++i)
                t[i][k] = t[i][k - 1] & t[i + (1 << (k - 1))][k - 1];
        }
        auto query = [&](int l, int r) -> int {
            int k = 31 - __builtin_clz(r - l + 1);
            return t[l][k] & t[r - (1 << k) + 1][k]; 
        };
        auto find_right = [&](int ed, int val) {
            int l = 1, r = ed + 1; // [l, r)
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                if (query(mid, ed) <= val) l = mid;
                else r = mid;
            }
            return query(l, ed) == val ? l : -1;
        };
        auto find_left = [&](int ed, int val) {
            int l = 0, r = ed; // (l, r]
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                if (query(mid, ed) >= val) r = mid;
                else l = mid;
            }
            return query(r, ed) == val ? r : -1;
        };
        // dp + 二分 
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0] = 0;
        Update(1, 0, n, 0, 0, 0); // [0, n]
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int r = find_right(i, andValues[j - 1]), l = find_left(i, andValues[j - 1]);
                if (r != -1) {
                    // 存在一个点可以满足，那么l必然不是-1
                    int res = Query(1, 0, n, j - 1, l - 1, r - 1);
                    if (res != 0x3f3f3f3f) {
                        dp[i][j] = res + nums[i - 1];
                        Update(1, 0, n, j, i, dp[i][j]);
                    }
                }
            }
        }
        return dp[n][m] == 0x3f3f3f3f ? -1 : dp[n][m];
    }
};