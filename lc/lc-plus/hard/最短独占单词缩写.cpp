int have[2100000];
class Solution {
public:
    string minAbbreviation(string target, vector<string>& dictionary) {
        // 不允许连续的压缩字符串主要是为了防止双位数字的比较
        memset(have, 0, sizeof(have));
        int n = target.size();
        for (string& s : dictionary) { // 二进制运算
            int m = s.size();
            if (m != n) continue;
            have[0] = 1;
            int res = 0;
            for (int i = 0; i < n; ++i) {
                if (target[i] == s[i]) {
                    res |= (1 << i);
                }
            }
            for (int j = res; j; j = (j - 1) & res) { // 枚举子集
                have[j] = 1;
            }
        }
        int ans = -1, len = INT_MAX;
        for (int i = 0; i < (1 << n); ++i) {
            if (!have[i]) {
                int pre = 0, cur = (i & 1), l = 0;
                for (int j = 1; j < n; ++j) {
                    if (((i >> j) & 1) != cur) {
                        int x = j - pre;
                        if (cur == 0) {
                            l += (x >= 10 ? 2 : 1);
                        }
                        else {
                            l += x;
                        }
                        cur ^= 1;
                        pre = j;
                    }
                }
                l += (cur == 1 ? n - pre : (n - pre >= 10 ? 2 : 1));
                if (l < len) {
                    len = l;
                    ans = i;
                }
            }
        }
        string res;
        int pre = 0, cur = (ans & 1);
        for (int i = 1; i < n; ++i) {
            if (((ans >> i) & 1) != cur) {
                int x = i - pre;
                if (cur) {
                    for (int j = pre; j < i; ++j) {
                        res.push_back(target[j]);
                    }
                }
                else {
                    res += to_string(x);
                }
                cur ^= 1;
                pre = i;
            }
        }
        if (cur) {
            for (int j = pre; j < n; ++j) {
                res.push_back(target[j]);
            }
        }
        else res += to_string(n - pre);
        return res;
    }
};