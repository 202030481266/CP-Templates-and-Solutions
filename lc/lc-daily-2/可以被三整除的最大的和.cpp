class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> a[2];
        for (auto &c : nums) {
            if (c % 3 == 0) ans += c;
            else a[c % 3 - 1].emplace_back(c);
        } 
        sort(a[0].begin(), a[0].end(), greater<int>());
        sort(a[1].begin(), a[1].end(), greater<int>());
        vector<int> s0(a[0].size() + 1), s1(a[1].size() + 1);
        for (int i = 0; i < a[0].size(); ++i)
            s0[i + 1] = s0[i] + a[0][i];
        for (int i = 0; i < a[1].size(); ++i)
            s1[i + 1] = s1[i] + a[1][i];
        int res = 0;
        for (int i = 0; i <= a[1].size(); ++i) {
            // 枚举选择其中的2的数量
            int sum = 2 * i, x = sum % 3;
            int tmp;
            if (x == 0) {
                tmp = a[0].size() / 3;
                res = max(res, s0[tmp * 3] + s1[i]);
            }
            else {
                if (a[0].size() < 3 - x) continue;
                tmp = (a[0].size() - 3 + x) / 3;
                res = max(res, s0[tmp * 3 + 3 - x] + s1[i]);
            }
        }
        return ans + res;
    }
};