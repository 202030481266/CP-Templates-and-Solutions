#include <bits/stdc++.h>
using namespace std;
namespace Manacher {
    // 返回奇数长度的最大回文串，d1[i]表示右边最长回文半径， aba中，d1[1]=2
    std::vector<int> odd_palindrome_radius(std::string s) {
        int n = s.size();
        vector<int> d1(s.size());
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = (i > r ? 1 : min(d1[l + r - i], r - i + 1));
            while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) ++k;
            d1[i] = k--; // [0, k)
            if (i + k > r) {
                r = i + k;
                l = i - k;
            }
        }
        return d1;
    }
    // 返回偶数长度的最大回文串，d2[i]表示右边最长回文半径，abba中d2[2]=2
    std::vector<int> even_palindrome_radius(std::string s) {
        int n = s.size();
        vector<int> d2(s.size());
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = (i > r ? 0 : min(d2[l + r - i + 1], r - i + 1));
            while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k;
            d2[i] = k--; // [0, k)
            if (i + k > r) {
                r = i + k;
                l = i - k - 1;
            }
        }
        return d2;
    }
}
int main() {
    std::string s;
    cin >> s;
    std::vector<int> d1 = Manacher::odd_palindrome_radius(s);
    std::vector<int> d2 = Manacher::even_palindrome_radius(s);
    cout << max(*max_element(d1.begin(), d1.end()) * 2 - 1, *max_element(d2.begin(), d2.end()) * 2) << endl;
}

// 线性时间复杂度寻找到最长的回文子串
// 下面是统一的一种写法


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
