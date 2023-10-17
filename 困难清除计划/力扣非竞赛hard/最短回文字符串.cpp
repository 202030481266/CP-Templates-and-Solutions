class Solution {
public:
    string shortestPalindrome(string text) {
        // manachar algorithm
        int n = text.size(), dp[n * 2 + 10];
        memset(dp, 0, sizeof(dp));

        // construct the manacher string
        vector<char> s(n * 2 + 10);
        int cnt = 0;
        s[++cnt] = '~';  // 哨兵
        s[++cnt] = '#';
        for (int i = 0; i < n; ++i) s[++cnt] = text[i], s[++cnt] = '#';
        s[++cnt] = '!';  // 哨兵

        // manacher 
        int mr = 0, mid = 0, ans = 0;
        for (int i = 2; i <= cnt - 1; ++i) {
            if (i <= mr) dp[i] = min(dp[2 * mid - i], mr - i + 1);
            else dp[i] = 1; 
            while (s[i - dp[i]] == s[i + dp[i]]) ++dp[i]; 
            if (i + dp[i] > mr) mr = i + dp[i] - 1, mid = i;
            if (dp[i] == i - 1) ans = max(ans, i - 1);
        }
        string tmp = text.substr(ans - 1, n - ans + 1);
        reverse(tmp.begin(), tmp.end());
        return tmp + text;
    }
};