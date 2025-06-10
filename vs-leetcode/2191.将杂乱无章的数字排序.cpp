/*
 * @lc app=leetcode.cn id=2191 lang=cpp
 *
 * [2191] 将杂乱无章的数字排序
 */

// @lc code=start
class Solution {
public:
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        int n = nums.size();
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        vector<int> val;
        for (int v : nums) {
            vector<int> tmp;
            if (v == 0) {
                v = mapping[0];
            }
            else {
                while (v) {
                    tmp.push_back(mapping[v % 10]);
                    v /= 10;
                }
                for (int i = (int)tmp.size() - 1; i >= 0; --i)
                    v = v * 10 + tmp[i];
            }
            val.push_back(v);
        }
        ranges::sort(ids, [&](int i, int j){
            return val[i] == val[j] ? i < j : val[i] < val[j];
        });
        vector<int> ans;
        for (int i : ids) ans.push_back(nums[i]);
        return ans;
    }
};
// @lc code=end

