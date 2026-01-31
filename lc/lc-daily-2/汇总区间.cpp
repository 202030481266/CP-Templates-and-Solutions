class Solution {
public:
    string f(int a, int b) {
        if (a == b) return to_string(a);
        else return to_string(a) + "->" + to_string(b);
    }
    vector<string> summaryRanges(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return {};
        vector<string> ans;
        int l = -1, r = -1;
        for (int i = 0; i < n; ++i) {
            // cout << i << ' ' << l << ' ' << r << endl;
            if (l == -1) l = r = nums[i];
            else if (nums[i] == r + 1) ++r;
            else {
                ans.push_back(f(l, r));
                l = r = nums[i];
            }
        }
        ans.push_back(f(l, r));
        return ans;
    }
};