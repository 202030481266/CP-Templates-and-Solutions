// https://leetcode.cn/problems/minimum-cost-to-make-array-equal



class Solution {
public:
	long long minCost(vector<int>& nums, vector<int>& cost) {
		int n = nums.size();
		vector<pair<int, int>> a;
		for (int i = 0; i < n; ++i) a.emplace_back(nums[i], cost[i]);
		sort(a.begin(), a.end());

		vector<long long> S(n), F(n);
		unordered_map<int, int> pos;

		S[0] = 1ll * a[0].first * a[0].second;
		F[0] = a[0].second * 1ll;

		for (int i = 1; i < n; ++i) {
			S[i] = S[i - 1] + 1ll * a[i].first * a[i].second;
			F[i] = F[i - 1] + 1ll * a[i].second;
		}
		for (int i = 0; i < n; ++i) {
			if (!pos.count(a[i].first)) pos[a[i].first] = i;
		}
		long long ans = 0x3f3f3f3f3f3f3f3f;
		for (int i = 0; i < n; ++i) {
			// turn all the numbers to a[i].first
			int p = pos[a[i].first];
			if (p > 0) {
				ans = min(ans, a[i].first * (2 * F[p - 1] - F[n - 1]) + S[n - 1] - 2 * S[p - 1]);
			}
			else {
				ans = min(ans, S[n - 1] - a[i].first * F[n - 1]);
			}
		}
		return ans;
	}
};