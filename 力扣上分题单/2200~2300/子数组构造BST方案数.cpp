// https://leetcode.cn/problems/number-of-ways-to-reorder-array-to-get-same-bst/



typedef long long ll;
class Solution {
	static constexpr int p = 1000000007;
	ll a[2000];
	ll pow_mod(ll x, ll y) { // 快速幂 x^y%p
		ll ans = 1;
		x %= p;
		for (ll i = y; i; i >>= 1, x = x * x % p) 
			if (i & 1) ans = ans * x % p;
		return ans;
	}
	ll C(ll n, ll m) { // 使用费曼小定理求解组合数逆元
		if (m > n) return 0;
		return ((a[n] * pow_mod(a[m], p - 2)) % p * pow_mod(a[n - m], p - 2) % p);
	}
public:
    int numOfWays(vector<int>& nums) {
    	int n = nums.size(); 
    	a[0] = 1;
    	for (int i = 1; i <= n; ++i) a[i] = a[i - 1] * i % p;
    	// 递归求解
    	function<ll(vector<int>)> dfs = [&](vector<int> arr) -> ll {
    		int N = arr.size();
    		if (N <= 2) return 1;
    		vector<int> r, l;
    		for (int i = 1; i < N; ++i) {
    			if (arr[i] > arr[0]) r.emplace_back(arr[i]);
    			else l.emplace_back(arr[i]);
    		}
    		ll left = dfs(l);
    		ll right = dfs(r);
    		ll res = C(N - 1, 1ll * l.size());
    		return ((res * left) % p * right % p);
    	};
    	return (dfs(nums) - 1 + p) % p;
    }
};