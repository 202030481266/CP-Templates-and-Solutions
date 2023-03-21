// https://leetcode.cn/problems/minimum-sum-of-squared-difference/
// 复杂的数学统计算法，nlogn


class Solution {
public:
	long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
		int n = nums1.size();
		vector<long long> sub(n);
		unordered_map<int, int> cnt;
		priority_queue<int> q;
		set<int> s;

		long long ans = 0;
		int k = k1 + k2;

		for (int i = 0; i < n; ++i) {
			sub[i] = 1ll * abs(nums1[i] - nums2[i]);
			ans += sub[i] * sub[i];
			if (sub[i] > 0) {
				// calculate the numbers 
				++cnt[sub[i]];
				s.emplace(sub[i]);
			}
		}
		for (int v : s) q.emplace(v);
        cout << ans << endl;
		while (k > 0 && !q.empty()) {
			int mx = q.top();
			q.pop();

			if (q.empty()) {
				// 矩阵遍历
                if (k >= cnt[mx] * mx) {
                    ans = 0;
                    break;
                }
				int x = k / cnt[mx], y = k % cnt[mx];
				long long sum = 0;
				if (x > 0) {
					sum += (2ll * x * mx - 1ll * x * x) * cnt[mx];
				}
				sum += (2ll * mx - 1 - 2ll * x) * y;
				ans -= sum;
				break;
			}
			else {
				int sm = q.top();
				long long x = mx - sm;
				if (k >= x * cnt[mx]) {
					long long sum = (2ll * x * mx - 1ll * x * x) * cnt[mx];
					ans -= sum;
					k -= x * cnt[mx];
					cnt[sm] += cnt[mx];
					cnt[mx] = 0;
				}
				else {
					int x = k / cnt[mx], y = k % cnt[mx];
					long long sum = 0;
					if (x > 0) {
						sum += (2ll * x * mx - 1ll * x * x) * cnt[mx];
					}
					sum += (2ll * mx - 1 - 2ll * x) * y;
					ans -= sum;
					break;
				}
			}
		}
		return ans;
	}
};