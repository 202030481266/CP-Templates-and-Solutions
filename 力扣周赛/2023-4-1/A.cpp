class Solution {
public:
    int minNumber(vector<int>& nums1, vector<int>& nums2) {
        vector<int> a(10), b(10);
        for (int c : nums1) a[c] = 1;
        for (int c : nums2) b[c] = 1;

        for (int i = 1; i <= 9; ++i) {
            if (a[c] && b[c]) return i;
        }
        int x = 0;
        for (int i = 1; i <= 9; ++i) {
            if (a[i]) {
                x = i;
                break;
            }
        }
        int y = 0;
        for (int i = 1; i <= 9; ++i) {
            if (b[i]) {
                y = i;
                break;
            }
        }
        return min(x, y) * 10 + max(x, y);
    }
};