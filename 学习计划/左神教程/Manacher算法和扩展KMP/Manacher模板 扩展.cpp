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
    // 这里的原理是，每一个原串开始的位置i，都可以对应扩展串的一个形如 #.....# 的中心串。
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

// 手写的同时更新版本，逻辑更加复杂
// 原理是左端点不会回退而且遇到一个中心就更新，这种方法可以获取扩展串的起点开始最长回文子串长度
// 遇到下一个中心的左端点之前一直单调更新，这里很容易使用数学方法证明: 
// i, .... , nxt, ... c c+1, ...
// c+1的左端点在nxt，说明[i,nxt)的最长回文半径由c决定，而nxt开始，c-nxt < c+1-nxt，最长回文半径肯定不如c+1大
vector<int> manacher2(string s) {
    string ss(2 * s.size() + 1, '#');
    for (int i = 0; i < s.size(); ++i) ss[2 * i + 1] = s[i];
    int n = ss.size(), mx = 0, c = 0, r = 0;
    vector<int> dp(n), left(s.size());
    for (int i = 0; i < n; ++i) {
        int len = (i < r ? min(dp[2 * c - i], r - i) : 1);
        while (i - len >= 0 && i + len < n && ss[i - len] == ss[i + len]) ++len;
        dp[i] = len;
        ans = max(ans, dp[i]-1);
        if (i + len > r) {
            // 本质上在移动的时候还可以计算从某个点出发的最大回文串半径
            // c -> i
            for (int j = c; j < i; ++j) {
                int nxt = (j + 1) - dp[j + 1] + 1;
                for (int k = j - dp[j] + 1, v = dp[j]; k < nxt; ++k, --v) {
                    if (k & 1) left[k/2] = v;
                }
            }
            c = i;
            r = i + len;
            if ((c - len + 1) & 1) left[(c - len + 1)/2] = len;
        }
    }
    for (int j = c; j < n - 1; ++j) {
        int nxt = (j + 1) - dp[j + 1] + 1;
        for (int k = j - dp[j] + 1, v = dp[j]; k < nxt; ++k, --v) {
            if (k & 1) left[k/2] = v;
        }
    }
    // for (int v : left) cout << v << ' ';cout << endl;
    return left;
}
