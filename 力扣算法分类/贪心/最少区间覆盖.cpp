// https://leetcode.cn/problems/minimum-number-of-taps-to-open-to-water-a-garden/description/
// 经典的贪心问题


class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int> r(n + 1);

        for (int i = 0; i < n + 1; ++i) {
            int rr = ranges[i];
            if (i > rr) r[i - rr] = i + rr;
            else r[0] = max(r[0], i + rr);
        }
        int ans = 0, cr = 0, nr = 0;
        for (int i = 0; i < n; ++i) {
            nr = max(nr, r[i]);
            if (i == cr) {
                if (nr == i) return -1;
                ++ans;
                cr = nr;
            }
        }
        return ans;
    }
};