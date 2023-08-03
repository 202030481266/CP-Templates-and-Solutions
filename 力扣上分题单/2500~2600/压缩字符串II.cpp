// 这个数据范围应该是dp暴力，因为去除之后会产生很多合并的结果，所以需要搜索，贪心不行，局部最优解不一定是最优的
// 细节无比之多！！！！
class Solution {
    int dp[101][101][26][11];  // 0 ~ 10，可以使用滚动优化，但是我懒
public:
    int getLengthOfOptimalCompression(string s, int m) {
        int n = s.size();
        if (n <= m) return 0;
        if (n == 100 && m == 0) {
            bool flag = true;
            for (int i = 1; i < n; ++i)
                if (s[i] != s[0]) {
                    flag = false;
                    break;
                }
            if (flag) return 4; // a100， 只有这种可能字符出现的频率是3位数
        }
        memset(dp, 0x3f, sizeof(dp));
        vector<int> a, b;
        for  (int i = 0; i < n; ++i) {
            int j = i;
            // [i, j)
            while (j < n && s[j] == s[i]) ++j;
            a.emplace_back(s[i] - 'a');
            b.emplace_back(j - i);
            i = j - 1;
        }
        n = a.size();
        for (int j = 0; j <= m; ++j) {
            int tmp = max(0, b[0] - j), up = min(10, tmp);
            dp[1][j][a[0]][up] = (tmp <= 1 ? tmp : (tmp < 10 ? 2 : 3));
        }
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                // 全部去掉
                if (j >= b[i - 1]) {
                    for (int end = 0; end < 26; ++end)
                        for (int cnt = 0; cnt <= 10; ++cnt)
                            dp[i][j][end][cnt] = min(dp[i][j][end][cnt], dp[i - 1][j - b[i - 1]][end][cnt]);
                }
                // 有所保留，此刻必然是以 a[i - 1] 结尾
                // max(b[i - 1] - j, 1) <= x <= b[i - 1];
                for (int x = max(b[i - 1] - j, 1); x <= b[i - 1]; ++x) {
                    int len = (x <= 1 ? x : (x < 10 ? 2 : 3));
                    int up = min(x, 10);
                    for (int end = 0; end < 26; ++end) {
                        if (end != a[i - 1]) {
                            for (int k = 0; k <= 10; ++k)
                                dp[i][j][a[i - 1]][up] = min(dp[i][j][a[i - 1]][up], dp[i - 1][j - (b[i - 1] - x)][end][k] + len);
                        }
                        else {
                            // can merge
                            for (int k = 0; k <= 10; ++k) {
                                int tmp = min(10, x + k);
                                int val = (tmp <= 1 ? tmp : (tmp < 10 ? 2 : 3)) - (k <= 1 ? k : (k < 10 ? 2 : 3));  // 变化的差距
                                dp[i][j][a[i - 1]][tmp] = min(dp[i][j][a[i - 1]][tmp], dp[i - 1][j - (b[i - 1] - x)][end][k] + val);
                            }
                        }
                    }
                }
            }
        }
        int ans = 0x3f3f3f3f;
        for (int end = 0; end < 26; ++end)
            for (int cnt = 1; cnt <= 10; ++cnt) {
                ans = min(ans, dp[n][m][end][cnt]);
            }
        return ans;
    }
};