// https://leetcode.cn/problems/optimal-division/description/
// 脑筋急转弯, 把除法看成是分子除以分母，那么就能推出结论：
// 分子最大是nums[0]，分母最小是nums[1]/nums[2]/nums[3]....
// 第二个一定要除，后面全乘


class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        int n = nums.size();        
        if (n == 1) {
            return to_string(nums[0]);
        }
        if (n == 2) {
            return to_string(nums[0]) + "/" + to_string(nums[1]);
        }
        string res = to_string(nums[0]) + "/(" + to_string(nums[1]);
        for (int i = 2; i < n; i++) {
            res.append("/" + to_string(nums[i]));
        }
        res.append(")");
        return res;
    }
};

