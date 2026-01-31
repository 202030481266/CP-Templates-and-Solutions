#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r
class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        int n = heights.size(), m = queries.size();

        vector<int> ans;
        vector<int> mx(n * 4 + 10);

        function<void(int, int, int)> build = [&](int rt, int l, int r) {
            if (l == r) {
                mx[rt] = heights[l - 1]; // 
                return;
            }
            build(lson);
            build(rson);
            mx[rt] = max(mx[ls], mx[rs]);
        };

        function<int(int, int, int, int, int)> query = [&](int rt, int l, int r, int L, int R) -> int {
            if (L <= l && r <= R) return mx[rt];
            if (R <= mid) return query(lson, L, R);
            else if (L > mid) return query(rson, L, R);
            else return max(query(lson, L, mid), query(rson, mid + 1, R));
        };

        build(1, 1, n);

        int res, right, left;
        for (int i = 0; i < m; ++i) {
            int x = queries[i][0], y = queries[i][1], bigger = max(heights[x], heights[y]);
            // 两种特殊情况
            if (x == y) {
                ans.push_back(x);
                continue;
            }
            int small_id = min(x, y), big_id = max(x, y);
            if (heights[big_id] > heights[small_id]) {
                ans.push_back(big_id);
                continue;
            }
            left = big_id + 2, right = n, res = -1;
            while (left <= right) {
                int middle = (left + right) >> 1;
                if (query(1, 1, n, left, middle) > bigger) {
                    if (heights[middle - 1] > bigger) res = middle;
                    right = middle - 1;
                }
                else left = middle + 1;
            }
            ans.push_back((res == -1 ? -1 : res - 1));
        }
        return ans;
    }
};