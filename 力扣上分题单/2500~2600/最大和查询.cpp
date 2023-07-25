typedef tuple<int, int, int> tiii;
class Solution {
    static constexpr int N = 400010;
    int tr[N];
public:
    // sufix BIT
    int lowbit(int x) { return x & -x; }
    void update(int x, int val) {
        for (; x; x -= lowbit(x))
            tr[x] = max(tr[x], val);
    }
    int query(int x) {
        int res = -1;
        for (; x < N; x += lowbit(x))
            res = max(res, tr[x]);
        return res;
    }
    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = nums1.size(), m = queries.size();
        memset(tr, -1, sizeof(tr));
        vector<int> nums;
        for (int i = 0; i < n; ++i) {
            nums.push_back(nums1[i]);
            nums.push_back(nums2[i]);
        }
        for (int i = 0; i < m; ++i) {
            nums.push_back(queries[i][0]);
            nums.push_back(queries[i][1]);
        }
        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        vector<tiii> arr;
        vector<tiii> qs;
        // I prefer the 1-index in BIT
        for (int i = 0; i < n; ++i) {
            int tmp1 = lower_bound(nums.begin(), nums.end(), nums1[i]) - nums.begin() + 1;
            int tmp2 = lower_bound(nums.begin(), nums.end(), nums2[i]) - nums.begin() + 1;
            arr.emplace_back(tmp1, tmp2, nums1[i] + nums2[i]);
        }
        sort(arr.begin(), arr.end());
        for (int i = 0; i < m; ++i) {
            int tmp1 = lower_bound(nums.begin(), nums.end(), queries[i][0]) - nums.begin() + 1;
            int tmp2 = lower_bound(nums.begin(), nums.end(), queries[i][1]) - nums.begin() + 1;
            qs.emplace_back(tmp1, tmp2, i);
        }
        sort(qs.begin(), qs.end());
        vector<int> ans(m);
        int p = n - 1;
        // add is better than delete
        for (int i = m - 1; i >= 0; --i) {
            int x = get<0>(qs[i]), y = get<1>(qs[i]), id = get<2>(qs[i]);
            while (p >= 0 && get<0>(arr[p]) >= x) {
                update(get<1>(arr[p]), get<2>(arr[p]));
                --p;
            }
            ans[id] = query(y);
        }
        return ans;
    }
};