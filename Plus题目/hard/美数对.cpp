class Solution {
public:
    // 分治算法或者线性扫描
    using pii = pair<int, int>;
    using ll = long long;

    ll dist(int x1, int y1, int x2, int y2) {
        return 1ll * abs(x1 - x2) + 1ll * abs(y1 - y2);
    }

    ll comp(int x, int y, int xx, int yy) {
        return (x == xx ? y < yy : x < xx);
    }

    vector<int> beautifulPair(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        unordered_map<ll, int> cnt;
        vector<int> ids;
        vector<int> ans;
        // 需要判重，不然算法复杂度会很高，不过出现重复的点那就很简单了
        for (int i = 0; i < n; ++i) {
            ll tmp = nums1[i] * 1ll * (n + 1) + nums2[i];
            if (!cnt.count(tmp)) {
                cnt[tmp] = i;
                ids.push_back(i);
            }
            else {
                if (ans.empty()) ans = {cnt[tmp], i};
                else if (comp(cnt[tmp], i, ans[0], ans[1]))
                    ans = {cnt[tmp], i};
            }
        }
        if (!ans.empty()) return ans;
        sort(ids.begin(), ids.end(), [&](int i, int j) {
            return (nums1[i] != nums1[j] ? nums1[i] < nums1[j]
                                         : nums2[i] < nums2[j]);
        });
        if (ids.size() < 2) {
            return {ids[0], 1 - ids[0]};
        }
        int l = 0, r = 2;
        ll res =
            dist(nums1[ids[0]], nums2[ids[0]], nums1[ids[1]], nums2[ids[1]]);
        if (ids[0] < ids[1])
            ans = {ids[0], ids[1]};
        else
            ans = {ids[1], ids[0]};
        while (r < ids.size()) {
            while (l < r && nums1[ids[r]] - nums1[ids[l]] > res)
                ++l;
            for (int i = l; i < r; ++i) {
                ll tmp = dist(nums1[ids[i]], nums2[ids[i]], nums1[ids[r]],
                              nums2[ids[r]]);
                if (tmp < res) {
                    res = tmp;
                    ans = {min(ids[i], ids[r]), max(ids[i], ids[r])};
                } else if (tmp == res &&
                           comp(min(ids[i], ids[r]), max(ids[i], ids[r]),
                                ans[0], ans[1])) {
                    ans = {min(ids[i], ids[r]), max(ids[i], ids[r])};
                }
            }
            ++r;
        }
        return ans;
    }
};