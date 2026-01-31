// https://leetcode.cn/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/



class Solution {
	typedef long long ll;
public:
    double getProbability(vector<int>& balls) {
    	int n = balls.size(), sum[n + 1];
    	memset(sum, 0, sizeof(sum));
    	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + balls[i - 1];
    	// 统计函数
    	ll f[50][10];
    	memset(f, 0, sizeof(f));
    	auto C = [&](ll n, ll m) -> ll {
    		if (f[n][m]) return f[n][m];
    		ll rs = 1;
    		for (int i = n; i > n - m; --i) rs *= i;
    		for (int i = 2; i <= m; ++i) rs /= i;
    		return f[n][m] = rs;
    	};
    	// 搜索具体的方案
    	double ans = 0, total = 1;
    	int cnt[n];
    	memset(cnt, 0, sizeof(cnt));
    	function<void(int)> dfs = [&](int d) {
    		if (d == n) {
    			int res = 0, x = 0, y = 0;
    			for (int i = 0; i < n; ++i) {
    				res += cnt[i];
    				if (cnt[i] == 0) ++x;
    				if (cnt[i] == balls[i]) ++y;
    			}
    			if (res == sum[n] / 2 && x == y) {
    				double t1 = 1, t2 = 1;
    				int s1 = sum[n] / 2, s2 = sum[n] / 2;
    				for (int i = 0; i < n; ++i) {
    					t1 *= C(s1, cnt[i]);
    					s1 -= cnt[i];
    					t2 *= C(s2, balls[i] - cnt[i]);
    					s2 -= (balls[i] - cnt[i]);
    				}
    				ans += t1 * t2;
    			}
    			return;
    		}
    		for (int i = 0; i <= balls[d]; ++i) {
    			cnt[d] = i;
    			dfs(d + 1);
    		}
    	};
    	dfs(0);
    	for (int i = 1; i <= n; ++i) total *= C(sum[n] - sum[i - 1], balls[i - 1]);
    	return ans / total;
    }
};