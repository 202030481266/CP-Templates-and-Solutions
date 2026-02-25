// /usr/liushulin
// -*- coding:UTF-8 -*-
/*#########################################################################
# File Name: luogu_CF149D.cpp
# Author: xiaoshulin
# Created Time: 2021/11/13 10:08:06
#########################################################################*/
 
#include <bits/stdc++.h>
#define re register 
using namespace std;
typedef long long ll;
const ll maxn = 1000, inf = 0x3f3f3f3f3f3f3f3f, mod = 1000000007;
ll n, dp[maxn][maxn][3][3], f[maxn], ans; char s[maxn]; stack<int> st;
void dfs(int l, int r) {
		// when the situation is like "()", it is the basic case
		if(l + 1 == r) dp[l][r][0][1] = dp[l][r][0][2] = dp[l][r][1][0] = dp[l][r][2][0] = 1;
		// when the situation is like "(.....)" , it can be directly transfer
		else if(f[l] == r) {
				dfs(l + 1, r - 1);
				for(re int i = 0; i <= 2; i++)
						for(re int j = 0; j <= 2; j++) {
								if(j != 1) dp[l][r][0][1] = (dp[l][r][0][1] + dp[l + 1][r - 1][i][j]) % mod;
								if(j != 2) dp[l][r][0][2] = (dp[l][r][0][2] + dp[l + 1][r - 1][i][j]) % mod;
								if(i != 1) dp[l][r][1][0] = (dp[l][r][1][0] + dp[l + 1][r - 1][i][j]) % mod;
								if(i != 2) dp[l][r][2][0] = (dp[l][r][2][0] + dp[l + 1][r - 1][i][j]) % mod;
						}
		}
		// when the situation is like "(..)..(..)", it should be divide into two basic parts and dfs partially
		else {
				// travesl each basic situation
				// the i, j, t, k means the left and right color
				dfs(l, f[l]); dfs(f[l] + 1, r);
				for(re int i = 0; i <= 2; i++)
						for(re int j = 0; j <= 2; j++)
								for(re int t = 0; t <= 2; t++)
										for(re int k = 0; k <= 2; k++) {
												if((j == 1 && t == 1) || (j == 2 && t == 2)) continue;
												dp[l][r][i][k] = (dp[l][r][i][k] + dp[l][f[l]][i][j] * dp[f[l] + 1][r][t][k] % mod) % mod;
										}
		}
}
int main() {
		scanf("%s", s); n = strlen(s); 
		for(re int i = 0; i < n; i++) {
				if(s[i] == '(') st.push(i);
				else f[st.top()] = i, f[i] = st.top(), st.pop();
		}
		dfs(0, n - 1);
		// calculate the tatal ans 
		for(re int i = 0; i <= 2; i++)
				for(re int j = 0; j <= 2; j++)
						ans = (ans + dp[0][n - 1][i][j]) % mod;
		cout << ans << endl;
		return 0;
}