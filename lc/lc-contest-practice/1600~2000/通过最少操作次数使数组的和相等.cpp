class Solution {
public:
    // 考虑贡献进行统计
    int cal(vector<int>& cnt1, vector<int>& cnt2, int diff) {
        vector<int> h(7, 0);
        for (int i = 1; i <= 6; i++) {
            h[i - 1] += cnt1[i];
            h[6 - i] += cnt2[i];
        }
        int ans = 0;
        for (int i = 5; i && diff > 0; i--) {
            int temp = min((diff + i - 1) / i, h[i]);
            ans += temp;
            diff -= temp * i;
        }
        return ans;
    }
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size(), s1 = 0, s2 = 0;
        vector<int> cnt1(7), cnt2(7);
        for (auto c : nums1) s1 += c, cnt1[c]++;
        for (auto c : nums2) s2 += c, cnt2[c]++;
        if (s1 == s2) return 0;
        if (n > m * 6 || m > n * 6) return -1;
        if (s1 > s2) {
            return cal(cnt1, cnt2, s1 - s2);
        }
        return cal(cnt2, cnt1, s2 - s1);
    }
};