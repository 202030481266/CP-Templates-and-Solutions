/*
主要是考虑位数，限制，之前的状态，枚举数限制，是否填充，是否限制，前导0的影响
*/

// 数 1 的出现个数 [1, n]
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

// 至少重复出现一次的数统计
int numDupDigitsAtMostN(int n) {
    auto s = to_string(n);
    // dp[i] 表示不受n约束并且前面有数字填充的值
    int m = s.size(), dp[4096][m + 1][2];
    memset(dp, -1, sizeof(dp));

    function<int(int,int,bool,bool,bool)> dfs = [&](int pos,int S,bool is_limit,bool is_num,bool is_exist) -> int {
        if (pos == m) return is_exist;
        if (!is_limit && is_num) {
            if (is_exist && dp[S][pos][1] >= 0) return dp[S][pos][1];
            if (!is_exist && dp[S][pos][0] >= 0) return dp[S][pos][0];
        }
        int res = 0;
        int up = (is_limit) ? s[pos] - '0' : 9;
        if (!is_num) {
            res += dfs(pos + 1, S, false, false, is_exist);
            for (int i = 1; i <= up; i++) {
                bool temp = (S >> i) & 1;
                int cur = S | (1 << i);
                res += dfs(pos + 1, cur, is_limit && (i == up), true, is_exist || temp);
            }
        } else {
            for (int i = 0; i <= up; i++) {
                bool temp = (S >> i) & 1;
                int cur = S | (1 << i);
                res += dfs(pos + 1, cur, is_limit && (i == up), true, is_exist || temp);
            }
        }
        if (!is_limit && is_num) {
            if (is_exist) dp[S][pos][1] = res;
            else dp[S][pos][0] = res;
        }
        return res;
    };
    return dfs(0, 0, true, false, false);
}

// 填充数字
int atMostNGivenDigitSet(vector<string> &digits, int n) {
    auto s = to_string(n);
    int m = s.length(), dp[m];
    memset(dp, -1, sizeof(dp)); // dp[i] = -1 表示 i 这个状态还没被计算出来
    function<int(int, bool, bool)> f = [&](int i, bool is_limit, bool is_num) -> int {
        if (i == m) return is_num; // 如果填了数字，则为 1 种合法方案
        if (!is_limit && is_num && dp[i] >= 0) return dp[i]; // 在不受到任何约束的情况下，返回记录的结果，避免重复运算
        int res = 0;
        if (!is_num) // 前面不填数字，那么可以跳过当前数位，也不填数字
            // is_limit 改为 false，因为没有填数字，位数都比 n 要短，自然不会受到 n 的约束
            // is_num 仍然为 false，因为没有填任何数字
            res = f(i + 1, false, false);
        char up = is_limit ? s[i] : '9'; // 根据是否受到约束，决定可以填的数字的上限
        // 注意：对于一般的题目而言，如果这里 is_num 为 false，则必须从 1 开始枚举，由于本题 digits 没有 0，所以无需处理这种情况
        for (auto &d : digits) { // 枚举要填入的数字 d
            if (d[0] > up) break; // d 超过上限，由于 digits 是有序的，后面的 d 都会超过上限，故退出循环
            // is_limit：如果当前受到 n 的约束，且填的数字等于上限，那么后面仍然会受到 n 的约束
            // is_num 为 true，因为填了数字
            res += f(i + 1, is_limit && d[0] == up, true);
        }
        if (!is_limit && is_num) dp[i] = res; // 在不受到任何约束的情况下，记录结果
        return res;
    };
    return f(0, true, false);
}

// 连续数字（找到二进制下不存在连续1的数的个数）
int findIntegers(int n) {
    int m = __lg(n), dp[m + 1][2];
    memset(dp, -1, sizeof(dp));

    function<int(int,bool,bool)> dfs = [&](int pos,bool pre,bool is_limit) {
        if (pos < 0) return 1;
        if (!is_limit && dp[pos][pre] >= 0) return dp[pos][pre];
        int up = (is_limit) ? (n >> pos) & 1 : 1;
        int res = dfs(pos - 1, false, is_limit && up == 0);
        if (!pre && up == 1) res += dfs(pos - 1, true, is_limit);
        if (!is_limit) dp[pos][pre] = res;
        return res;
    };
    return dfs(m, false, true);
}


// 带上下限的数位DP
// 作者：灵茶山艾府
// https://leetcode.cn/problems/count-the-number-of-powerful-integers/solutions/2595149/shu-wei-dp-shang-xia-jie-mo-ban-fu-ti-da-h6ci/
class Solution {
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        string low = to_string(start);
        string high = to_string(finish);
        int n = high.size();
        low = string(n - low.size(), '0') + low; // 补前导零，和 high 对齐
        int diff = n - s.size();

        vector<long long> memo(n, -1);
        function<long long(int, bool, bool)> dfs = [&](int i, bool limit_low, bool limit_high) -> long long {
            if (i == low.size()) {
                return 1;
            }

            if (!limit_low && !limit_high && memo[i] != -1) {
                return memo[i]; // 之前计算过
            }

            // 第 i 个数位可以从 lo 枚举到 hi
            // 如果对数位还有其它约束，应当只在下面的 for 循环做限制，不应修改 lo 或 hi
            int lo = limit_low ? low[i] - '0' : 0;
            int hi = limit_high ? high[i] - '0' : 9;

            long long res = 0;
            if (i < diff) { // 枚举这个数位填什么
                for (int d = lo; d <= min(hi, limit); d++) {
                    res += dfs(i + 1, limit_low && d == lo, limit_high && d == hi);
                }
            } else { // 这个数位只能填 s[i-diff]
                int x = s[i - diff] - '0';
                if (lo <= x && x <= min(hi, limit)) {
                    res = dfs(i + 1, limit_low && x == lo, limit_high && x == hi);
                }
            }

            if (!limit_low && !limit_high) {
                memo[i] = res; // 记忆化 (i,false,false)
            }
            return res;
        };
        return dfs(0, true, true);
    }
};

