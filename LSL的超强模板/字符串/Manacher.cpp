// 线性时间复杂度寻找到最长的回文子串


char c[100010], s[100010];
int dp[100010];
void Manacher() {  // 预处理字符串，所有字符串变成奇数长度的字符串，同时可以加入哨兵防止越界
	scanf("%s", c + 1);
	memset(dp, 0, sizeof(dp));
	int n = strlen(c + 1), cnt = 0, mr = 0, mid = 0, ans = 0;
	s[++cnt] = '~'; // 哨兵
	s[++cnt] = '#';
	for (int i = 1; i <= n; ++i) s[++cnt] = c[i], s[++cnt] = '#';
	s[++cnt] = '!'; // 哨兵
	for (int i = 2; i <= cnt - 1; ++i) {
		if (i <= mr) dp[i] = min(dp[2 * mid - i], mr - i + 1);
		else dp[i] = 1;
		while (s[i - dp[i]] == s[i + dp[i]]) ++dp[i];
		if (i + dp[i] > mr) mr = i + dp[i] - 1, mid = i;
		ans = max(ans, dp[i]); // 最长的回文子串长度等于其中的回文半径-1  #a#a#b#a#a#
	}
	printf("%d", ans - 1);
}
