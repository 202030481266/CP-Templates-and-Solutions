class Solution {
public:
    int minOrAfterOperations(vector<int> &nums, int k) {
        int ans = 0, mask = 0;
        for (int b = 29; b >= 0; b--) {
            mask |= 1 << b;
            int cnt = 0, and_res = -1; // -1 的二进制全为 1
            for (int x : nums) {
                and_res &= x & mask;
                if (and_res) {
                    cnt++; // 合并 x，操作次数加一
                } else {
                    and_res = -1; // 准备合并下一段
                }
            }
            if (cnt > k) {
                ans |= 1 << b; // 答案的这个比特位必须是 1
                mask ^= 1 << b; // 后面不考虑这个比特位
            }
        }
        return ans;
    }
};

