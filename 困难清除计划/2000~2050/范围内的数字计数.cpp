// 数位DP模板题目，包含有前导零的影响
class Solution {
    int dp[12][12];
    string s;
    int m, num;
public:
    int f(int i, int cnt, bool is_limit, bool is_num) {
        if (i == m) return is_num ? cnt : 0;
        if (dp[i][cnt] != -1 && !is_limit && is_num) return dp[i][cnt];
        int res = 0, up = (is_limit ? s[i] - '0' : 9);
        if (!is_num) {
            res += f(i + 1, cnt, false, false);
            for (int d = 1; d <= up; ++d)
                res += f(i + 1, cnt + (d == num), is_limit && (d == up), true);
        }
        else { 
            for (int d = 0; d <= up; ++d) res += f(i + 1, cnt + (d == num), is_limit && (d == up), true);
        }
        if (!is_limit && is_num) dp[i][cnt] = res;
        return res;
    }
    int cal(int v) {
        memset(dp, -1, sizeof(dp));
        s = to_string(v);
        m = s.size();
        return f(0, 0, true, false);
    }
    int digitsCount(int d, int low, int high) {
        num = d;
        return cal(high) - cal(low - 1);
    }
};