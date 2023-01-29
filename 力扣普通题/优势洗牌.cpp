class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        multiset<int> s;
        for (auto c : nums1) s.emplace(c);
        for (auto c : nums2) {
            auto it = s.upper_bound(c);
            if (it == s.end()) {
                ans.emplace_back(*s.begin());
                s.erase(s.begin());
            } 
            else {
                ans.emplace_back(*it);
                s.erase(it);
            }
        }
        return ans;
    }
};