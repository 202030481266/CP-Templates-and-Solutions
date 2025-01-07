class Solution {
public:
    long long minimumTotalCost(vector<int> &nums1, vector<int> &nums2) {
        // 和众数有关系
        long ans = 0L;
        int swap_cnt = 0, mode_cnt = 0, mode, n = nums1.size(), cnt[n + 1];
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; ++i)
            if (int x = nums1[i]; x == nums2[i]) {
                ans += i;
                ++swap_cnt;
                ++cnt[x];
                if (cnt[x] > mode_cnt) {
                    mode_cnt = cnt[x];
                    mode = x;
                }
            }

        for (int i = 0; i < n && mode_cnt * 2 > swap_cnt; ++i) {
            int x = nums1[i], y = nums2[i];
            if (x != y && x != mode && y != mode) {
                ans += i;
                ++swap_cnt;
            }
        }
        return mode_cnt * 2 > swap_cnt ? -1 : ans;
    }
};

