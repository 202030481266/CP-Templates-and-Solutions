class Solution {
public:
    long long minOperations(vector<int>& nums1, vector<int>& nums2, int k) {
        long long pos = 0, neg = 0; 
        int n = nums1.size();
        for (int i = 0; i < n; ++i) {
            if (nums1[i] == nums2[i]) continue;
            if (k == 0) return -1;
            if (nums1[i] > nums2[i]) {
                int temp = nums1[i] - nums2[i];
                if (temp % k) return -1;
                pos += (temp / k);
            } else {
                int temp = nums2[i] - nums1[i];
                if (temp % k) return -1;
                neg += (temp / k);
            }
        }
        if (pos == neg) return pos;
        else return -1;
    }
};