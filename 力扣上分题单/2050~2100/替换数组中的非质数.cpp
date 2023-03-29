// https://leetcode.cn/problems/replace-non-coprime-numbers-in-array/
// 栈模拟的思想，我以为是双向遍历。。。


class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int> &nums) {
        vector<int> s;
        for (int num : nums) {
            s.push_back(num);
            while (s.size() > 1) {
                int x = s.back(), y = s[s.size() - 2];
                int g = gcd(x, y);
                if (g == 1) break;
                s.pop_back();
                s.back() *= x / g;
            }
        }
        return s;
    }
};

