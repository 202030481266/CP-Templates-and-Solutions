// 同时计算每个位置开始的最长回文半径

void manacher(string s) {
    int n0 = s.size();
    // 构造变换串，在字符间插入 '#' 保证回文长度均为奇数
    string ss(2 * n0 + 1, '#');
    for (int i = 0; i < n0; ++i)
        ss[2 * i + 1] = s[i];
    int n = ss.size();
    
    // dp[i] 表示以 i 为中心的回文半径（包括中心）
    vector<int> dp(n, 0);
    int c = 0, r = 0;
    for (int i = 0; i < n; ++i) {
        // 利用对称性加速
        int len = (i < r ? min(dp[2 * c - i], r - i) : 1);
        while (i - len >= 0 && i + len < n && ss[i - len] == ss[i + len])
            ++len;
        dp[i] = len;
        if (i + len > r) {
            c = i;
            r = i + len;
        }
    }
    
    // left[i] 表示原串中从位置 i 出发的最长回文长度
    // 这里的原理也不难，每一个原串开始的位置i，都可以对应扩展串的一个形如 #.....# 的回文串，而且是最长的。
    vector<int> left(n0, 0);
    for (int i = 0; i < n; ++i) {
        // 在变换串中，回文区间为 [i - dp[i] + 1, i + dp[i] - 1]
        int L = i - dp[i] + 1;
        int R = i + dp[i] - 1;
        // 映射回原串的下标（注意：'#' 与字符的混合，除以2即可）
        int origL = L / 2;
        int origR = R / 2;
        int lenOriginal = origR - origL + 1;
        if (origL < n0) {
            // 取最大的回文长度
            left[origL] = max(left[origL], lenOriginal);
        }
    }
    
    // 输出 left 数组（可以根据需要进一步处理）
    for (int v : left)
        cout << v << ' ';
}