class Solution {
public:
    vector<int> prefix_function(vector<int>& s) {
        vector<int> p(s.size());
        int k = 0;
        for (int i = 1; i < s.size(); i++) {
            while (k > 0 && s[k] != s[i])
                k = p[k - 1];
            if (s[k] == s[i])
                ++k;
            p[i] = k;
        }
        return p;
    }
    int find_substring(vector<int>& haystack, vector<int>& needle) {
        int m = needle.size();
        if (m == 0)
            return 0;
        vector<int> p = prefix_function(needle);
        int res = 0;
        for (int i = 0, k = 0; i < haystack.size(); i++) {
            while (k > 0 && needle[k] != haystack[i])
                k = p[k - 1];
            if (needle[k] == haystack[i])
                ++k;
            if (k == m) {
                ++res;
                k = p[k - 1];
            }
        }
        return res;
    }
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        int n = nums.size(), m = pattern.size();
        // kmp变种
        vector<int> arr;
        for (int i = 0; i + 1 < n; ++i) {
            if (nums[i + 1] > nums[i]) arr.push_back(1);
            else if (nums[i + 1] == nums[i]) arr.push_back(0);
            else arr.push_back(-1);
        }
        return find_substring(arr, pattern);
    }
};