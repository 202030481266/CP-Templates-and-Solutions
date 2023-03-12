// https://leetcode.cn/problems/get-the-maximum-score/
// 序列DP，关键点在于按照单调递增的顺序进行DP的转移，非常巧妙
// 注意最短路会超时


class Solution {
private:
    static constexpr int mod = 1000000007;
    
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        long long best1 = 0, best2 = 0;
        int i = 0, j = 0;
        while (i < m || j < n) {
            if (i < m && j < n) {
                if (nums1[i] < nums2[j]) {
                    best1 += nums1[i];
                    ++i;
                }
                else if (nums1[i] > nums2[j]) {
                    best2 += nums2[j];
                    ++j;
                }
                else {
                    long long best = max(best1, best2) + nums1[i];
                    best1 = best2 = best;
                    ++i;
                    ++j;
                }
            }
            else if (i < m) {
                best1 += nums1[i];
                ++i;
            }
            else if (j < n) {
                best2 += nums2[j];
                ++j;
            }
        }
        return max(best1, best2) % mod;
    }
};  

