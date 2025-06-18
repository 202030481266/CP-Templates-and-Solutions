// https://codeforces.com/problemset/problem/825/F
// 常数大优化 + 字符串哈希能卡过，哎，哈希太难了
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ull = unsigned long long;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 8003;
static constexpr ll base = 131;
static constexpr ll mod1 = 1e9 + 7; 
static constexpr ll mod2 = 1e9 + 9;

ll h1[maxn], h2[maxn], power1[maxn], power2[maxn];
char s[maxn];
int cost[maxn], dp[maxn], vis[maxn], mn[maxn];
int f[maxn][maxn];

bool cmp(int i, int k) {
	ll r_hash1 = ((h1[i] - h1[i - k] * power1[k] % mod1) % mod1 + mod1) % mod1;
	ll r_hash2 = ((h2[i] - h2[i - k] * power2[k] % mod2) % mod2 + mod2) % mod2;
	ll l_hash1 = ((h1[i - k] - h1[i - 2 * k] * power1[k] % mod1) % mod1 + mod1) % mod1;
	ll l_hash2 = ((h2[i - k] - h2[i - 2 * k] * power2[k] % mod2) % mod2 + mod2) % mod2;
	return (r_hash1 != l_hash1) || (r_hash2 != l_hash2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> (s + 1);
	int n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) {
		h1[i] = (h1[i - 1] * base + (ull)s[i]) % mod1;
		h2[i] = (h2[i - 1] * base + (ull)s[i]) % mod2;
	}
	power1[0] = power2[0] = 1;
	for (int i = 1; i <= n; ++i) {
		power1[i] = power1[i - 1] * base % mod1;
		power2[i] = power2[i - 1] * base % mod2;
	}
	for (int i = 1; i <= n; ++i) {
		if (i < 10) cost[i] = 1;
		else if (i < 100) cost[i] = 2;
		else if (i < 1000) cost[i] = 3;
		else cost[i] = 4;
	}
	memset(dp, 0x3f, sizeof(dp));
	memset(mn, 0x3f, sizeof(mn));
	dp[0] = 0;
	dp[1] = 2;
	mn[0] = mn[1] = 0;
	for (int i = 2; i <= n; ++i) {
		for (int j = i; 2 * j >= i + 2; --j) { // 只更新一半的长度
			int k = i - j + 1;
			bool flag = false;
			if (k >= 2) {
				if (!cmp(i, k)) flag = true;
			}
			else flag = (s[i] == s[i - 1]);
			if (flag) f[i][k] = 1 + (f[i - k][k] == 0 ? 1 : f[i - k][k]);
			else f[i][k] = 1;
			if (vis[j] < i) {
				for (int x = 1; x <= f[i][k]; ++x) {
					dp[i] = min(dp[i], dp[i - x * k] + cost[x] + k);
					vis[i - x * k + 1] = i;
				}
			}
		}
		if (i & 1) dp[i] = min(dp[i], mn[(1 + i) / 2] + 1 + i); // 前缀和优化
		else dp[i] = min(dp[i], mn[i / 2] + 1 + i);
		mn[i] = min(mn[i - 1], dp[i] - i);
	}
	cout << dp[n] << '\n';
}


// KMP 周期的做法
// 常数小的多，还没有被卡
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.length();
    
    // 计算每个数字的位数
    vector<int> sz(n + 1);
    for (int i = 1; i <= n; i++) {
        sz[i] = sz[i / 10] + 1;
    }
    
    // 动态规划数组
    vector<int> f(n + 1);
    vector<int> pi(n);
    
    for (int i = n - 1; i >= 0; i--) {
        string t = s.substr(i);
        int m = t.length();
        f[i] = min(m + 1, f[i + 1] + 2);
        
        int cnt = 0;
        for (int j = 1; j < m; j++) {
            char b = t[j];
            
            // KMP算法构建失败函数
            while (cnt > 0 && t[cnt] != b) {
                cnt = pi[cnt - 1];
            }
            if (t[cnt] == b) {
                cnt++;
            }
            pi[j] = cnt;
            
            // 检查是否存在周期性重复
            if (int k = j + 1 - cnt; cnt > 0 && (j + 1) % k == 0) {
                f[i] = min(f[i], f[i + j + 1] + sz[(j + 1) / k] + k);
            } else {
                f[i] = min(f[i], f[i + j + 1] + j + 2);
            }
        }
    }
    
    cout << f[0] << endl;
    return 0;
}