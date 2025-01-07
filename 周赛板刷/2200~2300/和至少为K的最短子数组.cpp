// https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/



#define lowbit(x) (x&(-x))
typedef long long ll;
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
    	// 离散化+权值树状数组
    	ll n = nums.size(), a[n * 2 + 10], p = 0, sum[n * 2 + 10];
    	memset(sum, 0, sizeof(sum));
    	memset(a, 0, sizeof(a));
    	a[p++] = 0;
    	for (int i = 1; i <= n * 2 + 1; ++i) {
    		if (i <= n) sum[i] = sum[i - 1] + nums[i - 1];
    		else sum[i] = sum[i - (n + 1)] + k;
    		a[p++] = sum[i];
    	}
    	sort(a, a + p);
    	for (int i = 0; i <= 2 * n + 1; ++i) {
    		int pos = lower_bound(a, a + p, sum[i]) - a + 1;  // 加一
    		sum[i] = pos;
    	}
    	// 权值线段树维护>=sum[i]+k的最大坐标
    	int tr[n * 2 + 10];
    	memset(tr, -1, sizeof(tr));
    	auto update = [&](ll x, int v) {
    		for (ll i = x; i < n * 2 + 10; i += lowbit(i)) tr[i] = max(tr[i], v);
    	};
    	auto query = [&](ll x) -> int {
    		int res = -1;
    		for (ll i = x; i > 0; i -= lowbit(i)) res = max(res, tr[i]);
    		return res;
    	};
    	update(sum[n + 1], 0);
    	int ans = n * 2;
    	for (int i = 1; i <= n; ++i) {
    		int rs = query(sum[i]);
    		if (rs != -1) ans = min(ans, i - rs);
    		update(sum[n + i + 1], i);
    	}
    	return ans == 2 * n ? -1 : ans;
    }
};



// 单调队列版本
typedef long long ll;
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
    	int n = nums.size(), q[n * 2]; 
    	ll sum[n + 1];
    	memset(sum, 0, sizeof(sum));
    	memset(q, -1, sizeof(q));
    	int st = 0, ed = 0, ans = n * 2;
    	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + nums[i - 1];
    	q[ed++] = 0;
    	for (int i = 1; i <= n; ++i) {
    		while (st < ed && sum[i] - sum[q[st]] >= k) ans = min(ans, i - q[st++]);
    		while (st < ed && sum[q[ed-1]] >= sum[i]) --ed;
    		q[ed++] = i;
    	}
    	return ans == 2 * n ? -1 : ans;
   }
};