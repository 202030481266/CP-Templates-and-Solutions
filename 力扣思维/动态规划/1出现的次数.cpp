// https://leetcode.cn/problems/number-of-digit-one/
// 经典的数位dp题目，使用模板就可以了
// dp[i][cnt1] 表示的是构造到第i位的时候，没有限制的情况下可以产生的1的个数
// 状态的意义为: 对于没有限制的情况下，前i位出现的1位置不是重要的。
// 比如对于dp[m-1][0]只能是1，因为只有一种情况 0000...1
// dp[m-1][1] 表示 10....1, 10....2, 10....3, 10....4等，共出现了11个1，而我们不关心前面的1出现的位置
// dp[m-1][2] 表示的情况也一样，都是21个


class Solution {
public:
    int countDigitOne(int n) {
        auto s = to_string(n);
        int m = s.length(), dp[m][m];
        memset(dp, -1, sizeof(dp));
        function<int(int, int, bool)> f = [&](int i, int cnt1, bool is_limit) -> int {
            if (i == m) return cnt1;
            if (!is_limit && dp[i][cnt1] >= 0) return dp[i][cnt1];
            int res = 0;
            for (int d = 0, up = is_limit ? s[i] - '0' : 9; d <= up; ++d) // 枚举要填入的数字 d
                res += f(i + 1, cnt1 + (d == 1), is_limit && d == up);
            if (!is_limit) dp[i][cnt1] = res;
            return res;
        };
        return f(0, 0, true);
    }
};

