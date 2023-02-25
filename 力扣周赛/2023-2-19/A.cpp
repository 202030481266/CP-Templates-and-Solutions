class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        int l = 0, r = 0;
        int n = nums1.size(), m = nums2.size();
        vector<vector<int>> ans;
        while (l < n || r < m) {
            if (l == n) ans.emplace_back(nums2[r++]);
            else if (r == m) ans.emplace_back(nums1[l++]);
            else {
                if (nums1[l][0] == nums2[r][0]) {
                    int id = nums1[l][0];
                    ans.emplace_back(vector<int>{id, nums1[l++][1] + nums2[r++][1]});
                } 
                else if (nums1[l][0] < nums2[r][0])
                    ans.emplace_back(nums1[l++]);
                else ans.emplace_back(nums2[r++]);
            }
        }
        return ans;
    }
};