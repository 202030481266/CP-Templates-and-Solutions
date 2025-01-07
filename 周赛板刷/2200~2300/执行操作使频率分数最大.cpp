// xiaoshulin
// 2024.1.6

class Solution {
    using ll = long long;
public:
    int maxFrequencyScore(vector<int>& nums, long long k) {
        int n = nums.size();

        // 众数的算法
		sort(nums.begin(), nums.end());

		vector<ll> sum(n + 1);
		for (int i = 0; i < n; ++i) 
			sum[i + 1] = sum[i] + nums[i];

		auto check = [&](int len) -> bool {
			// (l, l + len] = (l, mid], (mid, r]
			for (int i = 0; i + len <= n; ++i) {
				ll mid = (i * 2 + len + 1) / 2;
				ll left = (mid - i) * nums[mid - 1] - (sum[mid] - sum[i]);
				ll right = (sum[i + len] - sum[mid]) - (i + len - mid) * nums[mid - 1];
				if (left + right <= k) {
					return true;
				}
			}
			return false;
		};

		int l = 1, r = n, ans = 0;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				ans = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		return ans;
    }

};
