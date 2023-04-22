// https://leetcode.cn/problems/minimum-space-wasted-from-packaging/
// 逆向思维 + 排序 + 前缀和


class Solution {
	static constexpr int mod = 1000000007;
	int cnt[100010]; 
public:
    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
    	// 选择了一个供应商就已经决定了该供应商所能达到的最小浪费空间（贪心）
    	// 直接n*m可能会爆炸，所以做个计数映射就好了呗（一般都是这个套路）
    	// 统计每一个箱子的数值可以覆盖的包裹数量和前缀和
    	long long sum = 0, ans = 2e10; int mx = 0;
    	memset(cnt, 0, sizeof(cnt));
    	for (int c : packages) ++cnt[c], sum += c, mx = max(mx, c);
    	for (int i = 1; i <= 100000; ++i) cnt[i] += cnt[i - 1];
    	for (auto &c : boxes) {
    		sort(c.begin(), c.end());
			if (c.back() < mx) continue;
    		long long res = 1ll * cnt[c[0]] * c[0];
    		for (int i = 1; i < c.size(); ++i) 
    			res += (cnt[c[i]] - cnt[c[i - 1]]) * 1ll * c[i];
    		ans = min(ans, res - sum);
    	}
    	return ans == 2e10 ? -1 : ans % mod;
    }
};